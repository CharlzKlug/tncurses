#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::savetty
tncurses::resetty
tncurses::endwin
