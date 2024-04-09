#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

try {
    set p [newpad 50 100]
} trap {} {} {
    addstr "Unable to create new pad"
    refresh
    endwin
    exit 1
}

addstr "New pad created"
refresh
getch

try {
    delwin $p
    addstr "...and now it's gone!\n"
} trap {} {} {
    addstr "...and it's still there!\n"
}
    
refresh
getch

endwin
