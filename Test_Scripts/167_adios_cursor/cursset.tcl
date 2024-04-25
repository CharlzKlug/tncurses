#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

# first, turn the cursor off
set prev_value [curs_set 0]
addstr " <- The cursor has been turned off. Previous value: $prev_value"
move 0 0
refresh
getch

# second, turn the cursor on
set prev_value [curs_set 1]
addstr "\n <- The cursor now on. Previous value: $prev_value"
move 1 0
refresh
getch

# third, turn the cursor very on
set prev_value [curs_set 2]
addstr "\n <- The cursor is now very on. Previous value: $prev_value"
move 2 0
refresh
getch

endwin
