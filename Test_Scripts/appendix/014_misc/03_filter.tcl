#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::filter
tncurses::initscr
tncurses::addstr "Some test string"
tncurses::getch
tncurses::nofilter
tncurses::addstr "Another test string"
tncurses::getch
tncurses::endwin
