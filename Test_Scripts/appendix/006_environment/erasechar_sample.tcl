#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
set erchar [erasechar]
addstr "Current erase char is \"$erchar\". Press any key to continue."
getch
endwin
