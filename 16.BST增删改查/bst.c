#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// ������BST
BST *bst_create() {
    BST *bst = (BST *)malloc(sizeof(BST));
    if (!bst) {
        perror("BST�ڴ����ʧ��");
        exit(EXIT_FAILURE);
    }
    bst->root = NULL;  // ��ʼ���ڵ�Ϊ��
    return bst;
}

// �����������ݹ����ڵ㣨���ز�������������
static TreeNode *bst_insert_helper(TreeNode *node, KeyType key, bool *inserted) {
    if (!node) {  // ��λ�ò����½ڵ�
        TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
        if (!new_node) {
            perror("�½ڵ��ڴ����ʧ��");
            exit(EXIT_FAILURE);
        }
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        *inserted = true;  // ��ǲ���ɹ�
        return new_node;
    }

    if (key == node->key) {  // ���Ѵ��ڣ�����ʧ��
        *inserted = false;
        return node;
    }
    else if (key < node->key) {  // ����������
        node->left = bst_insert_helper(node->left, key, inserted);
    }
    else {  // ����������
        node->right = bst_insert_helper(node->right, key, inserted);
    }
    return node;
}

// �����½ڵ㣨��Ψһ��������ʧ�ܣ�
bool bst_insert(BST *tree, KeyType key) {
    if (!tree) return false;
    bool inserted = false;
    tree->root = bst_insert_helper(tree->root, key, &inserted);
    return inserted;
}

// �����������ݹ������ڵ�
static TreeNode *bst_search_helper(TreeNode *node, KeyType key) {
    if (!node) return NULL;  // ������δ�ҵ�
    if (key == node->key) {
        return node;  // �ҵ�Ŀ��ڵ�
    }
    else if (key < node->key) {
        return bst_search_helper(node->left, key);  // ����������
    }
    else {
        return bst_search_helper(node->right, key);  // ����������
    }
}

// �����ڵ㣨���ؽڵ�ָ�룬�����ڷ���NULL��
TreeNode *bst_search(BST *tree, KeyType key) {
    if (!tree) return NULL;
    return bst_search_helper(tree->root, key);
}

// ��������������nodeΪ������С�ڵ㣨����ڵ㣩
static TreeNode *bst_min(TreeNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}
// �����������ݹ�ɾ���ڵ㣨����ɾ�������������
static TreeNode *bst_delete_helper(TreeNode *node, KeyType key, bool *deleted) {
    if (!node) {  // δ�ҵ�Ŀ��ڵ�
        *deleted = false;
        return NULL;
    }

    if (key < node->key) {  // Ŀ����������
        node->left = bst_delete_helper(node->left, key, deleted);
    }
    else if (key > node->key) {  // Ŀ����������
        node->right = bst_delete_helper(node->right, key, deleted);
    }
    else {  // �ҵ�Ŀ��ڵ�
        *deleted = true;

        // ���1��Ҷ�ӽڵ��ֻ��һ���ӽڵ�
        if (!node->left) {  // ֻ����������������
            TreeNode *temp = node->right;
            free(node);  // �ͷŵ�ǰ�ڵ�
            return temp;  // ����������������ΪNULL��
        }
        else if (!node->right) {  // ֻ��������
            TreeNode *temp = node->left;
            free(node);  // �ͷŵ�ǰ�ڵ�
            return temp;  // ����������������ΪNULL��
        }

        // ���2���������ӽڵ㣨������������С�ڵ��滻��
        TreeNode *min_node = bst_min(node->right);  // ����������С�ڵ�
        node->key = min_node->key;  // �滻��ǰ�ڵ�ļ�
        // ɾ���������е���С�ڵ㣨�ݹ飩
        node->right = bst_delete_helper(node->right, min_node->key, deleted);
    }
    return node;
}

// ɾ���ڵ㣨������ʱ�ɹ���
bool bst_delete(BST *tree, KeyType key) {
    if (!tree) return false;
    bool deleted = false;
    tree->root = bst_delete_helper(tree->root, key, &deleted);
    return deleted;
}

// �����������ݹ��������нڵ�
static void bst_destroy_helper(TreeNode *node) {
    if (!node) return;
    bst_destroy_helper(node->left);   // ����������
    bst_destroy_helper(node->right);  // ����������
    free(node);                       // �ͷŵ�ǰ�ڵ�
}

// ����BST���ͷ������ڴ棩
void bst_destroy(BST *tree) {
    if (!tree) return;
    bst_destroy_helper(tree->root);  // �������нڵ�
    free(tree);                      // �ͷ�BST�ṹ��
}

// �������-�����������-��-�ң�
// ������������������ݹ���ģ�
static void bst_preorder_helper(TreeNode *node) {
    if (!node) return;  // �ݹ���ֹ��������ǰ�ڵ�Ϊ��
    printf("%d ", node->key);  // ���ʵ�ǰ�ڵ㣨����
    bst_preorder_helper(node->left);  // ����������
    bst_preorder_helper(node->right);  // ����������
}
void bst_preorder(BST *tree) {
    // ���������ڵ��Ƿ�Ϊ�գ������ָ�������
    if (!tree || !tree->root) return;
    // ���ø�����������ݹ�
    bst_preorder_helper(tree->root);
}

// ������������������ݹ���ģ�
static void bst_inorder_helper(TreeNode *node) {
    if (!node) return;
    bst_inorder_helper(node->left);  // ����������
    printf("%d ", node->key);  // ���ʵ�ǰ�ڵ㣨����
    bst_inorder_helper(node->right);  // ����������
}
// �������-�����������-��-�ң�
void bst_inorder(BST *tree) {
    if (!tree || !tree->root) return;
    bst_inorder_helper(tree->root);
}


// ������������������ݹ���ģ�
static void bst_postorder_helper(TreeNode *node) {
    if (!node) return;
    bst_postorder_helper(node->left);  // ����������
    bst_postorder_helper(node->right);  // ����������
    printf("%d ", node->key);  // ���ʵ�ǰ�ڵ㣨����
}
// �������-�����������-��-����
void bst_postorder(BST *tree) {
    if (!tree || !tree->root) return;
    bst_postorder_helper(tree->root);
}
