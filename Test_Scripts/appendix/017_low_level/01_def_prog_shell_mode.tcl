#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::def_shell_mode
tncurses::def_prog_mode
tncurses::reset_prog_mode
tncurses::reset_shell_mode
tncurses::endwin
