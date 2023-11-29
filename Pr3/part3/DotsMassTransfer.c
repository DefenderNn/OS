#include <stdio.h>
#include <stdlib.h>

struct MaterialPoint {
    int mass;
    int id;
    struct MaterialPoint* next;
};

struct MaterialPoint* createMaterialPoint(int mass, int id) {
    struct MaterialPoint* point = (struct MaterialPoint*)malloc(sizeof(struct MaterialPoint));
    point->mass = mass;
    point->id = id;
    point->next = NULL;
    return point;
}

void freeMaterialPoints(struct MaterialPoint* head) {
    while (head != NULL) {
        struct MaterialPoint* temp = head;
        head = head->next;
        free(temp);
    }
}

void massTransfer(struct MaterialPoint** points, int n) {
    while (n > 1) {
        struct MaterialPoint* minPoint = *points;
        struct MaterialPoint* prev = NULL;
        struct MaterialPoint* current = *points;

        while (current != NULL) {
            if (current->mass < minPoint->mass) {
                minPoint = current;
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    *points = current->next;
                }
            } else {
                prev = current;
            }

            current = current->next;
        }

        minPoint->next->mass += minPoint->mass;

        printf("Point %d transfers mass to Point %d\n", minPoint->id, minPoint->next->id);

        free(minPoint);

        n--;
    }
}

int main() {
    int n = 5;

    struct MaterialPoint* points = NULL;
    for (int i = 0; i < n; ++i) {
        struct MaterialPoint* point = createMaterialPoint(rand() % 100 + 1, i + 1);
        point->next = points;
        points = point;
    }

    printf("Initial state of material points:\n");
    struct MaterialPoint* current = points;
    while (current != NULL) {
        printf("Point %d: Mass %d\n", current->id, current->mass);
        current = current->next;
    }
    printf("\n");

    massTransfer(&points, n);

    printf("\nFinal state of material points:\n");
    struct MaterialPoint* finalState = points;
    while (finalState != NULL) {
        printf("Point %d: Mass %d\n", finalState->id, finalState->mass);
        finalState = finalState->next;
    }

    freeMaterialPoints(points);

    return 0;
}