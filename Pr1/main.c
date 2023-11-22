#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    char surname[50];
    int age;
};

int main() {
    int numStudents;

    printf("How many students are in your group -> ");
    scanf("%d", &numStudents);

    struct Student *students = (struct Student*)malloc(numStudents * sizeof(struct Student));

    for (int i = 0; i < numStudents; ++i) {
        printf("\nEnter name -> ");
        scanf("%s", students[i].name);

        printf("Enter surname -> ");
        scanf("%s", students[i].surname);

        printf("Enter age -> ");
        scanf("%d", &students[i].age);
    }

    printf("\nList of students:\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("\nName: %s\nSurname: %s\nAge: %d\n", students[i].name, students[i].surname, students[i].age);
    }

    free(students);

    return 0;
}
