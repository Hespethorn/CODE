#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// 创建空BST
BST *bst_create() {
    BST *bst = (BST *)malloc(sizeof(BST));
    if (!bst) {
        perror("BST内存分配失败");
        exit(EXIT_FAILURE);
    }
    bst->root = NULL;  // 初始根节点为空
    return bst;
}

// 辅助函数：递归插入节点（返回插入后的子树根）
static TreeNode *bst_insert_helper(TreeNode *node, KeyType key, bool *inserted) {
    if (!node) {  // 空位置插入新节点
        TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
        if (!new_node) {
            perror("新节点内存分配失败");
            exit(EXIT_FAILURE);
        }
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        *inserted = true;  // 标记插入成功
        return new_node;
    }

    if (key == node->key) {  // 键已存在，插入失败
        *inserted = false;
        return node;
    }
    else if (key < node->key) {  // 插入左子树
        node->left = bst_insert_helper(node->left, key, inserted);
    }
    else {  // 插入右子树
        node->right = bst_insert_helper(node->right, key, inserted);
    }
    return node;
}

// 插入新节点（键唯一，存在则失败）
bool bst_insert(BST *tree, KeyType key) {
    if (!tree) return false;
    bool inserted = false;
    tree->root = bst_insert_helper(tree->root, key, &inserted);
    return inserted;
}

// 辅助函数：递归搜索节点
static TreeNode *bst_search_helper(TreeNode *node, KeyType key) {
    if (!node) return NULL;  // 空树或未找到
    if (key == node->key) {
        return node;  // 找到目标节点
    }
    else if (key < node->key) {
        return bst_search_helper(node->left, key);  // 搜索左子树
    }
    else {
        return bst_search_helper(node->right, key);  // 搜索右子树
    }
}

// 搜索节点（返回节点指针，不存在返回NULL）
TreeNode *bst_search(BST *tree, KeyType key) {
    if (!tree) return NULL;
    return bst_search_helper(tree->root, key);
}

// 辅助函数：找以node为根的最小节点（最左节点）
static TreeNode *bst_min(TreeNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}
// 辅助函数：递归删除节点（返回删除后的子树根）
static TreeNode *bst_delete_helper(TreeNode *node, KeyType key, bool *deleted) {
    if (!node) {  // 未找到目标节点
        *deleted = false;
        return NULL;
    }

    if (key < node->key) {  // 目标在左子树
        node->left = bst_delete_helper(node->left, key, deleted);
    }
    else if (key > node->key) {  // 目标在右子树
        node->right = bst_delete_helper(node->right, key, deleted);
    }
    else {  // 找到目标节点
        *deleted = true;

        // 情况1：叶子节点或只有一个子节点
        if (!node->left) {  // 只有右子树或无子树
            TreeNode *temp = node->right;
            free(node);  // 释放当前节点
            return temp;  // 返回右子树（可能为NULL）
        }
        else if (!node->right) {  // 只有左子树
            TreeNode *temp = node->left;
            free(node);  // 释放当前节点
            return temp;  // 返回左子树（可能为NULL）
        }

        // 情况2：有两个子节点（找右子树的最小节点替换）
        TreeNode *min_node = bst_min(node->right);  // 找右子树最小节点
        node->key = min_node->key;  // 替换当前节点的键
        // 删除右子树中的最小节点（递归）
        node->right = bst_delete_helper(node->right, min_node->key, deleted);
    }
    return node;
}

// 删除节点（键存在时成功）
bool bst_delete(BST *tree, KeyType key) {
    if (!tree) return false;
    bool deleted = false;
    tree->root = bst_delete_helper(tree->root, key, &deleted);
    return deleted;
}

// 辅助函数：递归销毁所有节点
static void bst_destroy_helper(TreeNode *node) {
    if (!node) return;
    bst_destroy_helper(node->left);   // 销毁左子树
    bst_destroy_helper(node->right);  // 销毁右子树
    free(node);                       // 释放当前节点
}

// 销毁BST（释放所有内存）
void bst_destroy(BST *tree) {
    if (!tree) return;
    bst_destroy_helper(tree->root);  // 销毁所有节点
    free(tree);                      // 释放BST结构体
}

// 深度优先-先序遍历（根-左-右）
// 先序遍历辅助函数（递归核心）
static void bst_preorder_helper(TreeNode *node) {
    if (!node) return;  // 递归终止条件：当前节点为空
    printf("%d ", node->key);  // 访问当前节点（根）
    bst_preorder_helper(node->left);  // 遍历左子树
    bst_preorder_helper(node->right);  // 遍历右子树
}
void bst_preorder(BST *tree) {
    // 检查树或根节点是否为空，避免空指针解引用
    if (!tree || !tree->root) return;
    // 调用辅助函数处理递归
    bst_preorder_helper(tree->root);
}

// 中序遍历辅助函数（递归核心）
static void bst_inorder_helper(TreeNode *node) {
    if (!node) return;
    bst_inorder_helper(node->left);  // 遍历左子树
    printf("%d ", node->key);  // 访问当前节点（根）
    bst_inorder_helper(node->right);  // 遍历右子树
}
// 深度优先-中序遍历（左-根-右）
void bst_inorder(BST *tree) {
    if (!tree || !tree->root) return;
    bst_inorder_helper(tree->root);
}


// 后序遍历辅助函数（递归核心）
static void bst_postorder_helper(TreeNode *node) {
    if (!node) return;
    bst_postorder_helper(node->left);  // 遍历左子树
    bst_postorder_helper(node->right);  // 遍历右子树
    printf("%d ", node->key);  // 访问当前节点（根）
}
// 深度优先-后序遍历（左-右-根）
void bst_postorder(BST *tree) {
    if (!tree || !tree->root) return;
    bst_postorder_helper(tree->root);
}
