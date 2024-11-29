#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

set maxy [tncurses::getmaxy stdscr]

tncurses::scrollok stdscr true

for {set y 0} {$y < $maxy} {incr y} {
    tncurses::mvprintw $y 0 "This is boring text written to line $y."
}

tncurses::refresh
tncurses::getch

tncurses::scroll stdscr
tncurses::refresh
tncurses::getch

tncurses::endwin
