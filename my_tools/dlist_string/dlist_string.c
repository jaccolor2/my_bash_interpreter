// implement all the functions in dlist.h

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "dlist_string.h"

struct sdlist_item *sdlist_item_init(char *token)
{
    struct sdlist_item *node = malloc(sizeof(struct sdlist_item));
    if (!node)
        return NULL;
    node->token = token;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// Threshold 1.
struct sdlist *sdlist_init(void)
{
    struct sdlist *list = malloc(sizeof(struct sdlist));
    if (!list)
        return list;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void free_sdlist(struct sdlist *dlist)
{
    struct sdlist_item *node = dlist->head;
    while (node)
    {
        struct sdlist_item *temp = node;
        node = node->next;
        free(temp);
    }
    free(dlist);
}

void sdlist_print(const struct sdlist *list)
{
    if (list)
    {
        struct sdlist_item *temp = list->head;
        while (temp)
        {
            printf("%s\n", temp->token);
            temp = temp->next;
        }
    }
    else
        return;
}

int sdlist_push_front(struct sdlist *list, char *token)
{
    struct sdlist_item *node = sdlist_item_init(token);
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

int sdlist_push_back(struct sdlist *list, char *token)
{
    struct sdlist_item *node = sdlist_item_init(token);

    if (!list->size && !list->head && !list->tail)
        list->head = node;
    else
    {
        struct sdlist_item *temp = list->head;
        while (temp->next)
            temp = temp->next;
        temp->next = node;
        node->prev = temp;
    }
    list->size++;
    return 1;
}

struct sdlist *sdlist_copy(struct sdlist *src)
{
    struct sdlist *cpy = sdlist_init();
    if (!cpy)
        return NULL;
    struct sdlist_item *temp = src->head;
    while (temp)
    {
        sdlist_push_back(cpy, temp->token);
        temp = temp->next;
    }
    return cpy;
}

size_t sdlist_size(const struct sdlist *list)
{
    if (!list)
        return 0;
    return list->size;
}

// Threshold 2.
char *sdlist_get(struct sdlist *list, size_t index)
{
    if (!list || index > list->size - 1)
        return "\0";
    struct sdlist_item *tmp = list->head;
    size_t i = 0;
    while (i < index)
    {
        tmp = tmp->next;
        i++;
    }
    return tmp->token;
}

void sdlist_print_back_and_forth(struct sdlist *list)
{
    struct sdlist_item *temp = list->head;
    while (temp->next)
    {
        printf("%s\n", temp->token);
        temp = temp->next;
    }
    printf("%s\n", temp->token);
    temp = temp->prev;
    while (temp)
    {
        printf("%s\n", temp->token);
        temp = temp->prev;
    }
}

int sdlist_insert_at(struct sdlist *list, char *token, size_t index)
{
    if (!list || index > list->size)
        return -1;
    if (!index)
    {
        sdlist_push_front(list, token);
        return 1;
    }
    if (index == list->size - 1 || index == list->size)
    {
        sdlist_push_back(list, token);
        return 1;
    }
    size_t prev_index = 0;
    size_t next_index = 0;
    struct sdlist_item *temp1 = list->head;
    struct sdlist_item *node = sdlist_item_init(token);
    while (prev_index < index - 1)
    {
        temp1 = temp1->next;
        prev_index++;
    }
    struct sdlist_item *temp2 = list->head;
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

int sdlist_find(const struct sdlist *list, char *token)
{
    if (!list)
        return -1;
    struct sdlist_item *temp = list->head;
    size_t index = 0;
    while (my_strcmp(temp->token, token) && temp->next)
    {
        temp = temp->next;
        index++;
    }
    if (index == list->size - 1)
    {
        if (my_strcmp(temp->token, token))
            return -1;
        return index;
    }
    return index;
}

char *sdlist_remove_at(struct sdlist *list, size_t index)
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
    struct sdlist_item *temp1 = list->head;
    while (prev_index < index - 1)
    {
        temp1 = temp1->next;
        prev_index++;
    }
    struct sdlist_item *temp2 = list->head;
    while (next_index < index + 1)
    {
        temp2 = temp2->next;
        next_index++;
    }
    struct sdlist_item *temp = temp1->next;
    temp1->next = temp2;
    temp2->prev = temp1;
    char *res = temp->token;
    free(temp);
    list->size--;
    return res;
}

// Threshold 3.

void sdlist_reverse(struct sdlist *list)
{
    struct sdlist *new_dlist = sdlist_init();
    struct sdlist_item *temp = list->head;
    while (temp)
    {
        sdlist_push_front(new_dlist, temp->token);
        temp = temp->next;
    }
    temp = list->head;
    struct sdlist_item *temp_new_dlist = new_dlist->head;
    while (temp_new_dlist->next)
    {
        temp->token = temp_new_dlist->token;
        temp_new_dlist = temp_new_dlist->next;
        temp = temp->next;
    }
    temp->token = temp_new_dlist->token;
    free_sdlist(new_dlist);
}

// implement dlist_reverse

struct sdlist *dlist_split_at(struct sdlist *list, size_t index)
{
    struct sdlist_item *temp = list->head;
    if (index >= list->size)
        return NULL;
    if (!list)
        return sdlist_init();
    size_t i = 0;
    while (i < index)
    {
        temp = temp->next;
        i++;
    }
    struct sdlist *second_half = sdlist_init();
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

void free_sdlist_concat(struct sdlist *list)
{
    struct sdlist_item *node = list->head;
    while (node)
    {
        struct sdlist_item *temp = node;
        node = node->next;
        free(temp);
        list->size--;
    }
}

void sdlist_concat(struct sdlist *list1, struct sdlist *list2)
{
    if (!list1)
    {
        if (list2)
        {
            free_sdlist_concat(list2);
            return;
        }
        return;
    }
    if (!list2)
        return;
    struct sdlist_item *temp = list1->head;
    while (temp->next)
        temp = temp->next;
    struct sdlist_item *temp2 = list2->head;
    struct sdlist *new_list2 = sdlist_init();
    if (!new_list2)
        return;
    while (temp2)
    {
        sdlist_push_back(new_list2, temp2->token);
        temp2 = temp2->next;
    }
    free_sdlist_concat(list2);
    temp->next = new_list2->head;
    new_list2->head->prev = temp;
    list1->size += new_list2->size;

    free(new_list2);
    return;
}