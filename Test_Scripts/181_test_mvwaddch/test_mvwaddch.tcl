#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

addstr "This is the original window, stdscr.\n"
refresh
getch

set two [newwin 0 0 0 0]
if {$two eq "NULL"} {
    addstr "Unable to allocate memory for new window."
    endwin
    exit 2
}

# waddstr $two "This is the new window created!\n"
mvwaddch $two 2 3 [chtype * 0]
wrefresh $two
getch

delwin $two
addstr "The second window was removed.\n"
refresh
getch

endwin
