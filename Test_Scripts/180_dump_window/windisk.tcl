#!/usr/bin/env tclsh

load ./libtncurses.so

set FILENAME "window.tmp"

tncurses::initscr
tncurses::start_color
tncurses::init_pair 1 [tncurses::COLOR_WHITE] [tncurses::COLOR_BLUE]

tncurses::addstr "Creating new window\n"
tncurses::refresh

if {[catch {set win [tncurses::newwin 5 20 7 30]}]} {
    bomb "Unable to create window\n"
}
tncurses::wbkgd $win [tncurses::COLOR_PAIR 1]
tncurses::mvwaddstr $win 1 2 "This program was\n"
tncurses::mvwaddstr $win 2 5 "created by\n"
tncurses::mvwaddstr $win 3 5 "Dan Gookin\n"
tncurses::wrefresh $win
tncurses::getch

if {[catch {tncurses::putwin $win $FILENAME}]} {
    tncurses::addstr "Error putting window to disk\n"
} else {
    tncurses::addstr "Window put to disk\n"
}
tncurses::refresh
tncurses::getch

tncurses::endwin
