#!/usr/bin/env tclsh

load ./libtncurses.so

set text1 "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat."

set text2 "Four score and seven years ago our fathers brought forth on this continent, a new nation, conceived in Liberty, and dedicated to the proposition that all men are created equal."

initscr

set alpha [newwin 0 0 0 0]

addstr $text1
refresh
getch

waddstr $alpha $text2
wrefresh $alpha
getch

overlay stdscr $alpha
wrefresh $alpha
getch

endwin
