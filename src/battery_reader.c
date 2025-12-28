#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include "battery_reader.h"

long read_number_value(const char *rute)
{
    FILE *file = fopen(rute, "r");
    if (file == NULL)
    {
        perror("Not Open File");
        return -1;
    }

    long value;
    if (fscanf(file, "%ld", &value) != 1)
    {
        perror("Error read file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return value;
}

char *read_string_values(const char *route)
{
    FILE *file = fopen(route, "r");
    if (file == NULL)
    {
        perror("Not Open File");
        return NULL;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
        perror("Error read file");
        fclose(file);
        return NULL;
    }
    fclose(file);

    char *result = malloc(strlen(buffer) + 1);
    if (result == NULL)
    {
        perror("malloc failed");
        return NULL;
    }

    strcpy(result, buffer);
    return result;
}

double *read_values_two(const char *route)
{
    FILE *file = fopen(route, "r");
    if (file == NULL)
    {
        perror("Not Open File");
        return NULL;
    }

    double *values_return = malloc(sizeof(double) * 2);
    if (values_return == NULL)
    {
        perror("Error failed malloc");
        fclose(file);
        return NULL;
    }
    if (fscanf(file, "%lf %lf", &values_return[0], &values_return[1]) != 2)
    {
        perror("Error parcing data");
        free(values_return);
        fclose(file);
        return NULL;
    }
    fclose(file);
    return values_return;
}