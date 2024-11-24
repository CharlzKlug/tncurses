#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Type few buttons, please."
tncurses::refresh
after 2000
tncurses::flushinp
tncurses::addstr " Your typed characters are ignored!"
tncurses::addstr "\nPress any key to continue..."
tncurses::getch
tncurses::endwin
