#!/usr/bin/env tclsh

package require control
load ./libtncurses.so

proc showhelp {help} {
    touchwin $help
    wrefresh $help
    getch
    touchwin stdscr
    refresh
}

initscr

try {
    set help [newwin 10 30 4 26]
} trap {} {} {
    addstr "Unable to allocate window memory\n"
    endwin
}

mvwaddstr $help 1 7 "Help menu Screen"
mvwaddstr $help 5 3 "Press the ~ key to quit"
mvwaddstr $help 8 4 "Press ENTER to go back"
box $help 0 0

addstr "Typer Program\n"
addstr "Press + for help:\n\n"
refresh
noecho

control::do {
    set ch [getch]
    refresh
    set char_view [format "%c" $ch]
    if {$char_view eq "+"} {
	showhelp $help
    } else {
	addch $char_view
    }
} while {$char_view ne "~"}

endwin
