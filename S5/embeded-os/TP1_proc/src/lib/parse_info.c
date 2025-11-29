#include <stdio.h>
#include <string.h>

#include "parse_info.h"

int parse_info(const char *info_file_path, const char *categories[], int nb_categories) {

    // Open the info file
    FILE *file = fopen(info_file_path, "r");
    if (!file) {
        perror("Failed to open info file");
        return -1;
    }

    // Read each line and print it
    char line[256];
    while (fgets(line, sizeof(line), file) && line[0] != '\n') {

        // check if the line starts with one of the categories
        for (int i = 0; i < nb_categories; i++) {
            if (strncmp(line, categories[i], strlen(categories[i])) == 0) {
                printf("%s", line);
            }
        }
    }

    fclose(file);
    return 0;
}