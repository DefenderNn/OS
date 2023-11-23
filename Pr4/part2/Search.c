#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <variable_name>\n", argv[0]);
        return 1;
    }

    char *variable_name = argv[1];
    char *variable_value = getenv(variable_name);

    if (variable_value != NULL) {
        printf("Value of %s: %s\n", variable_name, variable_value);
    } else {
        printf("Variable %s not found in the environment.\n", variable_name);
    }

    return 0;
}
