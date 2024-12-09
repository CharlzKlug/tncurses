#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

# first, turn the cursor off
set prev_value [tncurses::curs_set 0]
tncurses::addstr " <- The cursor has been turned off. Previous value: $prev_value"
tncurses::move 0 0
tncurses::refresh
tncurses::getch

# second, turn the cursor on
set prev_value [tncurses::curs_set 1]
tncurses::addstr "\n <- The cursor now on. Previous value: $prev_value"
tncurses::move 1 0
tncurses::refresh
tncurses::getch

# third, turn the cursor very on
set prev_value [tncurses::curs_set 2]
tncurses::addstr "\n <- The cursor is now very on. Previous value: $prev_value"
tncurses::move 2 0
tncurses::refresh
tncurses::getch

tncurses::endwin
