#!/usr/bin/env tclsh

load ./libtncurses.so

set HLIN 10
set VLIN 5

set y {0 0 5 0 5 5 10 10 10 10 15 5}
set x {10 10 1 20 20 30 1 10 20 20 10 0}

initscr

for {set c 0} {$c < 12} {incr c 2} {
    mvhline [lindex $y $c] [lindex $x $c] 0 $HLIN
    mvvline [lindex $y [expr $c + 1]] [lindex $x [expr $c + 1]] 0 $VLIN
}

refresh
getch

endwin
