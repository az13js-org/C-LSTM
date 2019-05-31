#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void test_fprintf();
void test_fscanf();

int main(int argc, char *argv[])
{
    test_fprintf();
    test_fscanf();
    return 0;
}

void test_fprintf()
{
    FILE *test;
    test = fopen("temp.csv", "w");
    fprintf(test, "%lf\n", sqrt(2.0));
    fclose(test);
}

void test_fscanf()
{
    FILE *test;
    double result;
    test = fopen("temp.csv", "r");
    fscanf(test, "%lf", &result);
    fclose(test);
    printf("Value from file:\"%lf\".\n", result);
}
