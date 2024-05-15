#!/usr/bin/env tclsh

load ./libtncurses.so

proc bomb {inputMessage} {
    addstr $inputMessage
    refresh
    getch
    endwin
    exit 1
}

set FILENAME "window.tmp"

initscr
start_color
init_pair 1 COLOR_WHITE COLOR_BLUE

addstr "Press Enter to read the window from disk:\n"
refresh
getch

if {[catch {set win [getwin $FILENAME]}]} {
    bomb "Unable to read/create window\n"
}
wrefresh $win
getch

endwin
