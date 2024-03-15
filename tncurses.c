/* How to build: gcc -shared -o libtncurses.so -DUSE_TCL_STUBS -I /usr/include/tcl tncurses.c -ltclstub8.6 -lncurses -fPIC */
#include <tcl.h>
#include <ncurses.h>
#include <string.h>

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
  char ch= getch();
  char str[2];
  sprintf(str, "%c", ch);
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

static int AddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  addstr(Tcl_GetString(objv[1]));
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int MvWAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 5) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  void* pointer= NULL;
  if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
    Tcl_AppendResult(interp, "Bad scan", NULL);
    return TCL_ERROR;
  }
  WINDOW* win= (WINDOW*)pointer;
  int y_org;
  Tcl_GetIntFromObj(interp, objv[2], &y_org);
  int x_org;
  Tcl_GetIntFromObj(interp, objv[3], &x_org);
  char* strbuf= Tcl_GetString(objv[4]);
  mvwaddstr(win, y_org, x_org, strbuf);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
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

static int AddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  addch(*buffer);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 3) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  if (strcmp(buffer, "stdscr") == 0) {
    waddstr(stdscr, Tcl_GetString(objv[2]));
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    waddstr(win, Tcl_GetString(objv[2]));
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int DelWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  if (strcmp(buffer, "stdscr") == 0) {
    delwin(stdscr);
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    delwin(win);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
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
  return TCL_OK;
}
