#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::intrflush stdscr TRUE
tncurses::noecho

while {1} {
    tncurses::addstr "Press \[Ctrl\] + \[C\] to continue..."
    tncurses::refresh
    after 1000
}
tncurses::getch
tncurses::endwin
