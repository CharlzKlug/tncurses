#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

tncurses::scrollok STDSCR TRUE
tncurses::wsetscrreg STDSCR 10 15

for {set i 0} {$i < 50} {incr i} {
    tncurses::addstr "Just sample text: $i. Press \[Enter\] to continue.\n"
    tncurses::getch
}

tncurses::endwin
