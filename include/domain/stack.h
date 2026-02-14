#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;

Stack *create_stack();
void insert_stack(Stack *st, char c);
int pop_stack(Stack *st);
char st_view_top(Stack *st);
int st_view_size(Stack *st);
void st_set_color(Stack *st, char color);
char st_view_color(Stack *st);
void print_stack(Stack *st);
void free_stack(Stack *st);

#endif
