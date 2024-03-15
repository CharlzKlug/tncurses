#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

set halfx [expr {$maxx / 2}]
set halfy [expr {$maxy / 2}]

set a [newwin $halfy $halfx 0 0]
set b [newwin $halfy $halfx 0 $halfx]
set c [newwin $halfy $halfx $halfy 0]
set d [newwin $halfy $halfx $halfy $halfx]

refresh

mvwaddstr $a 0 0 "This is window A\n"
wrefresh $a

mvwaddstr $b 0 0 "This is window B\n"
wrefresh $b

mvwaddstr $c 0 0 "This is window C\n"
wrefresh $c

mvwaddstr $d 0 0 "This is window D\n"
wrefresh $d

getch

endwin
