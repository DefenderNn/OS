#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
    uid_t user_uid = getuid();
    struct passwd *user_info_uid = getpwuid(user_uid);

    if (user_info_uid != NULL) {
        printf("User ID: %d\n", user_info_uid->pw_uid);
        printf("Username: %s\n", user_info_uid->pw_name);
        printf("Home Directory: %s\n", user_info_uid->pw_dir);
    } else {
        perror("Error getting user information");
        return 1;
    }

    return 0;
}
