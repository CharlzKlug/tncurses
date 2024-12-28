#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
set val [tncurses::use_extended_names FALSE]
tncurses::addstr "$val"
tncurses::getch
tncurses::endwin
