#include <stdio.h>
#include <stdlib.h>

// Structure to represent a material point
struct MaterialPoint {
    int mass;
    int id;
    struct MaterialPoint* next;
};

// Function to create a material point
struct MaterialPoint* createMaterialPoint(int mass, int id) {
    struct MaterialPoint* point = (struct MaterialPoint*)malloc(sizeof(struct MaterialPoint));
    point->mass = mass;
    point->id = id;
    point->next = NULL;
    return point;
}

// Function to free the memory allocated for material points
void freeMaterialPoints(struct MaterialPoint* head) {
    while (head != NULL) {
        struct MaterialPoint* temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to simulate the mass transfer process
void massTransfer(struct MaterialPoint** points, int n) {
    while (n > 1) {
        // Find the point with the smallest mass
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

        // Transfer mass to the next point
        minPoint->next->mass += minPoint->mass;

        // Print the transfer information
        printf("Point %d transfers mass to Point %d\n", minPoint->id, minPoint->next->id);

        // Free the memory of the point that transferred its mass
        free(minPoint);

        // Update the number of points
        n--;
    }
}

int main() {
    // Number of material points
    int n = 5;

    // Create an array of material points
    struct MaterialPoint* points = NULL;
    for (int i = 0; i < n; ++i) {
        struct MaterialPoint* point = createMaterialPoint(rand() % 100 + 1, i + 1);
        point->next = points;
        points = point;
    }

    // Print the initial state of material points
    printf("Initial state of material points:\n");
    struct MaterialPoint* current = points;
    while (current != NULL) {
        printf("Point %d: Mass %d\n", current->id, current->mass);
        current = current->next;
    }
    printf("\n");

    // Simulate the mass transfer process
    massTransfer(&points, n);

    // Print the final state of material points
    printf("\nFinal state of material points:\n");
    struct MaterialPoint* finalState = points;
    while (finalState != NULL) {
        printf("Point %d: Mass %d\n", finalState->id, finalState->mass);
        finalState = finalState->next;
    }

    // Free the memory allocated for material points
    freeMaterialPoints(points);

    return 0;
}