#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

tncurses::addstr "Sample.\n"
set yxlist [tncurses::getyx stdscr]
tncurses::addstr "y = [lindex $yxlist 0], x = [lindex $yxlist 1]\n"
tncurses::getch
tncurses::endwin
