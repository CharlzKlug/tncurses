#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

set resolution [tncurses::getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

for {set y 0; set x 0} {$y < $maxy && $x < $maxx} {incr y; incr x 2} {
    tncurses::move $y $x
    tncurses::hline 0 [expr $maxx - $x]
    tncurses::vline 0 [expr $maxx - $y]
}

tncurses::refresh
tncurses::getch

tncurses::endwin
