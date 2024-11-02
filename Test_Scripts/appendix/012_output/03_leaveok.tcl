#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::leaveok curscr FALSE
tncurses::addstr "Just sample text\n"
tncurses::addstr "Press \[Enter\]...\n"
tncurses::getch
tncurses::addstr "Window refreshed. Press \[Enter\]...\n"
tncurses::getch

tncurses::endwin
