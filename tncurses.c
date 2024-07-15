/* How to build: gcc -shared -o libtncurses.so -DUSE_TCL_STUBS -I /usr/include/tcl tncurses.c -ltclstub8.6 -lncurses -fPIC */
#include <tcl.h>
#include <string.h>
#include "tncurses.h"
#include "attributes.h"
#include "addch.h"
#include "addchstr.h"
#include "addstr.h"
#include "colors.h"

static int Initscr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  initscr();
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int PrintW_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  printw(Tcl_GetString(objv[1]));
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Refresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  refresh();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int GetCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  int ch= getch();
  char str[64];
  sprintf(str, "%d", ch);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int EndWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  endwin();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NewWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 5) {
    return TCL_ERROR;
  }
  int rows;
  Tcl_GetIntFromObj(interp, objv[1], &rows);
  int cols;
  Tcl_GetIntFromObj(interp, objv[2], &cols);
  int y_org;
  Tcl_GetIntFromObj(interp, objv[3], &y_org);
  int x_org;
  Tcl_GetIntFromObj(interp, objv[4], &x_org);
  WINDOW *window= newwin(rows, cols, y_org, x_org);

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int NoEcho_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  noecho();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  void* pointer= NULL;
  if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
    Tcl_AppendResult(interp, "Bad scan", NULL);
    return TCL_ERROR;
  }
  WINDOW* window= (WINDOW*)pointer;
  wrefresh(window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int TouchWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  char stdscr_array[]= "stdscr";
  if (strcmp(buffer, "stdscr") == 0) {
    touchwin(stdscr);
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    touchwin(win);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}


static int DelWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  WINDOW* win;
  
  char* buffer= Tcl_GetString(objv[1]);
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  if (delwin(win) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "Error occured with delwin", NULL);
  return TCL_ERROR;
}

static int GetMaxYX_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  int maxy, maxx;
  if (strcmp(buffer, "stdscr") == 0) {
    getmaxyx(stdscr, maxy, maxx);
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    getmaxyx(win, maxy, maxx);
  }
  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d %d", maxy, maxx));
  return TCL_OK;
}

static int Start_Color_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  start_color();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Init_Pair_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 4) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  int pair_number;
  if (Tcl_GetIntFromObj(interp, objv[1], &pair_number) == TCL_ERROR) {
    Tcl_AppendResult(interp, "pair number must be integer", NULL);
    return TCL_ERROR;
  }

  NCURSES_COLOR_T foreground_color;
  if (string_to_color(Tcl_GetString(objv[2]), &foreground_color) == (-1)) {
    Tcl_AppendResult(interp, "wrong foreground color", NULL);
    return TCL_ERROR;
  }

  NCURSES_COLOR_T background_color;
  if (string_to_color(Tcl_GetString(objv[3]), &background_color) == (-1)) {
    Tcl_AppendResult(interp, "wrong background color", NULL);
    return TCL_ERROR;
  }

  init_pair(pair_number, foreground_color, background_color);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WBkgd_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 3) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  buffer= Tcl_GetString(objv[2]);
  int input_val= -1;

  if (buffer[0] >= '0' && buffer[0] <= '9') {
    Tcl_GetIntFromObj(interp, objv[2], &input_val);
  }

  if (strlen(buffer) == 3 && buffer[0] == '\'' && buffer[2] == '\'') {
    input_val= buffer[1];
  }

  if (strlen(buffer) == 1) {
    input_val= buffer[0];
  }

  if (input_val == -1) {
    Tcl_AppendResult(interp, "wrong argument", NULL);
    return TCL_ERROR;
  }
  
  if (wbkgd(win, input_val) == ERR) {
    Tcl_AppendResult(interp, "Error occured in bkgd function", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WGetCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  char ch;
  ch= wgetch(win);

  char str[2];
  sprintf(str, "%c", ch);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int SubWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 6) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  int rows;
  if (Tcl_GetIntFromObj(interp, objv[2], &rows) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int cols;
  if (Tcl_GetIntFromObj(interp, objv[3], &cols) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int y;
  if (Tcl_GetIntFromObj(interp, objv[4], &y) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int x;
  if (Tcl_GetIntFromObj(interp, objv[5], &x) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  WINDOW *window= subwin(win, rows, cols, y, x);
  if (window == NULL) {
    Tcl_AppendResult(interp, "Error in creating subwindow!", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int Bkgd_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  int input_val= -1;

  if (buffer[0] >= '0' && buffer[0] <= '9') {
    Tcl_GetIntFromObj(interp, objv[1], &input_val);
  }

  if (strlen(buffer) == 3 && buffer[0] == '\'' && buffer[2] == '\'') {
    input_val= buffer[1];
  }

  if (strlen(buffer) == 1) {
    input_val= buffer[0];
  }

  if (input_val == -1) {
    Tcl_AppendResult(interp, "wrong argument", NULL);
    return TCL_ERROR;
  }
  
  if (bkgd(input_val) == ERR) {
    Tcl_AppendResult(interp, "Error occured in bkgd function", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int DerWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 6) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  int rows;
  if (Tcl_GetIntFromObj(interp, objv[2], &rows) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int cols;
  if (Tcl_GetIntFromObj(interp, objv[3], &cols) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int y;
  if (Tcl_GetIntFromObj(interp, objv[4], &y) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int x;
  if (Tcl_GetIntFromObj(interp, objv[5], &x) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  WINDOW *window= derwin(win, rows, cols, y, x);
  if (window == NULL) {
    Tcl_AppendResult(interp, "Error in creating subwindow!", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int WClear_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  int result= wclear(win);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Overlay_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);
  
  int result= overlay(srcwin, dstwin);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int OverWrite_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);
  
  int result= overwrite(srcwin, dstwin);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int CopyWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(10, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[3], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[4], &smincol);

  int dminrow;
  Tcl_GetIntFromObj(interp, objv[5], &dminrow);

  int dmincol;
  Tcl_GetIntFromObj(interp, objv[6], &dmincol);

  int dmaxrow;
  Tcl_GetIntFromObj(interp, objv[7], &dmaxrow);

  int dmaxcol;
  Tcl_GetIntFromObj(interp, objv[8], &dmaxcol);

  int overlay;
  Tcl_GetIntFromObj(interp, objv[9], &overlay);

  
  int result= copywin(srcwin, dstwin, sminrow,
		      smincol, dminrow, dmincol,
		      dmaxrow, dmaxcol, overlay);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int DupWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* result= dupwin(srcwin);

  if (result == NULL) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int ScrollOk_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  bool is_scroll;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), is_scroll);
  
  scrollok(win, is_scroll);
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int GetMaxY_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  int maxy= getmaxy(win);
  char str[5];
  sprintf(str, "%d", maxy);
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int MvPrintW_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  char *string = Tcl_GetString(objv[3]);

  if (mvprintw(y, x, string) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured", NULL);
  return TCL_ERROR;
}

static int Scroll_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= scroll(win);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while scroll", NULL);
  return TCL_ERROR;
}

static int Scrl_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int lines_number;
  Tcl_GetIntFromObj(interp, objv[1], &lines_number);

  int result= scrl(lines_number);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while scrl", NULL);
  return TCL_ERROR;
}

static int WScrl_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int lines_number;
  Tcl_GetIntFromObj(interp, objv[2], &lines_number);

  int result= wscrl(win, lines_number);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while wscrl", NULL);
  return TCL_ERROR;
}

static int MvWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);
  
  int result= mvwin(win, y, x);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while mvwin", NULL);
  return TCL_ERROR;
}

static int TouchLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int start;
  Tcl_GetIntFromObj(interp, objv[2], &start);

  int count;
  Tcl_GetIntFromObj(interp, objv[3], &count);
  
  int result= touchline(win, start, count);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while touchline", NULL);
  return TCL_ERROR;
}

static int COLOR_PAIR_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int color_num;
  Tcl_GetIntFromObj(interp, objv[1], &color_num);

  int result= COLOR_PAIR(color_num);
  char int_str_buffer[10];
  sprintf(int_str_buffer, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(int_str_buffer, -1));
  return TCL_OK;
}

static int NewPad_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int rows_number;
  Tcl_GetIntFromObj(interp, objv[1], &rows_number);

  int cols_number;
  Tcl_GetIntFromObj(interp, objv[2], &cols_number);

  WINDOW *window= newpad(rows_number, cols_number);

  if (window != NULL) {
    char hexstr[24];
    sprintf(hexstr, "%p", (void*)window);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "can't create new PAD", NULL);
  return TCL_ERROR;
}

static int PRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(8, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  int pminrow;
  Tcl_GetIntFromObj(interp, objv[2], &pminrow);

  int pmincol;
  Tcl_GetIntFromObj(interp, objv[3], &pmincol);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[4], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[5], &smincol);

  int smaxrow;
  Tcl_GetIntFromObj(interp, objv[6], &smaxrow);

  int smaxcol;
  Tcl_GetIntFromObj(interp, objv[7], &smaxcol);

  int result= prefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while prefresh", NULL);
  return TCL_ERROR;
}

static int SubPad_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(6, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  int rows;
  Tcl_GetIntFromObj(interp, objv[2], &rows);

  int cols;
  Tcl_GetIntFromObj(interp, objv[3], &cols);

  int y;
  Tcl_GetIntFromObj(interp, objv[4], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[5], &x);

  WINDOW* sub_pad= subpad(pad, rows, cols, y, x);

  if (sub_pad != NULL) {
    char hexstr[24];
    sprintf(hexstr, "%p", (void*)sub_pad);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "can't create new subpad", NULL);
  return TCL_ERROR;
}

static int PNOutRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(8, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  int pminrow;
  Tcl_GetIntFromObj(interp, objv[2], &pminrow);

  int pmincol;
  Tcl_GetIntFromObj(interp, objv[3], &pmincol);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[4], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[5], &smincol);

  int smaxrow;
  Tcl_GetIntFromObj(interp, objv[6], &smaxrow);

  int smaxcol;
  Tcl_GetIntFromObj(interp, objv[7], &smaxcol);

  int result= pnoutrefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while prefresh", NULL);
  return TCL_ERROR;
}

static int DoUpdate_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= doupdate();
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while prefresh", NULL);
  return TCL_ERROR;
}

static int PEchoChar_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  char *buffer= Tcl_GetString(objv[2]);
  if (strlen(buffer) == 0) {
    Tcl_AppendResult(interp, "no char argument!", NULL);
    return TCL_ERROR;
  }
  char ch= buffer[0];
  int result= pechochar(pad, ch);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while pechochar", NULL);
  return TCL_ERROR;
}

static int SLK_Init_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int mode;
  Tcl_GetIntFromObj(interp, objv[1], &mode);
  
  int result= slk_init(mode);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while slk_init", NULL);
  return TCL_ERROR;
}

static int SLK_Set_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  int label_num;
  Tcl_GetIntFromObj(interp, objv[1], &label_num);

  char *label_text;
  label_text= Tcl_GetString(objv[2]);

  int fmt;
  Tcl_GetIntFromObj(interp, objv[3], &fmt);
  
  int result= slk_set(label_num, label_text, fmt);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while slk_set", NULL);
  return TCL_ERROR;
}

static int SLK_Refresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= slk_refresh();
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while slk_refresh", NULL);
  return TCL_ERROR;
}

static int SLK_Restore_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= slk_restore();
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while slk_restore", NULL);
  return TCL_ERROR;
}

static int SLK_Clear_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= slk_clear();
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while slk_clear", NULL);
  return TCL_ERROR;
}

static int KeyPad_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool enable_func_keys;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), enable_func_keys);
  
  int result= keypad(win, enable_func_keys);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while keypad", NULL);
  return TCL_ERROR;
}

static int KEY_F_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int number;
  Tcl_GetIntFromObj(interp, objv[1], &number);
  
  int result= KEY_F(number);

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int NCURSES_MOUSE_VERSION_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= NCURSES_MOUSE_VERSION;

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int ALL_MOUSE_EVENTS_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");
  char str[64];
  sprintf(str, "%ld", ALL_MOUSE_EVENTS);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int ButtonsEvents_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");
  
  char str[64];
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON1_RELEASED") == 0) {
    sprintf(str, "%ld", BUTTON1_RELEASED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON1_PRESSED") == 0) {
    sprintf(str, "%ld", BUTTON1_PRESSED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON1_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON1_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON1_DOUBLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON1_DOUBLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON1_TRIPLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON1_TRIPLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON2_RELEASED") == 0) {
    sprintf(str, "%ld", BUTTON2_RELEASED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON2_PRESSED") == 0) {
    sprintf(str, "%ld", BUTTON2_PRESSED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON2_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON2_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON2_DOUBLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON2_DOUBLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON2_TRIPLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON2_TRIPLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON3_RELEASED") == 0) {
    sprintf(str, "%ld", BUTTON3_RELEASED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON3_PRESSED") == 0) {
    sprintf(str, "%ld", BUTTON3_PRESSED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON3_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON3_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON3_DOUBLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON3_DOUBLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON3_TRIPLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON3_TRIPLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON4_RELEASED") == 0) {
    sprintf(str, "%ld", BUTTON4_RELEASED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON4_PRESSED") == 0) {
    sprintf(str, "%ld", BUTTON4_PRESSED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON4_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON4_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON4_DOUBLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON4_DOUBLE_CLICKED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "BUTTON4_TRIPLE_CLICKED") == 0) {
    sprintf(str, "%ld", BUTTON4_TRIPLE_CLICKED);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int MouseMask_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int newmask;
  Tcl_GetIntFromObj(interp, objv[1], &newmask);

  mmask_t* oldmask;
  STRING_TO_MMASK_T(Tcl_GetString(objv[2]), oldmask);
  
  mmask_t result= mousemask(newmask, oldmask);

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int KEY_MOUSE_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= KEY_MOUSE;

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int GetMouse_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  MEVENT mort;
  int result= getmouse(&mort);

  if(result == OK) {
    char str[64];
    sprintf(str, "%d %d %d %d %d", mort.id, mort.x, mort.y, mort.z, mort.bstate);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while getmouse", NULL);
  return TCL_ERROR;
}

static int Move_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);
  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);
  
  int result= move(y, x);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while move", NULL);
  return TCL_ERROR;
}

static int ClrToEol_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= clrtoeol();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while clrtoeol", NULL);
  return TCL_ERROR;
}

static int Clear_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= clear();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while clear", NULL);
  return TCL_ERROR;
}

static int Curs_Set_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int cursor_visibility;
  Tcl_GetIntFromObj(interp, objv[1], &cursor_visibility);

  int result= curs_set(cursor_visibility);

  if(result != ERR) {
    char str[4];
    sprintf(str, "%d", result);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while curs_set", NULL);
  return TCL_ERROR;
}

static int Box_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int verch;
  if(Tcl_GetIntFromObj(interp, objv[2], &verch) == TCL_ERROR) {
    verch= Tcl_GetString(objv[2])[0];
  }

  int horch;
  if(Tcl_GetIntFromObj(interp, objv[3], &horch) == TCL_ERROR) {
    horch= Tcl_GetString(objv[3])[0];
  }

  int result= box(win, verch, horch);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while box", NULL);
  return TCL_ERROR;
}

static int Border_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(9, "wrong # args");

  int ls;
  if(Tcl_GetIntFromObj(interp, objv[1], &ls) == TCL_ERROR) {
    ls= Tcl_GetString(objv[1])[0];
  }
    
  int rs;
  if(Tcl_GetIntFromObj(interp, objv[2], &rs) == TCL_ERROR) {
    rs= Tcl_GetString(objv[2])[0];
  }

  int ts;
  if(Tcl_GetIntFromObj(interp, objv[3], &ts) == TCL_ERROR) {
    ts= Tcl_GetString(objv[3])[0];
  }

  int bs;
  if(Tcl_GetIntFromObj(interp, objv[4], &bs) == TCL_ERROR) {
    bs= Tcl_GetString(objv[4])[0];
  }

  int tl;
  if(Tcl_GetIntFromObj(interp, objv[5], &tl) == TCL_ERROR) {
    tl= Tcl_GetString(objv[5])[0];
  }

  int tr;
  if(Tcl_GetIntFromObj(interp, objv[6], &tr) == TCL_ERROR) {
    tr= Tcl_GetString(objv[6])[0];
  }

  int bl;
  if(Tcl_GetIntFromObj(interp, objv[7], &bl) == TCL_ERROR) {
    bl= Tcl_GetString(objv[7])[0];
  }

  int br;
  if(Tcl_GetIntFromObj(interp, objv[8], &br) == TCL_ERROR) {
    br= Tcl_GetString(objv[8])[0];
  }

  int result= border(ls, rs, ts, bs, tl, tr, bl, br);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while border", NULL);
  return TCL_ERROR;
}

static int HLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int ch;
  if(Tcl_GetIntFromObj(interp, objv[1], &ch) == TCL_ERROR) {
    ch= Tcl_GetString(objv[1])[0];
  }
    
  int n;
  Tcl_GetIntFromObj(interp, objv[2], &n);

  int result= hline(ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while hline", NULL);
  return TCL_ERROR;
}

static int VLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int ch;
  if(Tcl_GetIntFromObj(interp, objv[1], &ch) == TCL_ERROR) {
    ch= Tcl_GetString(objv[1])[0];
  }
    
  int n;
  Tcl_GetIntFromObj(interp, objv[2], &n);

  int result= vline(ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while vline", NULL);
  return TCL_ERROR;
}

static int MvHLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);
  
  int ch;
  if(Tcl_GetIntFromObj(interp, objv[3], &ch) == TCL_ERROR) {
    ch= Tcl_GetString(objv[3])[0];
  }
    
  int n;
  Tcl_GetIntFromObj(interp, objv[4], &n);

  int result= mvhline(y, x, ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvhline", NULL);
  return TCL_ERROR;
}

static int MvVLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);
  
  int ch;
  if(Tcl_GetIntFromObj(interp, objv[3], &ch) == TCL_ERROR) {
    ch= Tcl_GetString(objv[3])[0];
  }
    
  int n;
  Tcl_GetIntFromObj(interp, objv[4], &n);

  int result= mvvline(y, x, ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvvline", NULL);
  return TCL_ERROR;
}

static int Scr_Dump_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int result= scr_dump(Tcl_GetString(objv[1]));

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while scr_dump", NULL);
  return TCL_ERROR;
}

static int Scr_Restore_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int result= scr_restore(Tcl_GetString(objv[1]));

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while scr_restore", NULL);
  return TCL_ERROR;
}

static int PutWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  char* filename;
  filename= Tcl_GetString(objv[2]);

  FILE *wfile;
  wfile= fopen(filename, "w");
  if(wfile == NULL) {
    Tcl_AppendResult(interp, "can't open file while putwin", NULL);
    return TCL_ERROR;
  }
  
  int result= putwin(win, wfile);
  fclose(wfile);
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while putwin", NULL);
  return TCL_ERROR;
}

static int GetWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  char* filename;
  filename= Tcl_GetString(objv[1]);

  FILE *wfile;
  wfile= fopen(filename, "r");
  if(wfile == NULL) {
    Tcl_AppendResult(interp, "can't open file while getwin", NULL);
    return TCL_ERROR;
  }
  
  WINDOW *window= getwin(wfile);
  fclose(wfile);

  if(window == NULL) {
    Tcl_AppendResult(interp, "error occured while getwin (no window pointer)", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

int DLLEXPORT Tncurses_Init(Tcl_Interp *interp) {
  if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
    return TCL_ERROR;
  }
  /* changed this to check for an error - GPS */
  if (Tcl_PkgProvide(interp, "Tncurses", "1.0") == TCL_ERROR) {
    return TCL_ERROR;
  }
  Tcl_CreateObjCommand(interp, "initscr", Initscr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "printw", PrintW_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "refresh", Refresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getch", GetCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "endwin", EndWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "newwin", NewWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addstr", AddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwaddstr", MvWAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "noecho", NoEcho_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wrefresh", WRefresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "touchwin", TouchWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addch", AddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddstr", WAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "delwin", DelWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getmaxyx", GetMaxYX_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "start_color", Start_Color_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "init_pair", Init_Pair_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wbkgd", WBkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddch", WAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wgetch", WGetCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "subwin", SubWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "bkgd", Bkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "derwin", DerWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wclear", WClear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "overlay", Overlay_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "overwrite", OverWrite_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "copywin", CopyWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "dupwin", DupWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scrollok", ScrollOk_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getmaxy", GetMaxY_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvprintw", MvPrintW_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scroll", Scroll_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scrl", Scrl_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wscrl", WScrl_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwin", MvWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "touchline", TouchLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_PAIR", COLOR_PAIR_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "newpad", NewPad_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "prefresh", PRefresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "subpad", SubPad_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "pnoutrefresh", PNOutRefresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "doupdate", DoUpdate_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "pechochar", PEchoChar_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "slk_init", SLK_Init_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "slk_set", SLK_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "slk_refresh", SLK_Refresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "slk_restore", SLK_Restore_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "slk_clear", SLK_Clear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "keypad", KeyPad_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "KEY_F", KEY_F_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "NCURSES_MOUSE_VERSION", NCURSES_MOUSE_VERSION_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "ALL_MOUSE_EVENTS", ALL_MOUSE_EVENTS_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mousemask", MouseMask_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON1_RELEASED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON1_PRESSED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON1_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON1_DOUBLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON1_TRIPLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON2_RELEASED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON2_PRESSED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON2_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON2_DOUBLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON2_TRIPLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON3_RELEASED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON3_PRESSED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON3_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON3_DOUBLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON3_TRIPLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON4_RELEASED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON4_PRESSED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON4_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON4_DOUBLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "BUTTON4_TRIPLE_CLICKED", ButtonsEvents_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "KEY_MOUSE", KEY_MOUSE_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getmouse", GetMouse_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "move", Move_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "clrtoeol", ClrToEol_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvaddch", MvAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "clear", Clear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvaddstr", MvAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "curs_set", Curs_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "box", Box_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "border", Border_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "hline", HLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "vline", VLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvhline", MvHLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvvline", MvVLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scr_dump", Scr_Dump_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scr_restore", Scr_Restore_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "putwin", PutWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getwin", GetWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwaddch", MvWAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_ATTRIBUTES", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_NORMAL", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_STANDOUT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_UNDERLINE", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_REVERSE", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_BLINK", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_DIM", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_BOLD", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_ALTCHARSET", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_INVIS", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_PROTECT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_HORIZONTAL", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_LEFT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_LOW", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_RIGHT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_TOP", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_VERTICAL", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_ITALIC", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addchstr", AddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addchnstr", AddChNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddchstr", WAddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddchnstr", WAddChNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvaddchstr", MvAddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvaddchnstr", MvAddChNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwaddchstr", MvWAddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwaddchnstr", MvWAddChNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addnstr", AddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddnstr", WAddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvaddnstr", MvAddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwaddnstr", MvWAddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "assume_default_colors", Assume_Default_Colors_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_BLACK", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_RED", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_GREEN", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_YELLOW", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_BLUE", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_MAGENTA", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_CYAN", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_WHITE", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attr_get", Attr_Get_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attrset", AttrSet_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "A_COLOR", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attr_off", Attr_Off_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attr_on", Attr_On_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attroff", AttrOff_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattroff", WAttrOff_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attron", AttrOn_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattron", WAttrOn_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattrset", WAttrSet_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "color_set", Color_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wcolor_set", WColor_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "standend", Standend_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wstandend", WStandend_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "standout", StandOut_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattr_get", WAttr_Get_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattr_off", WAttr_Off_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattr_on", WAttr_On_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "attr_set", Attr_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wattr_set", WAttr_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "chgat", ChGAt_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wchgat", WChGAt_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvchgat", MvChGAt_Cmd, NULL, NULL);
  return TCL_OK;
}
