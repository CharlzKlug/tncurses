#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
try {
    set someWindow [tncurses::newwin 10 30 4 26]
} trap {} {} {
    tncurses::addstr "Unable to allocate window memory\n"
    tncurses::endwin
}
tncurses::addstr "String in STDSCR window\n"
tncurses::waddstr $someWindow "Window content\nPress \[Enter\] to clear window content"
tncurses::refresh
tncurses::wrefresh $someWindow
tncurses::getch
tncurses::wclear $someWindow
tncurses::wrefresh $someWindow
tncurses::addstr "Window content is cleared\n"
tncurses::addstr "Press \[Enter\] to exit."
tncurses::getch

tncurses::endwin
