#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

typedef int KeyType;  // 键类型为整数

// 二叉搜索树节点结构体
typedef struct node {
	KeyType key;          // 节点键值（唯一）
	struct node *left;    // 左子树指针
	struct node *right;   // 右子树指针
} TreeNode;

// 二叉搜索树结构体（封装根节点）
typedef struct {
	TreeNode *root;       // 根节点指针
} BST;

// 基础操作函数声明
BST *bst_create();                  // 创建空BST
bool bst_insert(BST *tree, KeyType key);  // 插入新节点（键唯一）
TreeNode *bst_search(BST *tree, KeyType key);  // 搜索节点（返回节点指针）
bool bst_delete(BST *tree, KeyType key);  // 删除节点（键存在时成功）
void bst_destroy(BST *tree);          // 销毁BST（释放所有内存）

void bst_preorder(BST *tree);
void bst_inorder(BST *tree);
void bst_postorder(BST *tree);

#endif