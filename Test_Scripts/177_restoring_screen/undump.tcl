#!/usr/bin/env tclsh

load ./libtncurses.so

set FILENAME "/home/charlzk/Projects/tncurses/windump.tmp"

initscr

addstr "Press Enter to restore the screen\n"
refresh
getch

if {[catch {scr_restore $FILENAME}]} {
    addstr "Error reading window file: press Enter\n"
}

refresh
getch

endwin
exit 0
    
