#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

tncurses::addstr "Sample.\n"
set yxlist [tncurses::getparyx stdscr]
tncurses::addstr "y = [lindex $yxlist 0], x = [lindex $yxlist 1]\n"


set subWindow [tncurses::subwin STDSCR 10 30 4 26]
tncurses::border 0 0 0 0 0 0 0 0
tncurses::waddstr $subWindow "test... "
tncurses::refresh
tncurses::wrefresh $subWindow
set yxList2 [tncurses::getbegyx $subWindow]
tncurses::waddstr $subWindow "[lindex $yxList2 0] [lindex $yxList2 1]"
tncurses::refresh
tncurses::wrefresh $subWindow
tncurses::getch
tncurses::delwin $subWindow

tncurses::endwin
