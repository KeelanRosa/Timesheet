/*
 * Timesheet - A simple CLI to input hours worked into a .csv or .txt file
 * Copyright (C) 2021
 *
 * Author:  Keelan Rosa
 * License: GPLv3
 * Version: 1.0
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Settings
// Defaults can be temporarily toggled using -d and/or -p in the command line
bool auto_dating = true;  // whether to ask for date or use computer calendar
bool payday = false;      // whether current input is for payment or time

// Prototype
int toint(char n);

// Main function
int main(int argc, char *argv[])
{
        // Check file validity
        if (argc == 1)
        {
                printf("Please specify a .csv or .txt file.\n");
                return 1;
        }
        char *filename = argv[1];
        char fileext[5];
        int namelen = strlen(filename);
        strncpy(fileext, filename + namelen - 4, 4);
        if (strcmp(fileext, ".csv") != 0 && strcmp(fileext, ".txt") != 0)
        {
                printf("Please specify a .csv or .txt file.\n");
                return 1;
        }

        // Open file
        FILE *f = fopen(filename, "a");
        if (f == NULL)
        {
                printf("Could not open file.\n");
                return 1;
        }

        // Use flags to toggle default options
        for (int i = 2; i < argc; i++)
        {
                if (strcmp(argv[i], "-d") == 0)
                {
                        auto_dating = !auto_dating;
                }
                else if (strcmp(argv[i], "-p") == 0)
                {
                        payday = !payday;
                }
        }

        // Add date
        char date[11];

        if (auto_dating)
        {
                time_t rawtime;
                struct tm *t;
                time(&rawtime);
                t = localtime(&rawtime);

                sprintf(date, "%i/%i/%i", t->tm_mday, t->tm_mon+1, t->tm_year+1900);
                printf("Date: %s\n", date);
        }
        else
        {
                printf("Date: ");
                scanf("%s", date);
        }

        // Input payment or hours worked
        if (payday)
        {
                char pay[16];

                printf("Pay: ");
                scanf("%s", pay);
                fprintf(f, "%s,,%s\n", date, pay);
        }
        else
        {
                char time_total[6];
                char time_temp[6];
                int hours = 0;
                int minutes = 0;
                int n;

                printf("Number of days worked: ");
                scanf("%i", &n);
                for (int i = 1; i <= n; i++)
                {
                        printf("Day %i: ", i);
                        scanf("%s", time_temp);
                        while (time_temp[2] != ':')
                        {
                                printf("Please use HH:MM format.\nDay %i: ", i);
                                scanf("%s", time_temp);
                        }
                        hours += toint(time_temp[0]) * 10;
                        hours += toint(time_temp[1]);
                        minutes += toint(time_temp[3]) * 10;
                        minutes += toint(time_temp[4]);
                }
                hours += minutes / 60;
                minutes %= 60;

                sprintf(time_total, "%i:%i", hours, minutes);
                printf("Total: %s\n", time_total);
                fprintf(f, "%s,%s\n", date, time_total);
        }

        fclose(f);
        return 0;
}

// Simple conversion of string -> int for hours worked
int toint(char n)
{
        return n - 48;
}
