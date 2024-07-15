#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
start_color
init_pair 1 COLOR_RED COLOR_BLUE

addstr "Attributes active in this window:\n"
mvaddstr 0 0 "A"
wchgat stdscr 5 [expr [A_BLINK]] 1 NULL
refresh
getch

set someWindow [newwin 10 30 4 26]
waddstr $someWindow "---==Test==---"
mvwaddstr $someWindow 0 0 "-"
wchgat $someWindow 5 [expr [A_BLINK]] 1 NULL
wrefresh $someWindow
getch
delwin $someWindow

endwin
