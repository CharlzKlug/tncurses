#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

for {set y 0; set x 0} {$y < $maxy && $x < $maxx} {incr y; incr x 2} {
    move $y $x
    hline 0 [expr $maxx - $x]
    vline 0 [expr $maxx - $y]
}

refresh
getch

endwin
