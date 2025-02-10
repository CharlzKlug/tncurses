#ifndef DELETE_H
#define DELETE_H

static int DelCh_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"delch\"");

  int result= delch();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while delch", NULL);
  return TCL_ERROR;
}

static int WDelCh_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"wdelch window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= wdelch(win);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while wdelch", NULL);
  return TCL_ERROR;
}

static int MVDelCh_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"mvdelch y x\"");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);
  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  int result= mvdelch(y, x);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvdelch", NULL);
  return TCL_ERROR;
}

static int MVWDelCh_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"mvwdelch window y x\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);
  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);

  int result= mvwdelch(win, y, x);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvwdelch", NULL);
  return TCL_ERROR;
}

#endif /* DELETE_H */
