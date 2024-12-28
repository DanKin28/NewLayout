#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    int depth;
    struct Node *parent;
    int children_count;
} Node;

typedef struct Stack {
    Node **nodes;
    int top;
    int capacity;
} Stack;

Node *create_node(int id, int depth, Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->id = id;
    node->depth = depth;
    node->parent = parent;
    node->children_count = 0;
    return node;
}

void initStack(Stack *stack, int capacity) {    
    stack->nodes = (Node **)malloc(capacity * sizeof(Node *));
    stack->top = -1;
    stack->capacity = capacity;
}

int isStackEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, Node *node) {
    stack->top++;
    stack->nodes[stack->top] = node;
}

Node *pop(Stack *stack) {
    return stack->nodes[stack->top--];
}

Node *peek(Stack *stack) {
    return stack->nodes[stack->top];
}

int main() {
    int room_id;
    Stack stack;
    initStack(&stack, 100);
    int quarters_count = 0;
    int total_distance = 0;
    while (1) {
        scanf("%d", &room_id);
        if (room_id == -1) break;
    
        if (isStackEmpty(&stack)) {
            Node *entrance = create_node(room_id, 0, NULL);
            push(&stack, entrance);
            continue;
        }
        
        Node *current_node = peek(&stack);
        if (current_node->parent != NULL && current_node->parent->id == room_id) {
            if (current_node->children_count == 0) {
                quarters_count++;
                total_distance += current_node->depth;
            }
            pop(&stack);
        } else {
            Node *new_node = create_node(room_id, current_node->depth + 1, current_node);
            current_node->children_count++;
            push(&stack, new_node);
        }
    }

    Node *entrance = peek(&stack);
    if (entrance->children_count == 0) {
        quarters_count++;
        total_distance += entrance->depth;
    }   
    
    printf("%d %d\n", quarters_count, total_distance);
    
    while (!isStackEmpty(&stack)) {
        Node *node = pop(&stack);
        free(node);
    }
    
    free(stack.nodes);

    return 0;
}
