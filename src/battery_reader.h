#ifndef BATTERY_READER_H
#define BATTERY_READER_H

long read_number_value(const char *route);
char *read_string_values(const char *route);
double *read_values_two(const char *route);

#endif