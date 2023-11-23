#include <stdio.h>
#include <stdlib.h>

int countAboveAverage(int* array, int size) {
    if (size <= 0) {
        printf("Invalid array size.\n");
        return -1; // Assuming -1 is not a valid count
    }

    // Calculate the average
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    double average = sum / size;

    // Count elements greater than the average
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] > average) {
            count++;
        }
    }

    return count;
}

// Function to calculate the sum of the absolute values of elements after the first negative element
int sumOfAbsoluteValuesAfterNegative(int* array, int size) {
    if (size <= 0) {
        printf("Invalid array size.\n");
        return -1; // Assuming -1 is not a valid sum
    }

    int sum = 0;
    int foundNegative = 0;

    for (int i = 0; i < size; ++i) {
        if (foundNegative) {
            sum += abs(array[i]);
        }

        if (array[i] < 0) {
            foundNegative = 1;
        }
    }

    return sum;
}

int main() {
    // Example array
    int myArray[] = {2, 4, 6, 8, 10, 12, -3, 5, 7};

    // Calculate and print the count of elements greater than the average
    int aboveAverageCount = countAboveAverage(myArray, sizeof(myArray) / sizeof(myArray[0]));
    printf("Count of elements above average: %d\n", aboveAverageCount);

    // Calculate and print the sum of absolute values after the first negative element
    int sumAfterNegative = sumOfAbsoluteValuesAfterNegative(myArray, sizeof(myArray) / sizeof(myArray[0]));
    printf("Sum of absolute values after the first negative element: %d\n", sumAfterNegative);

    return 0;
}