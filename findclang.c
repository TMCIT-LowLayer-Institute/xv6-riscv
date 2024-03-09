#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <paths.h>

constexpr auto PATH_SEPARATOR = ':';

int 
main(void) 
{
    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "Error: Could not get the PATH environment variable\n");
        return 1;
    }

    char *path_copy = strdup(path);
    if (path_copy == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for PATH\n");
        return 1;
    }

    char *dir = strtok(path_copy, ":");
    char *found_compiler = nullptr;

    while (dir != NULL) {
        char command[256];
        snprintf(command, sizeof(command), "%s/clang --version", dir);

        FILE *pipe = popen(command, "r");
        if (pipe != NULL) {
            char version_string[100];
            if (fgets(version_string, sizeof(version_string), pipe) != NULL) {
                pclose(pipe);

                /*
                 * Extract version number
                 */
                char *version_ptr = strstr(version_string, "version");
                if (version_ptr != NULL) {
                    double clang_version;
                    if (sscanf(version_ptr + strlen("version"), "%lf", &clang_version) == 1) {
                        /*
                         * Check if version is 18.1.0 or higher
                         */
                        if (clang_version >= 18.1) {
                            found_compiler = strdup(dir);
                            break;  /* Found a suitable compiler, no need to continue searching */
                        }
                    }
                }
            } else {
                pclose(pipe);
            }
        }

        dir = strtok(NULL, ":");
    }

    free(path_copy);

    if (found_compiler != NULL) {
        printf("%s/clang\n", found_compiler);
        free(found_compiler);
        return 0;
    } else {
        fprintf(stderr, "Error: Clang version 18.1.0 or higher not found in PATH\n");
        return 1;
    }
}
