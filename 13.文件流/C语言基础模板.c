#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define Maxsize 1024

void copy_file_char(const char *src_file, const char *dest_file) {
	int ret;
	while ((ret = fgetc(src_file)) != EOF) {
		fputc(ret, dest_file);  // ������ȡ����Ч�ַ�ʱд��
	}
}
void copy_file_line(const char *src_file, const char *dest_file) {
	char buf[Maxsize];
	while (fgets(buf, Maxsize,src_file) != NULL) {
		fputs(buf, dest_file);  // ������ȡ����Ч�ַ�ʱд��
	}
}
void binary_file_cpy(const char *src_file, const char *dest_file) {
	char buf[4096]; // 4KB��������ƽ��IOЧ�ʺ��ڴ�ռ�ã�
	size_t read_size; // ʵ�ʶ�ȡ���ֽ���
	while ((read_size = fread(buf, 1, sizeof(buf), src_file)) > 0) {
		// д��ʵ�ʶ�ȡ���ֽ������������һ�ζ�ȡ���㻺������Сʱ����
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
	if (dest_file == NULL) {  // ���Ŀ���ļ��Ƿ�򿪳ɹ�
		printf("Error: �޷���Ŀ���ļ�\n");
		fclose(src_file);  // �ر��Ѵ򿪵�Դ�ļ�
		return 1;
	}
	copy_file_line(src_file, dest_file);
	fclose(src_file);
	fclose(dest_file);
	return 0;
}