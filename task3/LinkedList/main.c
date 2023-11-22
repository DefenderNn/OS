#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        perror("Memory error");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Функція для додавання елемента в кінець списку
void add(LinkedList *list, int item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory error");
        exit(1);
    }
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

void insert(LinkedList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Wrong index\n");

        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory problem");
        exit(1);
    }
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

int size(LinkedList *list) {
    return list->size;
}

void removeItem(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Wrong index\n");
        return;
    }
    if (index == 0) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    list->size--;
}

void set(LinkedList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Wrong index\n");
        return;
    }
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = item;
}

int get(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Wrong index\n");
        return -1;
    }
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void printLinkedList(LinkedList *list) {
    Node *current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void destroyLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList *list = createLinkedList();

    add(list, 1);
    add(list, 2);
    add(list, 3);

    printLinkedList(list);
    printf("LinkedArray length: %d\n", size(list));

    insert(list, 1, 4);
    printLinkedList(list);

    printf("Element with index 1: %d\n", get(list, 1));

    set(list, 2, 5);
    printLinkedList(list);

    printf("Element with index 2: %d\n", get(list, 2));

    removeItem(list, 0);

    printf("Array length after deletion: %d\n", size(list));

    printLinkedList(list);

    destroyLinkedList(list);

    return 0;
}
