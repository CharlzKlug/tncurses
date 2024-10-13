#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Just sample text\n"
tncurses::addstr "Press \[Enter\]...\n"
tncurses::getch
tncurses::erase
tncurses::addstr "Everything cleared. Press \[Enter\]...\n"
tncurses::getch

tncurses::endwin
