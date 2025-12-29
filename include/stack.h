typedef struct stack stack;

stack *create_stack();
void insert_stack(stack *st, char c);
int pop_stack(stack *st);
int view_top(stack *st);
void print_stack(stack *st);
void free_stack(stack *st);
