#!/usr/bin/env tclsh

set FILENAME "windump.tmp"
load ./libtncurses.so

proc make_word {} {
    set result ""
    for {set i 0} {$i < 6} {incr i} {
	set result $result[format "%c" [expr {int(rand() * 100) % 26 + [scan a %c]}]]
    }
    return $result
}


initscr

for {set x 0} {$x < 200} {incr x} {
    printw "[make_word]\t"
}
addch \n
addstr "Press Enter to write this screen to disk\n"
refresh
getch

if {[catch {scr_dump $FILENAME}]} {
    addstr "Error writing window to disk\n"
} else {
    addstr "File written; press Enter to quit\n"
}
refresh
getch
endwin
exit 0
