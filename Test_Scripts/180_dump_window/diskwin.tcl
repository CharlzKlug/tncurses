#!/usr/bin/env tclsh

load ./libtncurses.so

proc bomb {inputMessage} {
    tncurses::addstr $inputMessage
    tncurses::refresh
    tncurses::getch
    tncurses::endwin
    exit 1
}

set FILENAME "window.tmp"

tncurses::initscr
tncurses::start_color
tncurses::init_pair 1 [tncurses::COLOR_WHITE] [tncurses::COLOR_BLUE]

tncurses::addstr "Press Enter to read the window from disk:\n"
tncurses::refresh
tncurses::getch

if {[catch {set win [tncurses::getwin $FILENAME]}]} {
    bomb "Unable to read/create window\n"
}
tncurses::wrefresh $win
tncurses::getch

tncurses::endwin
