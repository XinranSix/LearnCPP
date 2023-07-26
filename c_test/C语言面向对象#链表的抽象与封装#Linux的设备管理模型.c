#include <stdio.h>

struct list_head {
    struct list_head *next, *prev;
};

void INIT_LIST_HEAD(struct list_head *list);
int list_empty(const struct list_head *head);
void list_add(struct list_head *new, struct list_head *head);
void list_del(struct list_head *entry);
void list_replace(struct list_head *old, struct list_head *new);
void list_move(struct list_head *list, struct list_head *head);

struct my_list_node {
    int data;
    struct list_head list;
};

struct kobject {
    const char *name;
    struct list_head entry;
    struct kobject *parent;
    struct kset *kset;
    struct kobj_type *ktype;
    struct kernfs_node *sd;
    // struct kref kref;
};

int main() { return 0; }
