#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

tncurses::printw [string cat "This window is [tncurses::LINES] " \
		      "lines by [tncurses::COLS] columns."]
tncurses::refresh
tncurses::getch

tncurses::endwin
