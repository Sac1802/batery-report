#include "menu.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "battery_reader.h"

struct timespec ts;

void draw_menu(void)
{
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);

    while (1)
    {
        double **vals = get_values_double();
        double *value_numbers = get_values_num();
        char **values_string = get_values_string();

        clear();

        attron(COLOR_PAIR(1));
        mvprintw(1, 2, "==============================================");
        mvprintw(2, 2, "                 BATTERY MONITOR              ");
        mvprintw(3, 2, "==============================================");
        attroff(COLOR_PAIR(1));

        double battery_percent = value_numbers[0];

        int bar_width = 40;
        int filled = (battery_percent * bar_width) / 100;

        if (battery_percent >= 70)
            attron(COLOR_PAIR(2));
        else if (battery_percent >= 40)
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(4));

        mvprintw(5, 2, "[");
        for (int i = 0; i < bar_width; i++)
        {
            if (i < filled)
                mvaddch(5, 3 + i, '=');
            else
                mvaddch(5, 3 + i, ' ');
        }
        mvprintw(5, 3 + bar_width, "]");
        attroff(COLOR_PAIR(2) | COLOR_PAIR(3) | COLOR_PAIR(4));

        mvprintw(6, 2, "Battery: %.0f%%", battery_percent);

        attron(COLOR_PAIR(1));
        mvprintw(8, 2, "General Information");
        attroff(COLOR_PAIR(1));

        mvprintw(9, 4, "Status: %s", values_string[0]);
        mvprintw(10, 4, "Capacity Level: %s", values_string[2]);
        mvprintw(11, 4, "Model Name: %s", values_string[1]);

        attron(COLOR_PAIR(1));
        mvprintw(13, 2, "Energy");
        attroff(COLOR_PAIR(1));

        mvprintw(14, 4, "Voltage: %.2f V", value_numbers[1] / 1000000.0);
        mvprintw(15, 4, "Energy Full: %.2f Wh", value_numbers[3] / 1000000.0);
        mvprintw(16, 4, "Energy Now: %.2f Wh", value_numbers[5] / 1000000.0);
        mvprintw(17, 4, "Energy Full Design: %.2f Wh", value_numbers[2] / 1000000.0);

        double energy_full = value_numbers[3] / 1000000.0;
        double energy_now = value_numbers[5] / 1000000.0;
        double uptime_seconds = vals[0][0];
        double energy_used = energy_full - energy_now;
        double consumption_per_second = energy_used / uptime_seconds;
        double consumption_per_hour = consumption_per_second * 3600.0;
        double percent_per_hour = (consumption_per_hour / energy_full) * 100.0;

        mvprintw(18, 4, "Battery Drain (per hour): %.2f %%", percent_per_hour);

        attron(COLOR_PAIR(1));
        mvprintw(20, 2, "Technical Data");
        attroff(COLOR_PAIR(1));

        mvprintw(21, 4, "Cycle Count: %.0f", value_numbers[4]);
        mvprintw(22, 4, "Voltage Min Design: %.2f V", value_numbers[6] / 1000000.0);
        mvprintw(23, 2, "Press Ctrl + c for exit");

        refresh();

        int c = getch();
        if (c == 'q' || c == 'Q')
            break;

        for (size_t i = 0; i < NUM_VALUES_STRING; i++)
            free(values_string[i]);
        free(values_string);

        for (size_t i = 0; i < NUM_VALUES_TWO; i++)
            free(vals[i]);
        free(vals);

        free(value_numbers);

        ts.tv_sec = 1;
        ts.tv_nsec = 0;
        nanosleep(&ts, NULL);
    }

    endwin();
}