#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>

int main() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        printf("Hostname: %s\n", hostname);
    } else {
        perror("Error getting hostname");
        return 1;
    }

    struct utsname system_info;
    if (uname(&system_info) == 0) {
        printf("\nSystem Information:\n");
        printf("  System Name: %s\n", system_info.sysname);
        printf("  Node Name: %s\n", system_info.nodename);
        printf("  Release: %s\n", system_info.release);
        printf("  Version: %s\n", system_info.version);
        printf("  Machine: %s\n", system_info.machine);
    } else {
        perror("Error getting system information");
        return 1;
    }
    return 0;
}
