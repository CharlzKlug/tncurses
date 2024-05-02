#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 1]
set maxx [lindex $resolution 2]

# for {set y 0; set x 0} {$y < 3} {incr y; incr x 2} {
#     move $y $x
#     hline 0 [expr $maxx - $x]
#     # vline 0 [expr $maxy - $y]
# }

move 0 0
hline 0 10
refresh
getch

endwin
