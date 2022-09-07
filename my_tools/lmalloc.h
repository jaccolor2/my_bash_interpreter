#ifndef LMALLOC_H
#define LMALLOC_H

#include <stddef.h>

struct lmalloc_item
{
    void *malloc;
    struct lmalloc_item *next;
    struct lmalloc_item *prev;
};

struct lmalloc
{
    size_t size;
    struct lmalloc_item *head;
    struct lmalloc_item *tail;
};

// Threshold 1.
struct lmalloc *lmalloc_init(void);
void lmalloc_print(const struct lmalloc *list);
int lmalloc_push_front(struct lmalloc *list, char *token);
int lmalloc_push_back(struct lmalloc *list, char *token);
size_t lmalloc_size(const struct lmalloc *list);

// Threshold 2.
char *lmalloc_get(struct lmalloc *list, size_t index);
int lmalloc_insert_at(struct lmalloc *list, char *token, size_t index);
int lmalloc_find(const struct lmalloc *list, char *token);
char *lmalloc_remove_at(struct lmalloc *list, size_t index);

// Threshold 3.
void lmalloc_reverse(struct lmalloc *list);
struct lmalloc *lmalloc_split_at(struct lmalloc *list, size_t index);
void lmalloc_concat(struct lmalloc *list1, struct lmalloc *list2);

// else

void free_lmalloc(struct lmalloc *list);
void lmalloc_print_back_and_forth(struct lmalloc *list);

#endif