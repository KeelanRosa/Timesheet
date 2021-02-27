# Timesheet

A simple CLI to input hours worked into a .csv or .txt file.

Made for Linux; untested on other systems but may work if a command-line C compiler is installed.

## Usage

Navigate to the folder you installed Timesheet in and run `./timesheet filename.csv [-d] [-p]`

**filename.csv** - file you want to append your time/pay to
**-d** - toggle automatic dating. By default Timesheet will automatically insert today's date based on your computer clock; this will allow you to insert the date manually.
**-p** - toggle payday. By default Timesheet brings up dialog for inputting hours worked; this will change the dialog to asking how much you were paid.

After starting the program with default settings, Timesheet will ask how many days you worked and the hours worked per day. Input your time in HH:MM format for each day and at the end, Timesheet will calculate the total time worked for the period and add it to your desired CSV file.

## Features

- Automatically use today's date or use `-d` to be asked for the relevant date
- Allows you to input the hours worked for several days at once and will calculate the total time worked for that time period
- Can also be used to track paydays and payments

## Installation

Download the source code to the folder you want to run it from. Compile the source code using `make timesheet`.

## License

This project is licensed under GNU GPL 3.0.
