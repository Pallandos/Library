#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

// ------ Constants and Var ------
const char *CPUINFO_FILE = "/proc/cpuinfo";
const char *MEMINFO_FILE = "/proc/meminfo";
const char *VERSION_FILE = "/proc/version";

const char *PARTITIONS_FILE = "/proc/partitions";
int BLOCK_SIZE = 1024; // in bytes  

const char *cpu_categories[] = {
    "model name",
    "cpu MHz",
    "cache size",
    "address sizes"
};

const char *meminfo_categories[] = {
    "MemTotal",
    "MemFree",
};

const char *versions_categories[] = {
    "", // Empty string to match all lines
};

const char *process_categories[] = {
    "Name",
    "Tgid",
    "Pid",
    "PPid",
    "Uid",
    "Gid",
    "Threads"
};

// ---------- Function ----------

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

int parse_partitions(const char *parititions_file_path) {

    // Open the partitions file
    FILE *file = fopen(parititions_file_path, "r");
    if (!file) {
        perror("Failed to open partitions file");
        return -1;
    }

    printf("Size (in MO) : Name\n");

    // Read each line and print it
    char line[256];
    int line_num = 0;
    while (fgets(line, sizeof(line), file)) {
        char *word = strtok(line, " "); // split by space
        int col = 0;
        while (word != NULL && line_num > 1) { // skip the first two lines (headers)
            if (col == 2) { // print the 3rd column (size)
                int size_in_mo;
                size_in_mo = atoi(word) / BLOCK_SIZE;
                printf("%d : ", size_in_mo);
            } else if (col == 3) { // print the 4th column (name)
                printf("%s", word);
            }
            word = strtok(NULL, " ");
            col++;
        }
        line_num++;
    }

    fclose(file);
    return 0;
}

int process_info(int pid) {
    char status_path[256];
    char cmd_path[256];
    snprintf(status_path, sizeof(status_path), "/proc/%d/status", pid);
    snprintf(cmd_path, sizeof(cmd_path), "/proc/%d/cmdline", pid);

    // Status file
    parse_info(status_path, process_categories, sizeof(process_categories) / sizeof(process_categories[0]));

    // launched command
    char command[512];
    FILE *file = fopen(cmd_path, "r");
    if (file) {
        if (fgets(command, sizeof(command), file)) {
            printf("Command: %s\n", command);
        }
    }
    fclose(file);

    return 0;
}


// ------------ Main ------------

int main(int argc, char *argv[]) 
{
    int opt;

    if (argc < 2) {
        printf("Usage: %s [-c] [-m] [-v] [-p] [-P <PID>]\n", argv[0]);
        printf("  -c : CPU info\n");
        printf("  -m : Memory info\n");
        printf("  -v : Version info\n");
        printf("  -p : Partitions info\n");
        printf("  -P <PID> : Process info for given PID\n");
        return 1;
    }

    while ((opt = getopt(argc, argv, "cmvpdP:")) != -1) {
        switch (opt) {
            case 'c':
                parse_info(CPUINFO_FILE, cpu_categories, sizeof(cpu_categories) / sizeof(cpu_categories[0]));
                break;
            case 'm':
                parse_info(MEMINFO_FILE, meminfo_categories, sizeof(meminfo_categories) / sizeof(meminfo_categories[0]));
                break;
            case 'v':
                parse_info(VERSION_FILE, versions_categories, sizeof(versions_categories) / sizeof(versions_categories[0]));
                break;
            case 'p':
                parse_partitions(PARTITIONS_FILE);
                break;
            case 'P':
                process_info(atoi(optarg));
                break;
            default:
                fprintf(stderr, "Unknown option: %c\n", opt);
                return 1;
        }
    }

    return 0;
}