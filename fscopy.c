#define _GNU_SOURCE
#define _POSIX_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include <unistd.h>


int compare(const void *a, const void *b) {
    const char *ia = *(const char**)a;
    const char *ib = *(const char**)b;
    return strcmp(ia, ib);
}

void printTree(const char *basePath, int root, char *prefix) {
    char path[1000];
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir(basePath);

    if (!dir) return;

    char **entries = NULL;
    int n = 0;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            entries = realloc(entries, sizeof(char*) * (n + 1));
            entries[n++] = strdup(dp->d_name);
        }
    }
    qsort(entries, n, sizeof(char *), compare);

    for (int i = 0; i < n; i++) {
        snprintf(path, sizeof(path), "%s/%s", basePath, entries[i]);

        if (lstat(path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        char newPrefix[1024];
        if (i < n - 1) {
            snprintf(newPrefix, sizeof(newPrefix), "%s│   ", prefix);
        } else {
            snprintf(newPrefix, sizeof(newPrefix), "%s    ", prefix);
        }

        if (root > 0) {
            printf("%s|-- %s\n", prefix, entries[i]);
        } else {
            printf("%s\n", entries[i]);
        }

        if (S_ISDIR(statbuf.st_mode)) {
            printTree(path, root + 1, newPrefix);
        }

        free(entries[i]);
    }

    free(entries);
    closedir(dir);
}

int main(int argc, char *argv[]) {
	
    char *basePath = argc > 1 ? argv[1] : ".";

    printf("%s\n", basePath);
    printTree(basePath, 0, "");


	return 0;
}
