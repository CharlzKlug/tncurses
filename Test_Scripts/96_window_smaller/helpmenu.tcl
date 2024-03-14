#!/usr/bin/env tclsh

load ./libtncurses.so

proc showhelp {help} {
    wrefresh $help
    getch
    touchwin $help
    # touchwin stdscr
    refresh
}
    
initscr
set help [newwin 10 30 4 26]
mvwaddstr $help 1 7 "Help menu Screen"
mvwaddstr $help 5 3 "Press the ~ key to quit"
mvwaddstr $help 8 4 "Press ENTER to go back"

addstr "Typer Program\n"
addstr "Press + for help:\n\n"
refresh
noecho
while 1 {
    set ch [getch]
    refresh
    addch $ch
    if {$ch eq "+"} {showhelp $help}
    if {$ch eq "~"} break
}

endwin
