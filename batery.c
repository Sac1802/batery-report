#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#define RUTA_CAPACITY "/sys/class/power_supply/BAT0/capacity"
#define RUTA_STATUS "/sys/class/power_supply/BAT0/status"
#define RUTA_POWER_NOW "/sys/class/power_supply/BAT0/power_now"
#define RUTA_VOLTAGE_NOW "/sys/class/power_supply/BAT0/voltage_now"
#define RUTA_ENERGY_FULL "/sys/class/power_supply/BAT0/energy_full"
#define RUTA_ENERGY_FULL_DESIGN "/sys/class/power_supply/BAT0/energy_full_design"
#define RUTA_CYCLE_COUNT "/sys/class/power_supply/BAT0/cycle_count"
#define RUTA_UPTIME "/proc/uptime"


long read_number_value(const char *rute) {
    FILE *file = fopen(rute, "r");
    if (file == NULL) {
        perror("Not Open File");
        return -1;
    }

    long value;
    if (fscanf(file, "%ld", &value) != 1) {
        perror("Error read file");
        fclose(file);
        return -1;
    }

    fclose(file);
    return value;
}


void display_battery_status() {
    FILE *file = fopen(RUTA_STATUS, "r");
    if (file == NULL) {
        perror("Not Open File");
        return;
    }

    char status[256];
    if (fgets(status, sizeof(status), file) != NULL) {
        printf("Battery Status: %s", status);
    } else {
        perror("Error read status");
    }

    fclose(file);
}


void display_battery_health() {
    long energy_full = read_number_value(RUTA_ENERGY_FULL);
    long energy_design = read_number_value(RUTA_ENERGY_FULL_DESIGN);
    long cycle_count = read_number_value(RUTA_CYCLE_COUNT);

    if (energy_full == -1 || energy_design == -1 || cycle_count == -1) {
        return;
    }

    double health = ((double)energy_full / energy_design) * 100;
    printf("Battery Health: %.2f%%\n", health);
    printf("Full Charge: %ld mAh\n", energy_full / 1000);
    printf("Design Capacity: %ld mAh\n", energy_design / 1000);
    printf("Cycle Count: %ld\n", cycle_count);
}


void display_battery_metrics() {
    long power_now = read_number_value(RUTA_POWER_NOW);
    long voltage_now = read_number_value(RUTA_VOLTAGE_NOW);

    if (power_now == -1 || voltage_now == -1) {
        return;
    }

    double voltage = (double)voltage_now / 1e6;
    double power = (double)power_now / 1e6;
    double current = power / voltage;
    double energy_per_minute = power / 60.0;

    printf("Voltage: %.2f V\n", voltage);
    printf("Power Consumption: %.2f W\n", power);
    printf("Current Draw: %.2f A\n", current);
    printf("Energy Consumption (per minute): %.6f Wh\n", energy_per_minute);
    printf("----------------------------------------\n");
}

void display_uptime() {
    FILE *file = fopen(RUTA_UPTIME, "r");
    if (file == NULL) {
        perror("Not Open Uptime File");
        return;
    }

    double uptime_seconds;
    if (fscanf(file, "%lf", &uptime_seconds) != 1) {
        perror("Error read uptime");
        fclose(file);
        return;
    }

    fclose(file);

    int hours = (int)(uptime_seconds / 3600);
    int minutes = (int)((uptime_seconds - (hours * 3600)) / 60);
    int seconds = (int)(uptime_seconds - (hours * 3600) - (minutes * 60));

    printf("System Uptime: %02d:%02d:%02d (HH:MM:SS)\n", hours, minutes, seconds);
}

int main() {

    while (1) {
        system("clear");
        printf("Real-time Battery Monitoring. Press Ctrl+C to exit.\n");
        printf("+---------------------------------------------------+\n");
        printf("|               Power consumption                   |\n");
        printf("+---------------------------------------------------+\n");
        printf("=== Battery Metrics ===\n");

        display_uptime();
        display_battery_status();
        display_battery_health();
        display_battery_metrics();

        sleep(1);
    }

    return 0;
}


