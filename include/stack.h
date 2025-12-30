typedef struct stack stack;

stack *create_stack();
void st_set_color(stack *st, char color);
char st_view_color(stack *st);
void insert_stack(stack *st, char c);
int pop_stack(stack *st);
int view_top(stack *st);
int view_size(stack *st);
void print_stack(stack *st);
void free_stack(stack *st);
