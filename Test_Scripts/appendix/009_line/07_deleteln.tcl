#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
for {set i 0} {$i < 10} {incr i} {
    tncurses::addstr "$i --- The quick brown fox jumps over the lazy dog.\n"
}
tncurses::addstr "Press any key to continue..."
tncurses::move 5 0
tncurses::getch
tncurses::deleteln
tncurses::getch

tncurses::endwin
exit 0
