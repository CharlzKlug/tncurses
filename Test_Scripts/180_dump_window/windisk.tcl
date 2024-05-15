#!/usr/bin/env tclsh

load ./libtncurses.so

set FILENAME "window.tmp"

initscr
start_color
init_pair 1 COLOR_WHITE COLOR_BLUE

addstr "Creating new window\n"
refresh

if {[catch {set win [newwin 5 20 7 30]}]} {
    bomb "Unable to create window\n"
}
wbkgd $win [COLOR_PAIR 1]
mvwaddstr $win 1 2 "This program was\n"
mvwaddstr $win 2 5 "created by\n"
mvwaddstr $win 3 5 "Dan Gookin\n"
wrefresh $win
getch

if {[catch {putwin $win $FILENAME}]} {
    addstr "Error putting window to disk\n"
} else {
    addstr "Window put to disk\n"
}
refresh
getch

endwin
