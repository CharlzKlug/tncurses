#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
start_color
init_pair 1 COLOR_WHITE COLOR_BLUE
init_pair 2 COLOR_RED COLOR_YELLOW

set sonny [subwin stdscr 5 20 10 30]

bkgd 1
addstr "Hello, son."
wbkgd $sonny 2
waddstr $sonny "Hello, Dad."
refresh
getch
endwin
