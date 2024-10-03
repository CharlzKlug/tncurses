#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Nodelay demo script\n"
tncurses::addstr "Press \[Enter\] to exit...\n"
tncurses::nodelay stdscr true
tncurses::noecho

while {1} {
    set ch [tncurses::getch]
    if {$ch != "-1"} {tncurses::addstr "$ch "}
    if {$ch == 10} {break}
}

tncurses::endwin
