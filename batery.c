#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdbool.h>

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

double *read_values_two(const char *rute)
{
}

double *get_values_num(void)
{
    const char *routes[] = {
        "/sys/class/power_supply/BAT0/capacity",
        "/sys/class/power_supply/BAT0/power_now",
        "/sys/class/power_supply/BAT0/voltage_now",
        "/sys/class/power_supply/BAT0/energy_full",
        "/sys/class/power_supply/BAT0/energy_full_design",
        "/sys/class/power_supply/BAT0/cycle_count",
        "/sys/class/power_supply/BAT0/energy_now",
        "/sys/class/power_supply/BAT0/charge_full",
        "/sys/class/power_supply/BAT0/voltage_min_design"};

    size_t leng = sizeof(routes) / sizeof(routes[0]);

    double *values_read = malloc(sizeof(double) * leng);
    if (!values_read)
    {
        perror("malloc failed");
        return NULL;
    }
    for (size_t i = 0; i < leng; i++)
    {
        if (access(routes[i], F_OK) != 0)
        {
            values_read[i] = 0.0;
            continue;
        }

        long value = read_number_value(routes[i]);
        if (value == -1)
        {
            values_read[i] = 0.0;
        }
        else
        {
            values_read[i] = (double)value;
        }
    }
    return values_read;
}

char **get_values_string(void)
{
    const char *routes[] = {
        "/sys/class/power_supply/BAT0/status",
        "/sys/class/power_supply/BAT0/model_name",
        "/sys/class/power_supply/BAT0/health",
        "/sys/class/power_supply/BAT0/temp"};

    size_t lengt = strlen(routes);
    char **values_return[] = malloc(sizeof(char *) * lengt);

    for (size_t i = 0; i < lengt; i++)
    {
        char *value = read_string_values(routes[i]);
        if (value == NULL)
        {
            values_return[i] = strdup("Error");
        }
        else
        {
            values_return[i] = value;
        }
    }
    return values_return;
}

double *get_values_double(void)
{
    // "/proc/uptime",
}

int main()
{

    get_values();

    return 0;
}
