#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

mvwaddnstr stdscr 0 10 "Hello!" 5
mvwaddnstr stdscr 1 9 "Hello!" 6
refresh
set someWindow [newwin 15 30 4 26]
mvwaddnstr $someWindow 1 1 "12345" 2
wrefresh $someWindow
getch
delwin $someWindow
endwin
