#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

for {set i 0} {$i < 320} {incr i} {
    tncurses::addstr "Test content. "
}
tncurses::addstr "\n\nPress \[Enter\] and part of screen will be cleared"
tncurses::getch
tncurses::move 10 10
tncurses::wclrtoeol stdscr
tncurses::addstr "\n\nPress \[Enter\] to exit...	   \n\n"
tncurses::getch
tncurses::endwin
