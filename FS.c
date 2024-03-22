
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

void printTree(const char *basePath, const int root) {
    char path[1000];
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    char **entries = NULL;
    int n = 0;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            entries = realloc(entries, sizeof(char*) * (n + 1));
            entries[n++] = strdup(dp->d_name);
        }
    }

<<<<<<< HEAD
int cmpfun(const void *a, const void *b){
	const char *name1 = (*(const struct dirent **)a)->d_name;
	const char *name2 = (*(const struct dirent **)b)->d_name;
		return strcmp(name1, name2);
}

void print_tree(const char *dir_path, int level){
	DIR *dir;
	struct dirent *entry;
	struct dirent **namelist;

	int n;

	dir = opendir(dir_path);

	if(!dir){
		perror("Error Opening directory");
		return;
	}

	//n = scandir(dir_path, &namelist, NULL, cmpfun);

}
=======
    qsort(entries, n, sizeof(char *), compare);
>>>>>>> df04400a5acb7764904356b9ccddfd1817d4ce7d

    for (int i = 0; i < n; i++) {
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, entries[i]);

        if (lstat(path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        printf("|%*s%s\n", root * 4, "", entries[i]);

        if (S_ISDIR(statbuf.st_mode)) {
            printTree(path, root + 1);
        }

        free(entries[i]);
    }

    free(entries);
    closedir(dir);
}

int main(int argc, char *argv[]) {
<<<<<<< HEAD
	//read UserInput for Directory
	char *dir_path = (argc == 2) ? argv[1] : ".";
=======
	
    char *basePath = argc > 1 ? argv[1] : ".";

    printf("%s\n", basePath);
    printTree(basePath, 0);
>>>>>>> df04400a5acb7764904356b9ccddfd1817d4ce7d

	printf("%s", dir_path);

	return 0;
}
