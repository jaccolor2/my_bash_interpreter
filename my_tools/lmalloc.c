// implement all the functions in dlist.h

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lmalloc.h"

struct lmalloc_item *lmalloc_item_init(void *malloc)
{
    struct lmalloc_item *node = malloc(sizeof(struct lmalloc_item));
    if (!node)
        return NULL;
    node->malloc = malloc;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Threshold 1.
struct lmalloc *lmalloc_init(void)
{
    struct lmalloc *list = malloc(sizeof(struct lmalloc));
    if (!list)
        return list;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_lmalloc(struct lmalloc *dlist)
{
    struct lmalloc_item *node = dlist->head;
    while (node)
    {
        struct lmalloc_item *temp = node;
        node = node->next;
        free(temp);
    }
    free(dlist);
}

void lmalloc_print(const struct lmalloc *list)
{
    if (list)
    {
        struct lmalloc_item *temp = list->head;
        while (temp)
        {
            printf("%p\n", temp->malloc);
            temp = temp->next;
        }
    }
    else
        return;
}

int lmalloc_push_front(struct lmalloc *list, void *malloc)
{
    struct lmalloc_item *node = lmalloc_item_init(malloc);
    if (!list->size && !list->head && !list->tail)
        list->head = node;
    else
    {
        list->tail = list->head;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->size++;
    return 1;
}

int lmalloc_push_back(struct lmalloc *list, void *malloc)
{
    struct lmalloc_item *node = lmalloc_item_init(malloc);

    if (!list->size && !list->head && !list->tail)
        list->head = node;
    else
    {
        struct lmalloc_item *temp = list->head;
        while (temp->next)
            temp = temp->next;
        temp->next = node;
        node->prev = temp;
    }
    list->size++;
    return 1;
}

struct lmalloc *lmalloc_copy(struct lmalloc *src)
{
    struct lmalloc *cpy = lmalloc_init();
    if (!cpy)
        return NULL;
    struct lmalloc_item *temp = src->head;
    while (temp)
    {
        lmalloc_push_back(cpy, temp->malloc);
        temp = temp->next;
    }
    return cpy;
}

size_t lmalloc_size(const struct lmalloc *list)
{
    if (!list)
        return 0;
    return list->size;
}

// Threshold 2.
void *lmalloc_get(struct lmalloc *list, size_t index)
{
    if (!list || index > list->size - 1)
        return "\0";
    struct lmalloc_item *tmp = list->head;
    size_t i = 0;
    while (i < index)
    {
        tmp = tmp->next;
        i++;
    }
    return tmp->malloc;
}


void lmalloc_print_back_and_forth(struct lmalloc *list)
{
    struct lmalloc_item *temp = list->head;
    while (temp->next)
    {
        printf("%p\n", temp->malloc);
        temp = temp->next;
    }
    printf("%p\n", temp->malloc);
    temp = temp->prev;
    while (temp)
    {
        printf("%p\n", temp->malloc);
        temp = temp->prev;
    }
}

int lmalloc_insert_at(struct lmalloc *list, void *malloc, size_t index)
{
    if (!list || index > list->size)
        return -1;
    if (!index)
    {
        lmalloc_push_front(list, malloc);
        return 1;
    }
    if (index == list->size - 1 || index == list->size)
    {
        lmalloc_push_back(list, malloc);
        return 1;
    }
    size_t prev_index = 0;
    size_t next_index = 0;
    struct lmalloc_item *temp1 = list->head;
    struct lmalloc_item *node = lmalloc_item_init(malloc);
    while (prev_index < index - 1)
    {
        temp1 = temp1->next;
        prev_index++;
    }
    struct lmalloc_item *temp2 = list->head;
    while (next_index < index)
    {
        temp2 = temp2->next;
        next_index++;
    }
    temp1->next = node;
    node->prev = temp1;
    temp2->prev = node;
    node->next = temp2;
    list->size++;
    return 1;
}

int my_strcmp(char *str1, char *str2)
{
    int i = 0;
    while(*(str1 + i) == *(str2 + i) && str1 && str2)
        i++;
    if (*(str1 + i) > *(str2 + i))
        return 1;
    if (*(str1 + i) < *(str2 + i))
        return -1;
    return 0;
}

int lmalloc_find(const struct lmalloc *list, void *malloc)
{
    if (!list)
        return -1;
    struct lmalloc_item *temp = list->head;
    size_t index = 0;
    while (my_strcmp(temp->malloc, malloc) && temp->next) // est-ce une str (pointeur sur char) ? non => adapter
    {
        temp = temp->next;
        index++;
    }
    if (index == list->size - 1)
    {
        if (my_strcmp(temp->token, token)) // pareil
            return -1;
        return index;
    }
    return index;
}

char *lmalloc_remove_at(struct lmalloc *list, size_t index)
{
    if (!list || index > list->size - 1)
        return "\0";
    size_t prev_index = 0;
    size_t next_index = 0;
    if (!index)
    {
        //struct dlist_item *node = list->head;
        list->head = list->head->next;
        list->tail = list->head->next->next;
        return "\0";
    }
    struct lmalloc_item *temp1 = list->head;
    while (prev_index < index - 1)
    {
        temp1 = temp1->next;
        prev_index++;
    }
    struct lmalloc_item *temp2 = list->head;
    while (next_index < index + 1)
    {
        temp2 = temp2->next;
        next_index++;
    }
    struct lmalloc_item *temp = temp1->next;
    temp1->next = temp2;
    temp2->prev = temp1;
    void *res = temp->malloc;
    free(temp);
    list->size--;
    return res;
}

// Threshold 3.

void lmalloc_reverse(struct lmalloc *list)
{
    struct lmalloc *new_dlist = lmalloc_init();
    struct lmalloc_item *temp = list->head;
    while (temp)
    {
        lmalloc_push_front(new_dlist, temp->malloc);
        temp = temp->next;
    }
    temp = list->head;
    struct lmalloc_item *temp_new_dlist = new_dlist->head;
    while (temp_new_dlist->next)
    {
        temp->malloc = temp_new_dlist->malloc;
        temp_new_dlist = temp_new_dlist->next;
        temp = temp->next;
    }
    temp->malloc = temp_new_dlist->malloc;
    free_sdlist(new_dlist);
}

// implement dlist_reverse

struct lmalloc *dlist_split_at(struct lmalloc *list, size_t index)
{
    struct lmalloc_item *temp = list->head;
    if (index >= list->size)
        return NULL;
    if (!list)
        return lmalloc_init();
    size_t i = 0;
    while (i < index)
    {
        temp = temp->next;
        i++;
    }
    struct lmalloc *second_half = lmalloc_init();
    second_half->head = temp;
    second_half->size = list->size - index;
    if (!second_half->head->next)
    {
        if (!temp->prev)
        {
            free(list);
            return second_half;
        }
        temp->prev->next = NULL;
        temp->prev = NULL;
        return second_half;
    }
    if (!temp->prev)
    {
        list->head = NULL;
        return second_half;
    }
    second_half->tail = second_half->head->next;
    temp->prev->next = NULL;
    temp->prev = NULL;
    list->size = index;
    return second_half;
}

void free_lmalloc_concat(struct lmalloc *list)
{
    struct lmalloc_item *node = list->head;
    while (node)
    {
        struct lmalloc_item *temp = node;
        node = node->next;
        free(temp);
        list->size--;
    }
}

void lmalloc_concat(struct lmalloc *list1, struct lmalloc *list2)
{
    if (!list1)
    {
        if (list2)
        {
            free_lmalloc_concat(list2);
            return;
        }
        return;
    }
    if (!list2)
        return;
    struct lmalloc_item *temp = list1->head;
    while (temp->next)
        temp = temp->next;
    struct lmalloc_item *temp2 = list2->head;
    struct lmalloc *new_list2 = lmalloc_init();
    if (!new_list2)
        return;
    while (temp2)
    {
        lmalloc_push_back(new_list2, temp2->malloc);
        temp2 = temp2->next;
    }
    free_lmalloc_concat(list2);
    temp->next = new_list2->head;
    new_list2->head->prev = temp;
    list1->size += new_list2->size;

    free(new_list2);
    return;
}