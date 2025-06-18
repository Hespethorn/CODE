/**
 * directory_lister.c - ���� `ls -l` ��Ŀ¼�б����
 *
 * ����ܹ���
 * 1. �������������������в�����ȷ��Ŀ��Ŀ¼
 * 2. Ŀ¼ɨ�裺��ȡĿ¼�����
 * 3. Ԫ���ݻ�ȡ��ͨ��lstat��ȡÿ���ļ�����ϸ��Ϣ
 * 4. ��ʽ�����������ls -l�ĸ�ʽչʾ���
 *
 * ��ȫע�����
 * - ʹ��calloc����mallocȷ���ڴ��ʼ��Ϊ0
 * - �����ַ�������ʹ��snprintf/strftime���⻺�������
 */

// Cϵͳ��ͷ�ļ���������������������У�
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

/* �궨�壺�����飨Google���do-while(0)�ṹ�� */
#define ERROR_CHECK(ret, error_val, msg) \
do { \
    if ((ret) == (error_val)) { \
        fprintf(stderr, "Error: %s (errno=%d)\n", (msg), errno); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

/**
 * ��ʽ���ļ����ͺ�Ȩ���ַ������� "-rwxr-xr-x"��
 * @param mode �ļ�ģʽ������lstat.st_mode��
 * @param tm_str ���������������11�ֽڣ�����ֹ����
 *
 * ʵ��ϸ�ڣ�
 * - ʹ�ñ�׼�꣨��S_IRUSR������λ����Ӳ���룬��߿ɶ���
 * - ����Ȩ��λ��SUID/SGID/Sticky�������߼���
 *   - ��ִ��λ��������ʾСд��ĸ����'s'��'t'��
 *   - ��ִ��λ�رգ���ʾ��д��ĸ����'S'��'T'��
 */
void format_type_mode(mode_t mode, char* tm_str) {
   // �ļ����ʹ���
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

  // Ȩ��λ����ʹ�ñ�׼����߿ɶ��ԣ�
  tm_str[1] = (mode & S_IRUSR) ? 'r' : '-';  // �û���
  tm_str[2] = (mode & S_IWUSR) ? 'w' : '-';  // �û�д
  tm_str[3] = (mode & S_IXUSR) ? 'x' : '-';  // �û�ִ��
  tm_str[4] = (mode & S_IRGRP) ? 'r' : '-';  // ���
  tm_str[5] = (mode & S_IWGRP) ? 'w' : '-';  // ��д
  tm_str[6] = (mode & S_IXGRP) ? 'x' : '-';  // ��ִ��
  tm_str[7] = (mode & S_IROTH) ? 'r' : '-';  // ������
  tm_str[8] = (mode & S_IWOTH) ? 'w' : '-';  // ����д
  tm_str[9] = (mode & S_IXOTH) ? 'x' : '-';  // ����ִ��

  // ����Ȩ��λ˵����
// - S_ISUID: ִ��ʱ�����û�ID����/bin/su��
// - S_ISGID: ִ��ʱ������ID����ĳЩ����Ŀ¼��
// - S_ISVTX: ճ��λ����/tmpĿ¼�ķ�ɾ��������
  if (mode & S_ISUID) tm_str[2] = (tm_str[2] == '-') ? 's' : 'S';
  if (mode & S_ISUID) tm_str[2] = (tm_str[2] == '-') ? 's' : 'S';
  if (mode & S_ISGID) tm_str[5] = (tm_str[5] == '-') ? 's' : 'S';
  if (mode & S_ISVTX) tm_str[8] = (tm_str[8] == '-') ? 't' : 'T';

  tm_str[10] = '\0';  // ��ֹ��
}

/**
 * ��ʽ��ʱ��Ϊ"Mon dd HH:MM"���� "Jul  5 14:30"��
 * @param mtime �ļ��޸�ʱ���������lstat.st_mtime��
 * @param time_str ���������������20�ֽڣ�
 *
 * ע�����
 * - localtime���̰߳�ȫ�����̻߳��������localtime_r��
 * - strftime��ʽ˵����
 *   - %b: �·���д����"Jan"��
 *   - %e: ���ڣ���ǰ���ո���" 5"��
 *   - %H:%M: 24Сʱ��ʱ�䣨��"14:30"��
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
 * �ȽϺ��������ļ�����������Ŀ¼���qsortʹ�ã�
 * @param a Ŀ¼��ָ���ָ��
 * @param b Ŀ¼��ָ���ָ��
 * @return �ȽϽ��������/0/������
 */
int compare_strings(const void* a, const void* b) {
  const struct dirent* const* pa = (const struct dirent* const*)a;
  const struct dirent* const* pb = (const struct dirent* const*)b;
  return strcmp((*pa)->d_name, (*pb)->d_name);
}

/**
* ��ȡ������Ŀ¼����������ͷ��ڴ棩
* ʵ�����̣�
* 1. ��Ŀ¼��ͳ����Ŀ����
* 2. ��̬�����ڴ�洢������Ŀָ��
* 3. �ض�Ŀ¼���������
* 4. ʹ��qsort���ļ�����������
*/
struct dirent** read_and_sort_dir(const char* dir_path, int* out_count) {
  DIR* dirp = opendir(dir_path);
  ERROR_CHECK(dirp, NULL, "opendir failed");

  // ͳ��Ŀ¼������
  int count = 0;
  struct dirent* p;
  while ((p = readdir(dirp)) != NULL) count++;

  // �����ڴ�洢Ŀ¼��ָ��
  struct dirent** entries = (struct dirent**)calloc(count, sizeof(struct dirent*));
  ERROR_CHECK(entries, NULL, "calloc failed");

  // ����Ŀ¼������ȡ������
  rewinddir(dirp);
  for (int i = 0; i < count; i++) {
    entries[i] = readdir(dirp);
    ERROR_CHECK(entries[i], NULL, "readdir failed");
  }

  // ���ļ�������
  qsort(entries, count, sizeof(struct dirent*), compare_strings);

  closedir(dirp);
  *out_count = count;
  return entries;
}

/**
 * ��ӡ�����ļ�/Ŀ¼����ϸ��Ϣ������ls -l��
 * @param dent Ŀ¼��ṹ��ָ��
 * @param stat_buf �ļ�״̬��Ϣ
*/
void print_file_info(const struct dirent* dent, const struct stat* stat_buf) {
  char type_mode[11];
  format_type_mode(stat_buf->st_mode, type_mode);

  // ��ȡ�û�/�����������ָ�룩
  struct passwd* pw = getpwuid(stat_buf->st_uid);
  char* username = pw ? pw->pw_name : "unknown";
  struct group* gr = getgrgid(stat_buf->st_gid);
  char* groupname = gr ? gr->gr_name : "unknown";

  // ��ʽ��ʱ��
  char time_str[20];
  format_time(stat_buf->st_mtime, time_str);

  // �������ʽ��ls -lһ�£�
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
    // ���������в���
  const char* target_dir = (argc == 2) ? argv[1] : ".";

  // ��ȡ������Ŀ¼��
  int entry_count = 0;
  struct dirent** entries = read_and_sort_dir(target_dir, &entry_count);
  ERROR_CHECK(entries, NULL, "read_and_sort_dir failed");

  // ��ӡ��ͷ������ls -l��
  printf("total %d\n", entry_count);

  // ��������ӡ�ļ���Ϣ
  for (int i = 0; i < entry_count; i++) {
    const char* filename = entries[i]->d_name;
    struct stat stat_buf;

    // ����.��..
    if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
      continue;
    }

    // ��ȡ�ļ�״̬������������ӣ�
    int ret = lstat(filename, &stat_buf);
    if (ret == -1) {
      if (errno == ENOENT) {
        fprintf(stderr, "Warning: %s not found, skipping\n", filename);
        continue;
      }
      ERROR_CHECK(ret, -1, "lstat failed");
    }

    // ��ӡ�ļ���Ϣ
    print_file_info(entries[i], &stat_buf);
  }

  // ������Դ
  free(entries);
  return 0;
}