#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "1234567890. Press \[Enter\] key to delete one char..."
tncurses::getch
tncurses::mvdelch 0 1
tncurses::getch
tncurses::mvdelch 0 2
tncurses::getch
tncurses::endwin
