#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::clearok curscr TRUE
tncurses::addstr "Just sample text\n"
tncurses::addstr "Press \[Enter\]...\n"
tncurses::getch
tncurses::wrefresh stdscr
tncurses::addstr "Window refreshed. Press \[Enter\]...\n"
tncurses::getch

tncurses::endwin
