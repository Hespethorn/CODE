/**
 * directory_lister.c - 类似 `ls -l` 的目录列表程序
 *
 * 整体架构：
 * 1. 参数解析：处理命令行参数，确定目标目录
 * 2. 目录扫描：读取目录项并排序
 * 3. 元数据获取：通过lstat获取每个文件的详细信息
 * 4. 格式化输出：按照ls -l的格式展示结果
 *
 * 安全注意事项：
 * - 使用calloc而非malloc确保内存初始化为0
 * - 所有字符串操作使用snprintf/strftime避免缓冲区溢出
 */

// C系统库头文件（按功能相关性有序排列）
#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <sys/stat.h>   
#include <dirent.h>     
#include <unistd.h>     
#include <time.h>       
#include <sys/types.h>  
#include <pwd.h>        
#include <grp.h>        

/* 宏定义：错误检查（Google风格do-while(0)结构） */
#define ERROR_CHECK(ret, error_val, msg) \
do { \
    if ((ret) == (error_val)) { \
        fprintf(stderr, "Error: %s (errno=%d)\n", (msg), errno); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

/**
 * 格式化文件类型和权限字符串（如 "-rwxr-xr-x"）
 * @param mode 文件模式（来自lstat.st_mode）
 * @param tm_str 输出缓冲区（至少11字节，含终止符）
 *
 * 实现细节：
 * - 使用标准宏（如S_IRUSR）代替位运算硬编码，提高可读性
 * - 特殊权限位（SUID/SGID/Sticky）处理逻辑：
 *   - 若执行位开启，显示小写字母（如's'、't'）
 *   - 若执行位关闭，显示大写字母（如'S'、'T'）
 */
void format_type_mode(mode_t mode, char* tm_str) {
   // 文件类型处理
  switch (mode & S_IFMT) {
  case S_IFDIR:   tm_str[0] = 'd'; break;
  case S_IFCHR:   tm_str[0] = 'c'; break;
  case S_IFBLK:   tm_str[0] = 'b'; break;
  case S_IFIFO:   tm_str[0] = 'p'; break;
  case S_IFLNK:   tm_str[0] = 'l'; break;
  case S_IFREG:   tm_str[0] = '-'; break;
  case S_IFSOCK:  tm_str[0] = 's'; break;
  default:        tm_str[0] = '?'; break;
  }

  // 权限位处理（使用标准宏提高可读性）
  tm_str[1] = (mode & S_IRUSR) ? 'r' : '-';  // 用户读
  tm_str[2] = (mode & S_IWUSR) ? 'w' : '-';  // 用户写
  tm_str[3] = (mode & S_IXUSR) ? 'x' : '-';  // 用户执行
  tm_str[4] = (mode & S_IRGRP) ? 'r' : '-';  // 组读
  tm_str[5] = (mode & S_IWGRP) ? 'w' : '-';  // 组写
  tm_str[6] = (mode & S_IXGRP) ? 'x' : '-';  // 组执行
  tm_str[7] = (mode & S_IROTH) ? 'r' : '-';  // 其他读
  tm_str[8] = (mode & S_IWOTH) ? 'w' : '-';  // 其他写
  tm_str[9] = (mode & S_IXOTH) ? 'x' : '-';  // 其他执行

  // 特殊权限位说明：
// - S_ISUID: 执行时设置用户ID（如/bin/su）
// - S_ISGID: 执行时设置组ID（如某些共享目录）
// - S_ISVTX: 粘滞位（如/tmp目录的防删除保护）
  if (mode & S_ISUID) tm_str[2] = (tm_str[2] == '-') ? 's' : 'S';
  if (mode & S_ISUID) tm_str[2] = (tm_str[2] == '-') ? 's' : 'S';
  if (mode & S_ISGID) tm_str[5] = (tm_str[5] == '-') ? 's' : 'S';
  if (mode & S_ISVTX) tm_str[8] = (tm_str[8] == '-') ? 't' : 'T';

  tm_str[10] = '\0';  // 终止符
}

/**
 * 格式化时间为"Mon dd HH:MM"（如 "Jul  5 14:30"）
 * @param mtime 文件修改时间戳（来自lstat.st_mtime）
 * @param time_str 输出缓冲区（至少20字节）
 *
 * 注意事项：
 * - localtime非线程安全（多线程环境需改用localtime_r）
 * - strftime格式说明：
 *   - %b: 月份缩写（如"Jan"）
 *   - %e: 日期（带前导空格，如" 5"）
 *   - %H:%M: 24小时制时间（如"14:30"）
 */
void format_time(time_t mtime, char* time_str) {
  struct tm* st_tm = localtime(&mtime);
  if (!st_tm) {
    snprintf(time_str, 20, "InvalidTime");
    return;
  }
  strftime(time_str, 20, "%b %e %H:%M", st_tm);
}

/**
 * 比较函数：按文件名升序排序目录项（供qsort使用）
 * @param a 目录项指针的指针
 * @param b 目录项指针的指针
 * @return 比较结果（负数/0/正数）
 */
int compare_strings(const void* a, const void* b) {
  const struct dirent* const* pa = (const struct dirent* const*)a;
  const struct dirent* const* pb = (const struct dirent* const*)b;
  return strcmp((*pa)->d_name, (*pb)->d_name);
}

/**
* 读取并排序目录项（调用者需释放内存）
* 实现流程：
* 1. 打开目录并统计条目数量
* 2. 动态分配内存存储所有条目指针
* 3. 重读目录并填充数组
* 4. 使用qsort按文件名排序（升序）
*/
struct dirent** read_and_sort_dir(const char* dir_path, int* out_count) {
  DIR* dirp = opendir(dir_path);
  ERROR_CHECK(dirp, NULL, "opendir failed");

  // 统计目录项数量
  int count = 0;
  struct dirent* p;
  while ((p = readdir(dirp)) != NULL) count++;

  // 分配内存存储目录项指针
  struct dirent** entries = (struct dirent**)calloc(count, sizeof(struct dirent*));
  ERROR_CHECK(entries, NULL, "calloc failed");

  // 重置目录流并读取所有项
  rewinddir(dirp);
  for (int i = 0; i < count; i++) {
    entries[i] = readdir(dirp);
    ERROR_CHECK(entries[i], NULL, "readdir failed");
  }

  // 按文件名排序
  qsort(entries, count, sizeof(struct dirent*), compare_strings);

  closedir(dirp);
  *out_count = count;
  return entries;
}

/**
 * 打印单个文件/目录的详细信息（类似ls -l）
 * @param dent 目录项结构体指针
 * @param stat_buf 文件状态信息
*/
void print_file_info(const struct dirent* dent, const struct stat* stat_buf) {
  char type_mode[11];
  format_type_mode(stat_buf->st_mode, type_mode);

  // 获取用户/组名（处理空指针）
  struct passwd* pw = getpwuid(stat_buf->st_uid);
  char* username = pw ? pw->pw_name : "unknown";
  struct group* gr = getgrgid(stat_buf->st_gid);
  char* groupname = gr ? gr->gr_name : "unknown";

  // 格式化时间
  char time_str[20];
  format_time(stat_buf->st_mtime, time_str);

  // 输出（格式与ls -l一致）
  printf("%s %2lu %s %s %6lu %s %s\n",
    type_mode,
    (unsigned long)stat_buf->st_nlink,
    username,
    groupname,
    (unsigned long)stat_buf->st_size,
    time_str,
    dent->d_name);
}

int main(int argc, char* argv[]) {
    // 处理命令行参数
  const char* target_dir = (argc == 2) ? argv[1] : ".";

  // 读取并排序目录项
  int entry_count = 0;
  struct dirent** entries = read_and_sort_dir(target_dir, &entry_count);
  ERROR_CHECK(entries, NULL, "read_and_sort_dir failed");

  // 打印表头（类似ls -l）
  printf("total %d\n", entry_count);

  // 遍历并打印文件信息
  for (int i = 0; i < entry_count; i++) {
    const char* filename = entries[i]->d_name;
    struct stat stat_buf;

    // 跳过.和..
    if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
      continue;
    }

    // 获取文件状态（处理符号链接）
    int ret = lstat(filename, &stat_buf);
    if (ret == -1) {
      if (errno == ENOENT) {
        fprintf(stderr, "Warning: %s not found, skipping\n", filename);
        continue;
      }
      ERROR_CHECK(ret, -1, "lstat failed");
    }

    // 打印文件信息
    print_file_info(entries[i], &stat_buf);
  }

  // 清理资源
  free(entries);
  return 0;
}