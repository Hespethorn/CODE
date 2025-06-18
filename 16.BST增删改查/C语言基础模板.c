#include "bst.h"
#include <stdio.h>

// 打印三种遍历结果的辅助函数
void print_traversals(BST* bst) {
  printf("先序遍历结果: ");
  bst_preorder(bst);
  printf("\n");

  printf("中序遍历结果: ");
  bst_inorder(bst);
  printf("\n");

  printf("后序遍历结果: ");
  bst_postorder(bst);
  printf("\n");
}

// 测试函数
void test_bst( ) {
    // 创建空BST
  BST* bst = bst_create( );
  if (!bst) {
    printf("创建BST失败\n");
    return;
  }

  // 测试插入操作
  int keys_to_insert[] = { 50, 30, 20, 40, 70, 60, 80 };
  int num_keys = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);
  for (int i = 0; i < num_keys; i++) {
    if (bst_insert(bst, keys_to_insert[i])) {
      printf("成功插入键: %d\n", keys_to_insert[i]);
      print_traversals(bst);
    }
    else {
      printf("插入键 %d 失败，键已存在\n", keys_to_insert[i]);
    }
  }

  // 测试重复插入
  if (!bst_insert(bst, 50)) {
    printf("成功检测到重复键 50，插入失败\n");
    print_traversals(bst);
  }

  // 测试搜索操作
  int keys_to_search[] = { 40, 90 };
  int num_search_keys = sizeof(keys_to_search) / sizeof(keys_to_search[0]);
  for (int i = 0; i < num_search_keys; i++) {
    TreeNode* result = bst_search(bst, keys_to_search[i]);
    if (result) {
      printf("找到键: %d\n", keys_to_search[i]);
    }
    else {
      printf("未找到键: %d\n", keys_to_search[i]);
    }
  }

  // 测试删除操作
  int keys_to_delete[] = { 20, 50, 100 };
  int num_delete_keys = sizeof(keys_to_delete) / sizeof(keys_to_delete[0]);
  for (int i = 0; i < num_delete_keys; i++) {
    if (bst_delete(bst, keys_to_delete[i])) {
      printf("成功删除键: %d\n", keys_to_delete[i]);
      print_traversals(bst);
    }
    else {
      printf("删除键 %d 失败，键不存在\n", keys_to_delete[i]);
    }
  }

  // 销毁BST
  bst_destroy(bst);
  printf("BST已成功销毁\n");
}

int main( ) {
  test_bst( );
  return 0;
}