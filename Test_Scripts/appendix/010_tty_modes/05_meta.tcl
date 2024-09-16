#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::meta stdscr FALSE
tncurses::addstr "Press \[Enter\] to exit..."

while {1} {
    set ch [tncurses::getch]
    tncurses::addstr "$ch\n"
    if {$ch == 10} {break}
}

tncurses::endwin
