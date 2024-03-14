/* How to build: gcc -shared -o libtncurses.so -DUSE_TCL_STUBS -I /usr/include/tcl tncurses.c -ltclstub8.6 -lncurses -fPIC */
#include <tcl.h>
#include <ncurses.h>

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
  return TCL_OK;
}
