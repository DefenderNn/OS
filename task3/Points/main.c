#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int mass;
    int index;
} Point;

int findSmallestMassIndex(Point points[], int n) {
    int smallestMass = points[0].mass;
    int smallestMassIndex = 0;

    for (int i = 1; i < n; i++) {
        if (points[i].mass < smallestMass) {
            smallestMass = points[i].mass;
            smallestMassIndex = i;
        }
    }

    return smallestMassIndex;
}

int main() {
    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    Point *points = (Point *) malloc(n * sizeof(Point));

    printf("Enter the masses of the points:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &points[i].mass);
        points[i].index = i;
    }

    while (n > 1) {
        int smallestMassIndex = findSmallestMassIndex(points, n);
        int nearestIndex = (smallestMassIndex == 0) ? 1 : 0;
        int smallestMass = points[smallestMassIndex].mass;

        for (int i = 0; i < n; i++) {
            if (i == smallestMassIndex) {
                continue;
            }

            int currentMass = points[i].mass;
            if (abs(i - smallestMassIndex) < abs(nearestIndex - smallestMassIndex) ||
                (abs(i - smallestMassIndex) == abs(nearestIndex - smallestMassIndex) &&
                 currentMass > points[nearestIndex].mass)) {
                nearestIndex = i;
            }
        }

        points[nearestIndex].mass += smallestMass;
        points[smallestMassIndex].mass = 0;

        for (int i = smallestMassIndex; i < n - 1; i++) {
            points[i] = points[i + 1];
        }

        n--;
    }

    printf("The last point has a mass of %d and an index of %d\n", points[0].mass, points[0].index);

    free(points);

    return 0;
}