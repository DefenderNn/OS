#include <stdio.h>
#include <math.h>

int main() {
    int n;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    double arr[n];

    printf("Enter %d real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double average = sum / n;

    int count = 0;
    double sumOfMods = 0;
    int foundNegative = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count++;
        }
        if (foundNegative) {
            sumOfMods += fabs(arr[i]);
        }
        if (arr[i] < 0) {
            foundNegative = 1;
        }
    }


    printf("Number of elements greater than the average: %d\n", count);
    printf("Absolute values sum of elements after the first negative number: %.2lf\n", sumOfMods);

    return 0;
}
