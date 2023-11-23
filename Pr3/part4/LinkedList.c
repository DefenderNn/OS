#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
    int size;
};

void initLinkedList(struct LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

void add(struct LinkedList* list, int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

void insert(struct LinkedList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Invalid index for insertion.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

int size(struct LinkedList* list) {
    return list->size;
}

void removeItem(struct LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for removal.\n");
        return;
    }

    struct Node* temp;

    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }

        temp = current->next;
        current->next = temp->next;
    }

    free(temp);
    list->size--;
}

void set(struct LinkedList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for setting.\n");
        return;
    }

    struct Node* current = list->head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    current->data = item;
}

int get(struct LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for getting.\n");
        return -1; // Assuming -1 is not a valid value in the list
    }

    struct Node* current = list->head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    return current->data;
}

void printLinkedList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeLinkedList(struct LinkedList* list) {
    struct Node* current = list->head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;
}

int main() {
    struct LinkedList myList;
    initLinkedList(&myList);

    add(&myList, 1);
    add(&myList, 2);
    add(&myList, 3);
    add(&myList, 4);

    insert(&myList, 2, 10);
    printLinkedList(&myList);

    removeItem(&myList, 1);
    printLinkedList(&myList);

    set(&myList, 0, 100);
    printLinkedList(&myList);

    int value = get(&myList, 2);
    printf("Value at index 2: %d\n", value);

    printf("Size of the list: %d\n", size(&myList));

    freeLinkedList(&myList);

    return 0;
}