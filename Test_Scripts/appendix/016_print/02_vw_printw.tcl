#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

set half [expr [tncurses::COLS] >> 1]
set size [expr $half * [tncurses::COLS]]
set size [expr $size >> 1]
set alpha [tncurses::newwin [tncurses::LINES] [expr $half - 1] 0 0]

tncurses::vw_printw $alpha "Test. Test. Test."

tncurses::wgetch $alpha
tncurses::endwin
