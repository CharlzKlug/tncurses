#!/usr/bin/env tclsh

load ./libtncurses.so

proc bomb {message} {
    addstr $message
    refresh
    getch
    endwin
    exit 1
}

initscr
try {
    set pod [newpad 50 50]
} trap {} {} {
    bomb "Unable to create new pad"
}

addstr "New pad created\n"
refresh

try {
    set pea [subpad $pod 20 20 29 29]
} trap {} {} {
    bomb "Unable to create subpad"
}

addstr "Subpad created\n"
refresh
getch

endwin
