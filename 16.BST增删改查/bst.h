#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

typedef int KeyType;  // ������Ϊ����

// �����������ڵ�ṹ��
typedef struct node {
	KeyType key;          // �ڵ��ֵ��Ψһ��
	struct node *left;    // ������ָ��
	struct node *right;   // ������ָ��
} TreeNode;

// �����������ṹ�壨��װ���ڵ㣩
typedef struct {
	TreeNode *root;       // ���ڵ�ָ��
} BST;

// ����������������
BST *bst_create();                  // ������BST
bool bst_insert(BST *tree, KeyType key);  // �����½ڵ㣨��Ψһ��
TreeNode *bst_search(BST *tree, KeyType key);  // �����ڵ㣨���ؽڵ�ָ�룩
bool bst_delete(BST *tree, KeyType key);  // ɾ���ڵ㣨������ʱ�ɹ���
void bst_destroy(BST *tree);          // ����BST���ͷ������ڴ棩

void bst_preorder(BST *tree);
void bst_inorder(BST *tree);
void bst_postorder(BST *tree);

#endif