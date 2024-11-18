#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
set someChar [tncurses::unctrl 313]
tncurses::addstr "Some char is $someChar\n"
tncurses::getch
tncurses::endwin
