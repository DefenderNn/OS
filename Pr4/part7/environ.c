#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

void print_environment() {
    extern char** environ;
    printf("Current Environment:\n");
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

void print_help() {
    printf("Usage: environ [OPTIONS]\n");
    printf("Options:\n");
    printf("  -h, --help               Display this help and exit\n");
    printf("  -i, --info <variable>    Display the value of the specified variable\n");
    printf("  -s, --set <variable=value> Set the specified environment variable\n");
    printf("  -a, --assign <variable>  Assign the specified variable a new value\n");
    printf("  -v, --value <value>      Specify the value for the -a option\n");
    printf("  -d, --del <variable>     Delete the specified environment variable\n");
    printf("  -c, --clear              Clear the entire environment\n");
}

void print_variable_value(const char *variable) {
    char *value = getenv(variable);
    if (value != NULL) {
        printf("%s=%s\n", variable, value);
    } else {
        printf("Variable %s not found in the environment.\n", variable);
    }
}

void set_variable(const char *variable, const char *value) {
    if (setenv(variable, value, 1) == 0) {
        printf("Environment Variable Set: %s=%s\n", variable, getenv(variable));
    } else {
        perror("Error setting environment variable");
    }
}

void assign_variable(const char *variable, const char *value) {
    if (variable == NULL) {
        fprintf(stderr, "Error: No variable specified for assignment.\n");
        return;
    }

    if (value == NULL) {
        value = "";
    }

    if (setenv(variable, value, 1) == 0) {
        printf("Environment Variable Assigned: %s=%s\n", variable, getenv(variable));
    } else {
        perror("Error assigning environment variable");
    }
}

void delete_variable(const char *variable) {
    if (unsetenv(variable) == 0) {
        printf("Environment Variable Deleted: %s\n", variable);
    } else {
        perror("Error deleting environment variable");
    }
}

void clear_environment() {
    if (clearenv() == 0) {
        printf("Environment Cleared.\n");
    } else {
        perror("Error clearing environment");
    }
}

int main(int argc, char *argv[]) {
    int option;
    char *variable = NULL;
    char *value = NULL;

    while ((option = getopt(argc, argv, "hi:s:a:v:d:c")) != -1) {
        switch (option) {
            case 'h':
                print_help();
                return 0;
            case 'i':
                variable = optarg;
                print_variable_value(variable);
                return 0;
            case 's':
                variable = strtok(optarg, "=");
                value = strtok(NULL, "=");
                set_variable(variable, value);
                return 0;
            case 'a':
                variable = optarg;
                break;
            case 'v':
                value = optarg;
                break;
            case 'd':
                variable = optarg;
                delete_variable(variable);
                return 0;
            case 'c':
                clear_environment();
                return 0;
            default:
                fprintf(stderr, "Unknown option: %c\n", optopt);
                print_help();
                return 1;
        }
    }

    if (argc == 1) {
        print_environment();
        return 0;
    }

    if (variable != NULL && value == NULL) {
        fprintf(stderr, "Error: Value not specified for variable assignment.\n");
        return 1;
    }

    if (variable != NULL) {
        assign_variable(variable, value);
    }

    return 0;
}
