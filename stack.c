#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    int value;
    node *next;
};

struct stack
{
    node *top;
    int size;
};

stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));

    if (!new_stack)
        return NULL;

    new_stack->top = NULL;
    new_stack->size = 0;
    return new_stack;
}

void insert_stack(stack *st, int k)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
        return;

    new_node->value = k;

    if (st->size == 0)
    {
        st->top = new_node;
        new_node->next = NULL;
    }

    else
    {
        new_node->next = st->top;
        st->top = new_node;
    }
    st->size++;
}

int pop_stack(stack *st)
{
    if (st->size == 0)
        return -1;

    node *to_free = st->top;
    int item = st->top->value;

    st->top = st->top->next;
    st->size--;

    free(to_free);
    return item;
}

void print_stack(stack *st)
{
    if (st == NULL)
        return;

    node *aux = st->top;
    while (aux != NULL)
    {
        printf("%d", aux->value);
        if (aux->next != NULL)
            printf(" -> ");
        aux = aux->next;
    }
}

int view_top(stack *st) { return st->top->value; }

void free_stack(stack *st)
{
    if (st->top == NULL)
        free(st);

    node *aux = st->top;

    while (aux != NULL)
    {
        node *to_free = aux;
        aux = aux->next;
        free(to_free);
    }
    free(st);
}
