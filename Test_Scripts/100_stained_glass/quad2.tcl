#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

start_color
refresh

init_pair 1 COLOR_BLACK COLOR_BLUE
init_pair 2 COLOR_BLACK COLOR_RED
init_pair 3 COLOR_BLACK COLOR_GREEN
init_pair 4 COLOR_BLACK COLOR_CYAN

set resolution [getmaxyx stdscr]
set halfy [expr {[lindex $resolution 0] / 2}]
set halfx [expr {[lindex $resolution 1] / 2}]

set a [newwin $halfy $halfx 0 0]
set b [newwin $halfy $halfx 0 $halfx]
set c [newwin $halfy $halfx $halfy 0]
set d [newwin $halfy $halfx $halfy $halfx]

mvwaddstr $a 0 0 "This is window A\n"
wbkgd $a [COLOR_PAIR 1]
wrefresh $a

mvwaddstr $b 0 0 "This is window B\n"
wbkgd $b [COLOR_PAIR 2]
wrefresh $b

mvwaddstr $c 0 0 "This is window C\n"
wbkgd $c [COLOR_PAIR 3]
wrefresh $c

mvwaddstr $d 0 0 "This is window D\n"
wbkgd $d [COLOR_PAIR 4]
wrefresh $d

getch

endwin

