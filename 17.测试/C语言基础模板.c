/*
 * file_copy.c - ���Բ�ͬ��������С���ļ��������ܵ�Ӱ��
 *
 * ���ܣ���Դ�ļ���argv[1]�����Ƶ�Ŀ���ļ���argv[2]��������ʹ��1KB��4KB��8KB��64KB��1MB�Ļ�������
 * ������./file_copy <source_file> <destination_file>
 * ��������׼��fcntl.h��open����unistd.h��read/write/close����stdlib.h��malloc/free/exit����errno.h�������룩��
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
  ARGS_CHECK(argc, 3);  // ��������������1��ʹ�ã�

  // ��Դ�ļ�����������޵�ǰ������
  int src_fd = open(argv[1], O_RDONLY);
  ERROR_CHECK(src_fd, -1, "open source file failed");

  // ��Ŀ���ļ�����������޵�ǰ������
  int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
  ERROR_CHECK(dest_fd, -1, "open destination file failed");

  // ���Բ�ͬ��������С����ȷ������
  const size_t buffer_sizes[] = { 1024, 4096, 8192, 65536, 1048576 };  // 1KB~1MB
  const int num_buffer_sizes = sizeof(buffer_sizes) / sizeof(buffer_sizes[0]);

  for (int i = 0; i < num_buffer_sizes; i++) {
    const size_t current_buf_size = buffer_sizes[i];
    char* buf = malloc(current_buf_size);  // ��̬���䵱ǰ��С�Ļ�����
    ERROR_CHECK(buf, NULL, "malloc failed");  // ����ڴ����

    ssize_t bytes_read;  // ������ѭ���ڣ���С������
    while ((bytes_read = read(src_fd, buf, current_buf_size)) > 0) {  // ��ȷ������ֵ
      ssize_t bytes_written = write(dest_fd, buf, bytes_read);  // ʵ��д���ֽ���
      ERROR_CHECK(bytes_written, -1, "write failed");  // ���д�����
    }

    if (bytes_read == -1) {  // ����read���󣨷�0�ҷ�-1���������ѭ���˳���
      ERROR_CHECK(-1, -1, "read failed");  // �����飬��Ϊʾ��
    }

    free(buf);  // ��ʱ�ͷ��ڴ�
    buf = NULL;  // ����Ұָ��
  }

  close(src_fd);
  close(dest_fd);

  return 0;
}