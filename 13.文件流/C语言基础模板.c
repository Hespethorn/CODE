#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define Maxsize 1024

void copy_file_char(const char *src_file, const char *dest_file) {
	int ret;
	while ((ret = fgetc(src_file)) != EOF) {
		fputc(ret, dest_file);  // 仅当读取到有效字符时写入
	}
}
void copy_file_line(const char *src_file, const char *dest_file) {
	char buf[Maxsize];
	while (fgets(buf, Maxsize,src_file) != NULL) {
		fputs(buf, dest_file);  // 仅当读取到有效字符时写入
	}
}
void binary_file_cpy(const char *src_file, const char *dest_file) {
	char buf[4096]; // 4KB缓冲区（平衡IO效率和内存占用）
	size_t read_size; // 实际读取的字节数
	while ((read_size = fread(buf, 1, sizeof(buf), src_file)) > 0) {
		// 写入实际读取的字节数（避免最后一次读取不足缓冲区大小时出错）
		fwrite(buf, 1, read_size, dest_file);
	}
}
int main(void) {
	FILE *src_file = fopen("1.txt", "rb");
	if (src_file == NULL) {
		printf("Error");
		return;
	}
	FILE *dest_file = fopen("1_copy.txt", "wb");
	if (dest_file == NULL) {  // 检查目标文件是否打开成功
		printf("Error: 无法打开目标文件\n");
		fclose(src_file);  // 关闭已打开的源文件
		return 1;
	}
	copy_file_line(src_file, dest_file);
	fclose(src_file);
	fclose(dest_file);
	return 0;
}