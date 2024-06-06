#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr
refresh
start_color
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

wbkgd $a [COLOR_PAIR 1]
mvwaddstr $a 0 0 "This is window A\n"
wrefresh $a

wbkgd $b [COLOR_PAIR 2]
mvwaddstr $b 0 0 "This is window B\n"
wrefresh $b

wbkgd $c [COLOR_PAIR 3]
mvwaddstr $c 0 0 "This is window C\n"
wrefresh $c

wbkgd $d [COLOR_PAIR 4]
mvwaddstr $d 0 0 "This is window D\n"
wrefresh $d

while true {
    set ch [wgetch $a]
    waddch $b [chtype $ch 0]
    waddch $c [chtype $ch 0]
    waddch $d [chtype $ch 0]
    wrefresh $b
    wrefresh $c
    wrefresh $d
    if {$ch eq "~"} {break}
}

endwin
