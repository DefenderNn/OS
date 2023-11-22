#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct ArrayList {
    int *data;
    int size;
    int capacity;
} ArrayList;

ArrayList *createArrayList() {
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    if (list == NULL) {
        perror("Memory error on creation");
        exit(1);
    }
    list->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return list;
}

void add(ArrayList *list, int item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int *)realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->size] = item;
    list->size++;
}

void insert(ArrayList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Wrong index\n");
        return;
    }
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int *)realloc(list->data, list->capacity * sizeof(int));
    }
    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = item;
    list->size++;
}

int size(ArrayList *list) {
    return list->size;
}

void removeItem(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Wrong index\n");
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}

void set(ArrayList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Wrong index\n");
        return;
    }
    list->data[index] = item;
}

int get(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Wrong index\n");
        return -1;
    }
    return list->data[index];
}


void printArrayList(ArrayList *list) {
    printf("List: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

void destroyArrayList(ArrayList *list) {
    free(list->data);
    free(list);
}

int main() {

    ArrayList *list = createArrayList();

    add(list, 1);
    add(list, 2);
    add(list, 3);

    printArrayList(list);

    printf("Array length: %d\n", size(list));

    insert(list, 1, 4);

    printArrayList(list);

    printf("Element with index 1: %d\n", get(list, 1));


    set(list, 2, 5);

    printf("Element with index 2: %d\n", get(list, 2));

    removeItem(list, 0);


    printf("Array size after deletion: %d\n", size(list));

    printArrayList(list);

    destroyArrayList(list);

    return 0;
}