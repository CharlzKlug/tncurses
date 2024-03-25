#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
refresh

set fred [newwin 0 0 0 0]
waddstr $fred "This is the original window, Fred.\n"
wrefresh $fred
getch

set barney [dupwin $fred]
waddstr $barney "This is the Barney copy of window Fred.\n"
wrefresh $barney
getch

waddstr $fred "Nice to see you again!\n"
wrefresh $fred
getch

waddstr $barney "And Barney says 'Hi' as well.\n"
touchwin $barney
wrefresh $barney
getch

endwin
