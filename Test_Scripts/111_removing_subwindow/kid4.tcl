#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
refresh

start_color
init_pair 1 COLOR_WHITE COLOR_BLUE
init_pair 2 COLOR_RED COLOR_YELLOW
init_pair 3 COLOR_CYAN COLOR_GREEN

set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

set grandpa [newwin [expr {$maxy - 4}] [expr {$maxx - 10}] 2 5]
set father [subwin $grandpa [expr {$maxy - 8}] [expr {$maxx - 20}] 4 10]
set boy [subwin $father [expr {$maxy - 16}] [expr {$maxx - 40}] 8 20]

wbkgd $grandpa [COLOR_PAIR 1]
waddstr $grandpa "Grandpa\n"
wbkgd $father [COLOR_PAIR 2]
waddstr $father "Father\n"
wbkgd $boy [COLOR_PAIR 3]
waddstr $boy "Boy\n"
wrefresh $grandpa
getch

delwin $boy
wclear $father
waddstr $father "Bye, son!\n"
wrefresh $father
getch

endwin
