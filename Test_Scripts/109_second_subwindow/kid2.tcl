#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
start_color
init_pair 1 COLOR_WHITE COLOR_BLUE
init_pair 2 COLOR_RED COLOR_YELLOW
init_pair 3 COLOR_CYAN COLOR_WHITE

set sonny [subwin stdscr 5 20 10 30]
set babygirl [derwin stdscr 5 20 1 50]

bkgd 1
addstr "Hello, son, hello baby girl."
wbkgd $sonny 2
waddstr $sonny "Hello, Dad."
wbkgd $babygirl 3
waddstr $babygirl "Hello, Papa."
refresh
getch

endwin
