#ifndef CLEAR_H
#define CLEAR_H

static int Erase_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"erase\"");

  int result= erase();

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while erase", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WErase_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"werase window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= werase(win);

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while werase", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Clear_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"clear\"");

  int result= clear();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while clear", NULL);
  return TCL_ERROR;
}

static int WClear_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"wclear window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= wclear(win);

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while wclear", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int ClrToBot_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"clrtobot\"");

  int result= clrtobot();

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while clrtobot", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WClrToBot_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"wclrtobot window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= wclrtobot(win);

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while wclrtobot", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int ClrToEol_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"clrtoeol\"");

  int result= clrtoeol();

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while clrtoeol", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WClrToEol_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"wclrtoeol window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= wclrtoeol(win);

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while wclrtoeol", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* CLEAR_H */
