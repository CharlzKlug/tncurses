#!/usr/bin/env tclsh

package require control
load ./libtncurses.so

initscr
refresh

set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

set lister [newwin $maxy [expr {$maxx / 2}] 0 [expr {$maxx / 4}]]

set filename "Test_Scripts/122_scroll/gettysburg.txt"
set fp [open $filename r]
fconfigure $fp -buffering line
# while {[gets $fp line] >= 0} {
#     waddstr $lister $line\n
#     wrefresh $lister
# }

while {![eof $fp]} {
    set file_char [read $fp 1]
    if {![eof $fp]} {
	waddch $lister $file_char
	wrefresh $lister
    }
}

close $fp

getch
endwin
