#!/usr/bin/env tclsh

load ./libtncurses.so
# source ./mkchtype.tcl

initscr
start_color
assume_default_colors [COLOR_RED] [COLOR_CYAN]
addstr "The default colors have been set to\n"
addstr "Red text on a cyan background.\n"
refresh
getch

endwin
