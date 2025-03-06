#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
for {set i 0} {$i < 10} {incr i} {
    tncurses::addstr "$i --- The quick brown fox jumps over the lazy dog.\n"
}
tncurses::addstr "Press any key to continue..."
tncurses::move 5 0
for {set i 4} {$i > 0} {incr i -1} {
    tncurses::getch
    tncurses::insdelln 3
}
tncurses::getch

tncurses::endwin
exit 0
