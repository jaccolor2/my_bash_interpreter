#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>

struct sdlist_item
{
    char *token;
    struct sdlist_item *next;
    struct sdlist_item *prev;
};

struct sdlist
{
    size_t size;
    struct sdlist_item *head;
    struct sdlist_item *tail;
};

// Threshold 1.
struct sdlist *sdlist_init(void);
void sdlist_print(const struct sdlist *list);
int sdlist_push_front(struct sdlist *list, char *token);
int sdlist_push_back(struct sdlist *list, char *token);
size_t sdlist_size(const struct sdlist *list);

// Threshold 2.
char *sdlist_get(struct sdlist *list, size_t index);
int sdlist_insert_at(struct sdlist *list, char *token, size_t index);
int sdlist_find(const struct sdlist *list, char *token);
char *sdlist_remove_at(struct sdlist *list, size_t index);

// Threshold 3.
void sdlist_reverse(struct sdlist *list);
struct sdlist *sdlist_split_at(struct sdlist *list, size_t index);
void sdlist_concat(struct sdlist *list1, struct sdlist *list2);

// else

void free_dlist(struct sdlist *list);
void dlist_print_back_and_forth(struct sdlist *list);
#endif // DLIST_H
