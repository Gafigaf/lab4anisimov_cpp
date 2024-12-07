#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE* file = fopen("100mb.txt", "rb");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize);
    if (!buffer) {
        perror("Failed to allocate buffer");
        fclose(file);
        return EXIT_FAILURE;
    }

    clock_t start = clock();
    fread(buffer, 1, fileSize, file);
    clock_t end = clock();

    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(buffer);
    fclose(file);

    return 0;
}
