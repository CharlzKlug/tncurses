#!/usr/bin/env tclsh

package require control
load ./libtncurses.so

set FILENAME "Test_Scripts/122_scroll/gettysburg.txt"
set TALL 24
set WIDE 19
set SPACER 5

initscr

set p [newpad 200 [expr {$WIDE + 1}]]

set fp [open $FILENAME r]
fconfigure $fp -buffering line

while {![eof $fp]} {
    set file_char [read $fp 1]
    if {![eof $fp]} {
	waddch $p $file_char
    }
}
close $fp


prefresh $p 0 0 0 0 [expr {$TALL - 1}] $WIDE
prefresh $p $TALL 0 0 [expr {$WIDE + $SPACER}] [expr {$TALL - 1}] [expr {$WIDE * 2 + $SPACER}]
prefresh $p [expr {$TALL * 2}] 0 0 [expr {$WIDE * 2 + $SPACER * 2}] [expr {$TALL - 1}] \
    [expr {$WIDE * 3 + $SPACER * 2}]

wgetch $p
endwin
