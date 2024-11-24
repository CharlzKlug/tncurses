#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::delay_output 1000
for {set i 0} {$i < 10} {incr i} {
    tncurses::addstr "1"
}

tncurses::addstr "\nPress any key to continue..."
tncurses::getch
tncurses::endwin
