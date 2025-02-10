#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "1234567890. Press \[Enter\] key to delete one char..."
tncurses::getch
tncurses::mvwdelch stdscr 0 2
tncurses::getch
tncurses::wdelch stdscr
tncurses::getch
tncurses::endwin
