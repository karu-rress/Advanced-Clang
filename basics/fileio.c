#include <stdio.h>

#define FILE_NAME "test.bin"

int main(void) {
    FILE *fp;
    int i = 2023;
    double pi = 3.141592;

    fp = fopen(FILE_NAME, "w+b");
    fwrite(&i, sizeof(int), 1, fp);
    fwrite(&pi, sizeof(double), 1, fp);
    fclose(fp);

    i = 0;
    pi = 0.0;

    fp = fopen(FILE_NAME, "rb");
    fread(&i, sizeof(int), 1, fp);
    fread(&pi, sizeof(double), 1, fp);
    fclose(fp);

    printf("i = %d, pi = %f\n", i, pi);

    return 0;
}