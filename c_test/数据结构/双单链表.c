#include <stdlib.h>
#include <stdio.h>

// typedef struct list_node {
//     int data;
//     struct list_node *next;
// } list_node_t, *list_node_p;

typedef struct list_node {
    int data;
    struct list_node *next;
    struct list_node *prev;
} list_node_t, *list_node_p;

// // 创建一个节点
// list_node_p createNode(int val);
// // 释放一个节点
// void freeNode(list_node_p *node);
// // 创建一个所有元素为 0 的链表
// list_node_p createList(size_t size);
// // 求链表元素个数
// size_t countList(list_node_p list);
// // 一个个地为链表元素赋值
// void initList(list_node_p list);
// // 一次性赋值链表元素赋值
// void initListAll(list_node_p list);
// // 释放一个链表
// void freeList(list_node_p *list);
// // 打印一个链表
// void printList(list_node_p list);
// // 尾插
// void insertTail(list_node_p *list, int val);
// // 头插
// void insertHead(list_node_p *list, int val);
// // 随机插入
// void insert(list_node_p *list, int val, size_t idx);
// // 返回第一个
// void font(list_node_p list);
// // 返回最后一个
// void back(list_node_p list);
// // 返回索引
// void get(list_node_p list);
// // 删除第一个
// // 删除最后一个
// // 删除索引
// // 排序
// // void sort(list_node_p list) ;
// // 逆序
// // 反向排序
// // 有序合并
// // 是否有序
// // 无序合并

int main(int argc, char *argv[]) {

    // list_node_p list = createList(0);

    // insertHead(&list, 1);
    // insertHead(&list, 2);
    // insertHead(&list, 3);
    // insertHead(&list, 4);
    // insertHead(&list, 5);

    // insertTail(&list, 1);
    // insertTail(&list, 2);
    // insertTail(&list, 3);
    // insertTail(&list, 4);
    // insertTail(&list, 5);

    // insert(&list, 1, 0);
    // insert(&list, 2, 0);
    // insert(&list, 3, 1);
    // insert(&list, 4, 3);
    // insert(&list, 5, 1);

    // printList(list);

    // printf("%zu\n", countList(list));
    // initList(list);
    // initListAll(list);
    // freeList(&list);
    // printList(list);

    return 0;
}
// // 创建一个节点
// list_node_p createNode(int val) {
//     list_node_p node = (list_node_p)malloc(sizeof(list_node_t));
//     if (node == NULL) {
//         perror("malloc()");
//         return NULL;
//     }
//     node->next = NULL;
//     node->data = val;

//     return node;
// }

// // 释放一个节点
// void freeNode(list_node_p *node) {
//     if (node == NULL) {
//         return;
//     }
//     if (*node == NULL) {
//         return;
//     }
//     free(*node);
//     node = NULL;
// }

// // 创建一个所有元素为 0 的链表
// list_node_p createList(size_t size) {
//     list_node_p head = createNode(-1);
//     if (head == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return NULL;
//     }
//     list_node_p temp = head;

//     while (size--) {
//         list_node_p newNode = createNode(0);
//         if (newNode == NULL) {
//             fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//             return NULL;
//         }
//         temp->next = newNode;
//         temp = newNode;
//     }
//     temp = head->next;
//     freeNode(&head);
//     return temp;
// }

// // 求链表元素个数
// size_t countList(list_node_p list) {
//     size_t cnt = 0;
//     while (list) {
//         ++cnt;
//         list = list->next;
//     }
//     return cnt;
// }

// // 一个个地为链表元素赋值
// void initList(list_node_p list) {
//     int cnt = 1;
//     while (list) {
//         printf("请输入第 %d 个节点的值：", cnt++);
//         scanf("%d", &list->data);
//         list = list->next;
//     }
// }

// // 一次性为链表元素赋值
// void initListAll(list_node_p list) {
//     int cnt = countList(list);
//     printf("链表长度为 %d, 请一次性输入 %d 个整数，以空格分隔\n", cnt, cnt);
//     while (list) {
//         scanf("%d", &list->data);
//         list = list->next;
//     }
// }

// // 释放一个链表
// void freeList(list_node_p *list) {
//     while (*list) {
//         list_node_p temp = (*list)->next;
//         freeNode(list);
//         *list = temp;
//     }
// }

// // 打印一个链表
// void printList(list_node_p list) {
//     while (list) {
//         printf("%d ", list->data);
//         list = list->next;
//     }
//     printf("\n");
// }

// // 尾插
// void insertTail(list_node_p *list, int val) {
//     list_node_p head = createNode(-1);
//     if (head == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return;
//     }
//     list_node_p temp = head;
//     head->next = *list;
//     while (temp->next) {
//         temp = temp->next;
//     }
//     temp->next = createNode(val);
//     if (temp->next == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return;
//     }
//     *list = head->next;
//     freeNode(&head);
// }

// // 头插
// void insertHead(list_node_p *list, int val) {
//     list_node_p head = createNode(-1);

//     if (head == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return;
//     }
//     list_node_p newNode = createNode(val);
//     if (newNode == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return;
//     }

//     head->next = *list;
//     newNode->next = head->next;
//     head->next = newNode;
//     *list = head->next;
//     freeNode(&head);
// }

// // 随机插入
// void insert(list_node_p *list, int val, size_t idx) {
//     int count = countList(*list);
//     if (idx > count) {
//         fprintf(stderr, "越界辣: %d\n", __LINE__);
//         return;
//     }
//     list_node_p head = createNode(-1);
//     if (head == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return;
//     }
//     list_node_p temp = head;
//     head->next = *list;
//     for (size_t i = 0; i < idx; ++i) {
//         head = head->next;
//     }
//     list_node_p newNode = createNode(val);
//     if (newNode == NULL) {
//         fprintf(stderr, "创建节点失败: %d\n", __LINE__);
//         return;
//     }
//     newNode->next = head->next;
//     head->next = newNode;
//     *list = temp->next;
//     free(temp);
// }
