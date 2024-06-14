#ifndef ADDCH_H
#define ADDCH_H

static int AddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int ch_value;
  Tcl_GetIntFromObj(interp, objv[1], &ch_value);
  int result= addch(ch_value);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

static int WAddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int ch_value;
  Tcl_GetIntFromObj(interp, objv[2], &ch_value);

  int result= waddch(win, ch_value);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while waddch", NULL);
  return TCL_ERROR;
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int MvAddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  int ch_value;
  Tcl_GetIntFromObj(interp, objv[3], &ch_value);
  
  int result= mvaddch(y, x, ch_value);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvaddch", NULL);
  return TCL_ERROR;
}

static int MvWAddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args");

  WINDOW* window;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), window);
  
  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);

  int ch_value;
  Tcl_GetIntFromObj(interp, objv[4], &ch_value);
  
  int result= mvwaddch(window, y, x, ch_value);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvwaddch", NULL);
  return TCL_ERROR;
}

#endif	/* ADDCH_H */
