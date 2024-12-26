#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
# first, turn the cursor off
set r [tncurses::curs_set 0]
tncurses::addstr "The cursor has been turned off: "
tncurses::refresh
tncurses::getch

# second, turn the cursor on
tncurses::curs_set 1
tncurses::move 1 0
tncurses::addstr "The cursor now on: "
tncurses::refresh
tncurses::getch

# third, turn the cursor very on
tncurses::curs_set 2
tncurses::move 2 0
tncurses::addstr "The cursor is now very on: "
tncurses::refresh
tncurses::getch

tncurses::curs_set $r
tncurses::endwin
