#ifndef ADDSTR_H
#define ADDSTR_H

static int AddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");
  
  int result= addstr(Tcl_GetString(objv[1]));

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while addstr", NULL);
  return TCL_ERROR;
}

static int AddNStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  char *charstr= Tcl_GetString(objv[1]);

  int n;
  Tcl_GetIntFromObj(interp, objv[2], &n);
  
  int result= addnstr(charstr, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while addnstr", NULL);
  return TCL_ERROR;
}

static int WAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  char *charstr= Tcl_GetString(objv[2]);

  int result= waddstr(win, charstr);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while waddstr", NULL);
  return TCL_ERROR;
}

static int WAddNStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  char *charstr= Tcl_GetString(objv[2]);

  int n;
  Tcl_GetIntFromObj(interp, objv[3], &n);
  
  int result= waddnstr(win, charstr, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while waddnstr", NULL);
  return TCL_ERROR;
}

static int MvAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  char *str= Tcl_GetString(objv[3]);
  
  int result= mvaddstr(y, x, str);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvaddstr", NULL);
  return TCL_ERROR;
}

static int MvAddNStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  char *str= Tcl_GetString(objv[3]);

  int n;
  Tcl_GetIntFromObj(interp, objv[4], &n);
  
  int result= mvaddnstr(y, x, str, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvaddnstr", NULL);
  return TCL_ERROR;
}

static int MvWAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);

  char *str= Tcl_GetString(objv[4]);

  int result= mvwaddstr(win, y, x, str);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvwaddstr", NULL);
  return TCL_ERROR;
}

#endif /* ADDSTR_H */
