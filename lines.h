#ifndef LINES_H
#define LINES_H

static int Border_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(9, "wrong # args: should be \"border leftSide\
rightSide topSide bottomSide topLeftHandCorner topRightHandCorner\
bottomLeftHandCorner bottomRightHandCorner\"");

  int ls;
  Tcl_GetIntFromObj(interp, objv[1], &ls);

  int rs;
  Tcl_GetIntFromObj(interp, objv[2], &rs);

  int ts;
  Tcl_GetIntFromObj(interp, objv[3], &ts);

  int bs;
  Tcl_GetIntFromObj(interp, objv[4], &bs);

  int tl;
  Tcl_GetIntFromObj(interp, objv[5], &tl);

  int tr;
  Tcl_GetIntFromObj(interp, objv[6], &tr);

  int bl;
  Tcl_GetIntFromObj(interp, objv[7], &bl);

  int br;
  Tcl_GetIntFromObj(interp, objv[8], &br);

  int result= border(ls, rs, ts, bs, tl, tr, bl, br);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while border", NULL);
  return TCL_ERROR;
}

static int WBorder_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(10, "wrong # args: should be \"wborder window leftSide\
rightSide topSide bottomSide topLeftHandCorner topRightHandCorner\
bottomLeftHandCorner bottomRightHandCorner\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int ls;
  Tcl_GetIntFromObj(interp, objv[2], &ls);

  int rs;
  Tcl_GetIntFromObj(interp, objv[3], &rs);

  int ts;
  Tcl_GetIntFromObj(interp, objv[4], &ts);

  int bs;
  Tcl_GetIntFromObj(interp, objv[5], &bs);

  int tl;
  Tcl_GetIntFromObj(interp, objv[6], &tl);

  int tr;
  Tcl_GetIntFromObj(interp, objv[7], &tr);

  int bl;
  Tcl_GetIntFromObj(interp, objv[8], &bl);

  int br;
  Tcl_GetIntFromObj(interp, objv[9], &br);

  int result= wborder(win, ls, rs, ts, bs, tl, tr, bl, br);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while wborder", NULL);
  return TCL_ERROR;
}

static int Box_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"box window verch horch\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int verch;
  Tcl_GetIntFromObj(interp, objv[2], &verch);

  int horch;
  Tcl_GetIntFromObj(interp, objv[3], &horch);

  int result= box(win, verch, horch);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while box", NULL);
  return TCL_ERROR;
}

static int HLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"hline char count\"");

  int ch;
  Tcl_GetIntFromObj(interp, objv[1], &ch);

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

static int WHLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"whline window char count\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int ch;
  Tcl_GetIntFromObj(interp, objv[2], &ch);

  int n;
  Tcl_GetIntFromObj(interp, objv[3], &n);

  int result= whline(win, ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while whline", NULL);
  return TCL_ERROR;
}

static int VLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"vline char count\"");

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

static int WVLine_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"wvline window char count\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int ch;
  Tcl_GetIntFromObj(interp, objv[2], &ch);

  int n;
  Tcl_GetIntFromObj(interp, objv[3], &n);

  int result= wvline(win, ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while wvline", NULL);
  return TCL_ERROR;
}

static int MvHLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args: should be \"mvhline y x chtype int\"");

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

static int MvWHLine_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(6, "wrong # args: should be \"mvwhline "
		  "window y x chtype length\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);

  int ch;
  if(Tcl_GetIntFromObj(interp, objv[4], &ch) == TCL_ERROR) {
    ch= Tcl_GetString(objv[3])[0];
  }

  int n;
  Tcl_GetIntFromObj(interp, objv[5], &n);

  int result= mvwhline(win, y, x, ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvwhline", NULL);
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

static int MvWVLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(6, "wrong # args: should be \"mvwvline "
		  "window y x chtype length");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);

  int ch;
  if(Tcl_GetIntFromObj(interp, objv[4], &ch) == TCL_ERROR) {
    ch= Tcl_GetString(objv[4])[0];
  }

  int n;
  Tcl_GetIntFromObj(interp, objv[5], &n);

  int result= mvwvline(win, y, x, ch, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvwvline", NULL);
  return TCL_ERROR;
}

static int DeleteLn_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"deleteln\"");

  int result= deleteln();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while deleteln", NULL);
  return TCL_ERROR;
}

static int WDeleteLn_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"wdeleteln\" window");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= wdeleteln(win);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while wdeleteln", NULL);
  return TCL_ERROR;
}

static int InsDelLn_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"insdelln\" number");

  int n;
  Tcl_GetIntFromObj(interp, objv[1], &n);

  int result= insdelln(n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while insdelln", NULL);
  return TCL_ERROR;
}

static int WInsDelLn_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"winsdelln\" window number");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int n;
  Tcl_GetIntFromObj(interp, objv[2], &n);

  int result= winsdelln(win, n);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while winsdelln", NULL);
  return TCL_ERROR;
}

#endif /* LINES_H */
