/*
 * file_copy.c - 测试不同缓冲区大小对文件复制性能的影响
 *
 * 功能：将源文件（argv[1]）复制到目标文件（argv[2]），依次使用1KB、4KB、8KB、64KB、1MB的缓冲区。
 * 参数：./file_copy <source_file> <destination_file>
 * 依赖：标准库fcntl.h（open）、unistd.h（read/write/close）、stdlib.h（malloc/free/exit）、errno.h（错误码）。
 */

#include <fcntl.h>   // open
#include <unistd.h>  // read/write/close
#include <stdlib.h>  // exit/malloc/free
#include <errno.h>   // errno

#define ARGS_CHECK(arg, expected) \
    do { \
        if ((arg) != (expected)) { \
            fprintf(stderr, "Error: Expected %d arguments, got %d\n", (expected), (arg)); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

#define ERROR_CHECK(ret, error_val, msg) \
    do { \
        if ((ret) == (error_val)) { \
            fprintf(stderr, "Error: %s (errno=%d)\n", (msg), errno); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)


int main(int argc, char* argv[]) {
  ARGS_CHECK(argc, 3);  // 检查参数数量（第1行使用）

  // 打开源文件（作用域仅限当前函数）
  int src_fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(src_fd, -1, "open source file failed");

  // 打开目标文件（作用域仅限当前函数）
  int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  ERROR_CHECK(dest_fd, -1, "open destination file failed");

  // 测试不同缓冲区大小（明确作用域）
  const size_t buffer_sizes[] = { 1024, 4096, 8192, 65536, 1048576 };  // 1KB~1MB
  const int num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);

  for (int i = 0; i < num_buffer_sizes; i++) {
    const size_t current_buf_size = buffer_sizes[i];
    char* buf = malloc(current_buf_size);  // 动态分配当前大小的缓冲区
    ERROR_CHECK(buf, NULL, "malloc failed");  // 检查内存分配

    ssize_t bytes_read;  // 声明在循环内，最小作用域
    while ((bytes_read = read(src_fd, buf, current_buf_size)) > 0) {  // 正确处理返回值
      ssize_t bytes_written = write(dest_fd, buf, bytes_read);  // 实际写入字节数
      ERROR_CHECK(bytes_written, -1, "write failed");  // 检查写入错误
    }

    if (bytes_read == -1) {  // 处理read错误（非0且非-1的情况已由循环退出）
      ERROR_CHECK(-1, -1, "read failed");  // 冗余检查，仅为示例
    }

    free(buf);  // 及时释放内存
    buf = NULL;  // 避免野指针
  }

  close(src_fd);
  close(dest_fd);

  return 0;
}