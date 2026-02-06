//Challenge Question #2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char *value;
    struct Node *prev;
    struct Node *next;
} Node;

Node* create_node(const char *s){
    Node *n = malloc(sizeof(Node));
    n->value = malloc(strlen(s) + 1);
    strcpy(n->value, s);

    n->prev = NULL;
    n->next = NULL;
    return n;
}

void insert(Node **head, Node *after, const char *s){
    Node *n = create_node(s);

    n->next = *head;
    if(*head)
       (*head)->prev = n;
    
    *head = n;
    return;

    n->next = after->next;
    n->prev = after;

    if (after->next)
        after->next->prev = n;

    after->next = n;
}


Node* find(Node *head, const char *s){
    while (head) {
        if(strcmp(head->value, s) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

void delete(Node **head, Node *n){
    if (!n) return;

    if(n->prev)
        n->prev->next = n->next;
    else
        *head = n->next;

    if(n->next)
        n->next->prev = n->prev;

    free(n->value);
    free(n);
}

void dump(Node *head){
    while (head) {
        printf("%s\n", head->value);
        head = head->next;
    }
}

void free_all(Node *head) {
    while (head) {
        Node *tmp = head;
        head = head->next;
        free(tmp->value);
        free(tmp);
    }
}

int main(int argc, const char* argv[]) {
    printf("Hello, world!\n");

    Node* list = NULL;
    insert(&list, NULL, "four");
    insert(&list, NULL, "one");
    insert(&list, find(list, "one"), "two");
    insert(&list, find(list, "two"), "three");

    Node *n = find(list, "three");
    if (n)
        printf("\nFound: %s\n", n->value);

    dump(list);
    printf("-- delete three --\n");
    delete(&list, find(list, "three"));
    dump(list);

    printf("-- delete one --\n");
    delete(&list, find(list, "one"));
    dump(list);

    free_all(list);
    return 0;
}
