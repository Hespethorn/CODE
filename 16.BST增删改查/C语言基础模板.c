#include "bst.h"
#include <stdio.h>

// ��ӡ���ֱ�������ĸ�������
void print_traversals(BST* bst) {
  printf("����������: ");
  bst_preorder(bst);
  printf("\n");

  printf("����������: ");
  bst_inorder(bst);
  printf("\n");

  printf("����������: ");
  bst_postorder(bst);
  printf("\n");
}

// ���Ժ���
void test_bst( ) {
    // ������BST
  BST* bst = bst_create( );
  if (!bst) {
    printf("����BSTʧ��\n");
    return;
  }

  // ���Բ������
  int keys_to_insert[] = { 50, 30, 20, 40, 70, 60, 80 };
  int num_keys = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
  for (int i = 0; i < num_keys; i++) {
    if (bst_insert(bst, keys_to_insert[i])) {
      printf("�ɹ������: %d\n", keys_to_insert[i]);
      print_traversals(bst);
    }
    else {
      printf("����� %d ʧ�ܣ����Ѵ���\n", keys_to_insert[i]);
    }
  }

  // �����ظ�����
  if (!bst_insert(bst, 50)) {
    printf("�ɹ���⵽�ظ��� 50������ʧ��\n");
    print_traversals(bst);
  }

  // ������������
  int keys_to_search[] = { 40, 90 };
  int num_search_keys = sizeof(keys_to_search) / sizeof(keys_to_search[0]);
  for (int i = 0; i < num_search_keys; i++) {
    TreeNode* result = bst_search(bst, keys_to_search[i]);
    if (result) {
      printf("�ҵ���: %d\n", keys_to_search[i]);
    }
    else {
      printf("δ�ҵ���: %d\n", keys_to_search[i]);
    }
  }

  // ����ɾ������
  int keys_to_delete[] = { 20, 50, 100 };
  int num_delete_keys = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
  for (int i = 0; i < num_delete_keys; i++) {
    if (bst_delete(bst, keys_to_delete[i])) {
      printf("�ɹ�ɾ����: %d\n", keys_to_delete[i]);
      print_traversals(bst);
    }
    else {
      printf("ɾ���� %d ʧ�ܣ���������\n", keys_to_delete[i]);
    }
  }

  // ����BST
  bst_destroy(bst);
  printf("BST�ѳɹ�����\n");
}

int main( ) {
  test_bst( );
  return 0;
}