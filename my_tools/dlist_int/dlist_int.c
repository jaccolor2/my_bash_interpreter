// implement all the functions in dlist.h

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

struct dlist_item *dlist_item_init(int element)
{
    struct dlist_item *node = malloc(sizeof(struct dlist_item));
    if (!node)
    {
        return NULL;
    }
    node->data = element;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Threshold 1.
struct dlist *dlist_init(void)
{
    struct dlist *list = malloc(sizeof(struct dlist));
    if (!list)
    {
        return list;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_dlist(struct dlist *dlist)
{
    struct dlist_item *node = dlist->head;
    while (node)
    {
        struct dlist_item *temp = node;
        node = node->next;
        free(temp);
    }
    free(dlist);
}

void dlist_print(const struct dlist *list)
{
    if (list)
    {
        struct dlist_item *temp = list->head;
        while (temp)
        {
            printf("%d\n", temp->data);
            temp = temp->next;
        }
    }
    else
        return;
}

int dlist_push_front(struct dlist *list, int element)
{
    struct dlist_item *node = dlist_item_init(element);
    if (!list->size && !list->head && !list->tail)
    {
        list->head = node;
    }
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

int dlist_push_back(struct dlist *list, int element)
{
    struct dlist_item *node = dlist_item_init(element);

    if (!list->size && !list->head && !list->tail)
    {
        list->head = node;
    }
    else
    {
        struct dlist_item *temp = list->head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
    list->size++;
    return 1;
}

struct dlist *dlist_copy(struct dlist *src)
{
    struct dlist *cpy = dlist_init();
    if (!cpy)
    {
        return NULL;
    }
    struct dlist_item *temp = src->head;
    while (temp)
    {
        dlist_push_back(cpy, temp->data);
        temp = temp->next;
    }
    return cpy;
}

size_t dlist_size(const struct dlist *list)
{
    if (!list)
    {
        return 0;
    }
    return list->size;
}

// Threshold 2.
int dlist_get(struct dlist *list, size_t index)
{
    if (!list || index > list->size - 1)
    {
        return -1;
    }
    struct dlist_item *tmp = list->head;
    size_t i = 0;
    while (i < index)
    {
        tmp = tmp->next;
        i++;
    }
    return tmp->data;
}

void dlist_print_back_and_forth(struct dlist *list)
{
    struct dlist_item *temp = list->head;
    while (temp->next)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
    temp = temp->prev;
    while (temp)
    {
        printf("%d\n", temp->data);
        temp = temp->prev;
    }
}

int dlist_insert_at(struct dlist *list, int element, size_t index)
{
    if (!list || index > list->size)
    {
        return -1;
    }
    if (!index)
    {
        dlist_push_front(list, element);
        return 1;
    }
    if (index == list->size - 1 || index == list->size)
    {
        dlist_push_back(list, element);
        return 1;
    }
    size_t prev_index = 0;
    size_t next_index = 0;
    struct dlist_item *temp1 = list->head;
    struct dlist_item *node = dlist_item_init(element);
    while (prev_index < index - 1)
    {
        temp1 = temp1->next;
        prev_index++;
    }
    struct dlist_item *temp2 = list->head;
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

int dlist_find(const struct dlist *list, int element)
{
    if (!list)
    {
        return -1;
    }
    struct dlist_item *temp = list->head;
    size_t index = 0;
    while (temp->data != element && temp->next)
    {
        temp = temp->next;
        index++;
    }
    if (index == list->size - 1)
    {
        if (temp->data != element)
            return -1;
        return index;
    }
    return index;
}

int dlist_remove_at(struct dlist *list, size_t index)
{
    if (!list || index > list->size - 1)
    {
        return -1;
    }
    size_t prev_index = 0;
    size_t next_index = 0;
    if (!index)
    {
        //struct dlist_item *node = list->head;
        list->head = list->head->next;
        list->tail = list->head->next->next;
        return 0;
    }
    struct dlist_item *temp1 = list->head;
    while (prev_index < index - 1)
    {
        temp1 = temp1->next;
        prev_index++;
    }
    struct dlist_item *temp2 = list->head;
    while (next_index < index + 1)
    {
        temp2 = temp2->next;
        next_index++;
    }
    struct dlist_item *temp = temp1->next;
    temp1->next = temp2;
    temp2->prev = temp1;
    int res = temp->data;
    free(temp);
    list->size--;
    return res;
}

// Threshold 3.

void dlist_map_square(struct dlist *list)
{
    struct dlist_item *temp = list->head;
    while (temp)
    {
        temp->data *= temp->data;
        temp = temp->next;
    }
}

void dlist_reverse(struct dlist *list)
{
    struct dlist *new_dlist = dlist_init();
    struct dlist_item *temp = list->head;
    while (temp)
    {
        dlist_push_front(new_dlist, temp->data);
        temp = temp->next;
    }
    temp = list->head;
    struct dlist_item *temp_new_dlist = new_dlist->head;
    while (temp_new_dlist->next)
    {
        temp->data = temp_new_dlist->data;
        temp_new_dlist = temp_new_dlist->next;
        temp = temp->next;
    }
    temp->data = temp_new_dlist->data;
    free_dlist(new_dlist);
}

// implement dlist_reverse

struct dlist *dlist_split_at(struct dlist *list, size_t index)
{
    struct dlist_item *temp = list->head;
    if (index >= list->size)
        return NULL;
    if (!list)
        return dlist_init();
    size_t i = 0;
    while (i < index)
    {
        temp = temp->next;
        i++;
    }
    struct dlist *second_half = dlist_init();
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

void free_dlist_concat(struct dlist *list)
{
    struct dlist_item *node = list->head;
    while (node)
    {
        struct dlist_item *temp = node;
        node = node->next;
        free(temp);
        list->size--;
    }
}

void dlist_concat(struct dlist *list1, struct dlist *list2)
{
    if (!list1)
    {
        if (list2)
        {
            free_dlist_concat(list2);
            return;
        }
        return;
    }
    if (!list2)
        return;
    struct dlist_item *temp = list1->head;
    while (temp->next)
        temp = temp->next;
    struct dlist_item *temp2 = list2->head;
    struct dlist *new_list2 = dlist_init();
    if (!new_list2)
        return;
    while (temp2)
    {
        dlist_push_back(new_list2, temp2->data);
        temp2 = temp2->next;
    }
    free_dlist_concat(list2);
    temp->next = new_list2->head;
    new_list2->head->prev = temp;
    list1->size += new_list2->size;

    free(new_list2);
    return;
}