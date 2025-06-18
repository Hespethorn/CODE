#define _CRT_SECURE_NO_WARNINGS  // ���ñ�������ȫ���棨��scanf�Ĳ���ȫ��ʾ��
#include <stdio.h>               // ���������������printf��
#include <stdlib.h>              // �ڴ���亯������calloc��

typedef int ElementType;         // ��������洢����������Ϊint�����滻Ϊ�������ͣ�

// ����ڵ�ṹ�嶨��
typedef struct node {
    ElementType data;            // �����򣺴洢�ڵ�ֵ
    struct node *next;           // ָ����ָ����һ���ڵ��ָ��
} Node;                          // �ṹ��������򻯺������룩

// ͷ�巨�����½ڵ㣨������
void insert_head_null(Node **head, ElementType new_val) {
    Node *new_node = calloc(1, sizeof(Node));  // �����ڴ沢��ʼ��Ϊ0
    if (new_node == NULL) {                    // ����ڴ�����Ƿ�ɹ�
        printf("calloc failed in insert_head_null\n");
            return;
    }
    new_node->data = new_val;                  // �����½ڵ������
    new_node->next = *head;                    // �½ڵ��nextָ��ԭͷ�ڵ㣨*head���ⲿhead�ĵ�ǰֵ��
    *head = new_node;                          // �޸��ⲿhead��ָ������ָ���½ڵ㣬���ͷ�壩
}

// �޸�ͷ�ڵ�ֵ�����ʼ��ͷ�ڵ㣩
void modify_first_node(Node **head, ElementType new_val) {
    if (*head == NULL) {  // ����Ϊ��ʱ��ͷָ��ΪNULL��
        Node *new_node = (Node *)calloc(1, sizeof(Node));  // �����½ڵ�
        if (new_node == NULL) {
            printf("calloc failed in modify_first_node\n");
                return;
        }
        new_node->data = new_val;  // �½ڵ�������Ϊnew_val
        *head = new_node;          // ͷָ��ָ���½ڵ㣨��ʼ��ͷ�ڵ㣩
        return;
    }
    (*head)->data = new_val;  // ����ǿ�ʱ��ֱ���޸�ͷ�ڵ�����
}

// β�巨�����½ڵ㣨������
void insert_tail(Node **head, ElementType new_val) {
    Node *new_node = (Node *)calloc(1, sizeof(Node));  // �����ڴ�
    if (new_node == NULL) {
        printf("calloc failed in insert_tail\n");
            return;
    }
    new_node->data = new_val;       // �����½ڵ�����
    new_node->next = NULL;          // β�ڵ��next����ΪNULL���ؼ�����

    if (*head == NULL) {            // ����Ϊ��ʱ��ͷָ��ΪNULL��
        *head = new_node;           // ͷָ��ֱ��ָ���½ڵ㣨Ψһ�ڵ㣩
        return;
    }

    // ����ǿ�ʱ�����������һ���ڵ�
    Node *p = *head;                // pָ��ǰ�ڵ㣬��ʼΪͷ�ڵ�
    while (p->next != NULL) {       // ѭ��ֱ��p����һ���ڵ���NULL�����ҵ�β�ڵ㣩
        p = p->next;
    }
    p->next = new_node;             // β�ڵ��nextָ���½ڵ㣨���β�壩
}

// ��ӡ��������
void print_list(Node *head) {
    if (head == NULL) {  // ���������
        printf("����Ϊ��\n");
            return;
    }
    Node *p = head;      // pΪ����ָ�룬��ʼָ��ͷ�ڵ�
    while (p != NULL) {  // ѭ��ֱ��pΪNULL�����������нڵ㣩
        printf("%d -> ", p->data);  // ��ӡ��ǰ�ڵ�����
        p = p->next;    // p�ƶ�����һ���ڵ�
    }
    printf("NULL\n");     // ��ӡ���������־
}

int main(void) {
    Node *head = NULL;  // ��ʼ��������ͷָ��ΪNULL��

    // ����ͷ�巨+�޸�ͷ�ڵ�
    insert_head_null(&head, 7);    // ����7 �� ����7 -> NULL
    modify_first_node(&head, 8);   // �޸�ͷ�ڵ�Ϊ8 �� ����8 -> NULL
    insert_head_null(&head, 7);    // ͷ��7 �� ����7 -> 8 -> NULL
    insert_head_null(&head, 77);   // ͷ��77 �� ����77 -> 7 -> 8 -> NULL
    modify_first_node(&head, 888); // �޸�ͷ�ڵ�Ϊ888 �� ����888 -> 77 -> 7 -> 8 -> NULL

    // ����β�巨
    insert_tail(&head, 6);         // β��6 �� ����888 -> 77 -> 7 -> 8 -> 6 -> NULL

    // ��ӡ��������
    print_list(head);              // �����888 -> 77 -> 7 -> 8 -> 6 -> NULL

    // �ͷ������ڴ棨��ѡ����������ӣ�
    Node *p = head;
    while (p != NULL) {
        Node *temp = p;
        p = p->next;
        free(temp);
    }
    head = NULL;  // ����Ұָ��

    return 0;
}