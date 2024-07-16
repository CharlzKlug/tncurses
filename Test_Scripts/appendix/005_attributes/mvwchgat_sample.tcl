#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
start_color
init_pair 1 COLOR_RED COLOR_BLUE

addstr "Attributes active in this window:\n"
mvwchgat stdscr 0 0 5 [expr [A_BLINK]] 1 NULL
refresh
getch

set newWindow [newwin 10 30 4 26]
waddstr $newWindow "---==Test==---"
wrefresh $newWindow
getch

mvwchgat $newWindow 0 0 7 [A_BLINK] 1 NULL
wrefresh $newWindow
getch

delwin $newWindow
endwin
