#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set TSIZE 18
set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

set x [expr {($maxx - $TSIZE) / 2}]
bkgd .
refresh

set b [newwin 1 $TSIZE 0 $x]
waddstr $b "I'm getting sick!"
wrefresh $b

for {set y 1} {$y < $maxy} {incr y} {
    mvwin $b $y $x
    touchline stdscr [expr {$y - 1}] 1
    refresh
    wrefresh $b
    getch
}

endwin
