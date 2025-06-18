#define _CRT_SECURE_NO_WARNINGS  // 禁用编译器安全警告（如scanf的不安全提示）
#include <stdio.h>               // 输入输出函数（如printf）
#include <stdlib.h>              // 内存分配函数（如calloc）

typedef int ElementType;         // 定义链表存储的数据类型为int（可替换为其他类型）

// 链表节点结构体定义
typedef struct node {
    ElementType data;            // 数据域：存储节点值
    struct node *next;           // 指针域：指向下一个节点的指针
} Node;                          // 结构体别名（简化后续代码）

// 头插法插入新节点（修正后）
void insert_head_null(Node **head, ElementType new_val) {
    Node *new_node = calloc(1, sizeof(Node));  // 分配内存并初始化为0
    if (new_node == NULL) {                    // 检查内存分配是否成功
        printf("calloc failed in insert_head_null\n");
            return;
    }
    new_node->data = new_val;                  // 设置新节点的数据
    new_node->next = *head;                    // 新节点的next指向原头节点（*head是外部head的当前值）
    *head = new_node;                          // 修改外部head的指向（让它指向新节点，完成头插）
}

// 修改头节点值（或初始化头节点）
void modify_first_node(Node **head, ElementType new_val) {
    if (*head == NULL) {  // 链表为空时（头指针为NULL）
        Node *new_node = (Node *)calloc(1, sizeof(Node));  // 创建新节点
        if (new_node == NULL) {
            printf("calloc failed in modify_first_node\n");
                return;
        }
        new_node->data = new_val;  // 新节点数据设为new_val
        *head = new_node;          // 头指针指向新节点（初始化头节点）
        return;
    }
    (*head)->data = new_val;  // 链表非空时，直接修改头节点数据
}

// 尾插法插入新节点（修正后）
void insert_tail(Node **head, ElementType new_val) {
    Node *new_node = (Node *)calloc(1, sizeof(Node));  // 分配内存
    if (new_node == NULL) {
        printf("calloc failed in insert_tail\n");
            return;
    }
    new_node->data = new_val;       // 设置新节点数据
    new_node->next = NULL;          // 尾节点的next必须为NULL（关键！）

    if (*head == NULL) {            // 链表为空时（头指针为NULL）
        *head = new_node;           // 头指针直接指向新节点（唯一节点）
        return;
    }

    // 链表非空时，遍历到最后一个节点
    Node *p = *head;                // p指向当前节点，初始为头节点
    while (p->next != NULL) {       // 循环直到p的下一个节点是NULL（即找到尾节点）
        p = p->next;
    }
    p->next = new_node;             // 尾节点的next指向新节点（完成尾插）
}

// 打印链表内容
void print_list(Node *head) {
    if (head == NULL) {  // 处理空链表
        printf("链表为空\n");
            return;
    }
    Node *p = head;      // p为遍历指针，初始指向头节点
    while (p != NULL) {  // 循环直到p为NULL（遍历完所有节点）
        printf("%d -> ", p->data);  // 打印当前节点数据
        p = p->next;    // p移动到下一个节点
    }
    printf("NULL\n");     // 打印链表结束标志
}

int main(void) {
    Node *head = NULL;  // 初始化空链表（头指针为NULL）

    // 测试头插法+修改头节点
    insert_head_null(&head, 7);    // 插入7 → 链表：7 -> NULL
    modify_first_node(&head, 8);   // 修改头节点为8 → 链表：8 -> NULL
    insert_head_null(&head, 7);    // 头插7 → 链表：7 -> 8 -> NULL
    insert_head_null(&head, 77);   // 头插77 → 链表：77 -> 7 -> 8 -> NULL
    modify_first_node(&head, 888); // 修改头节点为888 → 链表：888 -> 77 -> 7 -> 8 -> NULL

    // 测试尾插法
    insert_tail(&head, 6);         // 尾插6 → 链表：888 -> 77 -> 7 -> 8 -> 6 -> NULL

    // 打印最终链表
    print_list(head);              // 输出：888 -> 77 -> 7 -> 8 -> 6 -> NULL

    // 释放链表内存（可选，但建议添加）
    Node *p = head;
    while (p != NULL) {
        Node *temp = p;
        p = p->next;
        free(temp);
    }
    head = NULL;  // 避免野指针

    return 0;
}