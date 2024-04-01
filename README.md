# tncurses
Binded commands:
- initscr;
- printw;
- refresh;
- getch;
- endwin;
- newwin;
- addstr;
- mvwaddstr;
- noecho;
- wrefresh;
- touchwin;
- addch;
- waddstr;
- delwin;
- getmaxyx. Input: window pointer. Output: list with MaxY and MaxX;
- start_color;
- init_pair;
- wbkgd (no need for COLOR_PAIR). Usage: "wbkgd $window 2";
- waddch;
- wgetch;
- subwin;
- bkgd;
Use of bkgd: if you want to send a char then use "bkgd .", if you want to send "'" char then use "bkgd '''", if you want to send a number like char, then use "bkgd '1'", and if you want to send a value, then use for example "bkg 256".
- derwin;
- wclear;
- overlay;
- overwrite;
- copywin;
- dupwin;
- scrollok;
- getmaxy;
- mvprintw;
- scroll;
- scrl;
- wscrl;
- mvwin;
- touchline;
- COLOR_PAIR;
- newpad;
