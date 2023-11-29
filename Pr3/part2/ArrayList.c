#include <stdio.h>
#include <stdlib.h>

struct ArrayList {
    int* array;
    int capacity;
    int size;
};

void initArrayList(struct ArrayList* list, int capacity) {
    list->array = (int*)malloc(capacity * sizeof(int));
    list->capacity = capacity;
    list->size = 0;
}

void add(struct ArrayList* list, int item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
    }
    list->array[list->size++] = item;
}

void insert(struct ArrayList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Invalid index for insertion.\n");
        return;
    }

    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
    }

    for (int i = list->size; i > index; --i) {
        list->array[i] = list->array[i - 1];
    }

    list->array[index] = item;
    list->size++;
}

int size(struct ArrayList* list) {
    return list->size;
}

void removeItem(struct ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for removal.\n");
        return;
    }

    for (int i = index; i < list->size - 1; ++i) {
        list->array[i] = list->array[i + 1];
    }

    list->size--;
}

void set(struct ArrayList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for setting.\n");
        return;
    }

    list->array[index] = item;
}

int get(struct ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Invalid index for getting.\n");
        return -1;
    }

    return list->array[index];
}

void printArrayList(struct ArrayList* list) {
    for (int i = 0; i < list->size; ++i) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

void freeArrayList(struct ArrayList* list) {
    free(list->array);
}

int main() {
    struct ArrayList myList;
    initArrayList(&myList, 5);

    add(&myList, 1);
    add(&myList, 2);
    add(&myList, 3);
    add(&myList, 4);

    insert(&myList, 2, 10);
    printArrayList(&myList);

    removeItem(&myList, 1);
    printArrayList(&myList);

    set(&myList, 0, 100);
    printArrayList(&myList);

    int value = get(&myList, 2);
    printf("Value at index 2: %d\n", value);

    printf("Size of the list: %d\n", size(&myList));

    freeArrayList(&myList);

    return 0;
}