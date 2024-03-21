#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

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


int main(int argc, char *argv[]) {
	//read UserInput for Directory
	char *dir_path = (argc == 2) ? argv[1] : ".";

	printf("%s", dir_path);

	return 0;
}
