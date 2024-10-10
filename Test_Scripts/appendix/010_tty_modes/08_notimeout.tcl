#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Raw demo script. Try to press \[Ctrl\] + \[C\].\n"
tncurses::addstr "Press \[Enter\] to exit...\n"
tncurses::noecho
tncurses::notimeout stdscr true

while {1} {
    set ch [tncurses::wgetch stdscr]
    if {$ch != "-1"} {tncurses::addstr "$ch "}
    if {$ch == 10} {break}
}

tncurses::endwin
