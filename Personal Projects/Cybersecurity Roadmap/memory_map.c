#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// explorez memoria virtuala cu procfs, afland adresele rezervate heap-ului cu /proc/[pid]/maps
// si verificand ca ce am alocat cu malloc se afla in acel interval


int main(int argc, char* argv[])
{
    char* buffer = (char*)malloc(100);
    printf("Adresa buffer: %p\n", buffer);

    printf("Process ID: %d\n", getpid());

    char path[64];
    sprintf(path, "/proc/%d/maps", getpid());

    FILE* file = fopen(path, "r");
    if(file == NULL) {
	perror("Error opening file");
	free(buffer);
	return 1;
    }

    char line[256];

    while(fgets(line, sizeof(line), file) != NULL) {
	if(strstr(line, "[heap]") != NULL) {
	    printf("%s", line);

	    unsigned long start;
	    unsigned long finish;
	    unsigned long address = (unsigned long)buffer;
	    sscanf(line, "%lx-%lx", &start, &finish);

	    if(address >= start && address < finish) {
		printf("SUCCES! Se afla in interval.\n");
	    } else {
		printf("ESEC! Nu se afla in interval.\n");
	    }

	   break;
	}
    }

    fclose(file);
    free(buffer);

    return 0;
}
