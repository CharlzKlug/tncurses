#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set maxy [getmaxy stdscr]

scrollok stdscr true

for {set y 0} {$y < $maxy} {incr y} {
    mvprintw $y 0 "This is boring text written to line $y."
}

refresh
getch

scroll stdscr
refresh
getch

endwin
