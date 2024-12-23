#ifndef TTY_MODES_H
#define TTY_MODES_H

static int CBreak_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"cbreak\"");

  int result= cbreak();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while cbreak", NULL);
  return TCL_ERROR;
}

static int NoCBreak_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"nocbreak\"");

  int result= nocbreak();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while nocbreak", NULL);
  return TCL_ERROR;
}

static int Echo_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"echo\"");

  int result= echo();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while echo", NULL);
  return TCL_ERROR;
}

static int NoEcho_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"noecho\"");

  int result= noecho();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while noecho", NULL);
  return TCL_ERROR;
}

static int HalfDelay_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"halfdelay tenths\"");

  int tenths;
  Tcl_GetIntFromObj(interp, objv[1], &tenths);

  if (1 > tenths || tenths > 255) {
    Tcl_AppendResult(interp, "tenths should be in the range 1..255", NULL);
    return TCL_ERROR;
  }

  int result= halfdelay(tenths);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while halfdelay", NULL);
  return TCL_ERROR;
}

static int IntrFlush_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"intrflush window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= intrflush(win, bf);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while intrflush", NULL);
  return TCL_ERROR;
}

static int KeyPad_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"keypad window bool");

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

static int Meta_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"meta window bool");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= meta(win, bf);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while meta", NULL);
  return TCL_ERROR;
}

static int NoDelay_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"nodelay window bool");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= nodelay(win, bf);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while nodelay", NULL);
  return TCL_ERROR;
}

static int Raw_Cmd(ClientData cdata, Tcl_Interp *interp,
		   int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"raw\"");

  int result= raw();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while raw", NULL);
  return TCL_ERROR;
}

static int NoRaw_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"noraw\"");

  int result= noraw();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while noraw", NULL);
  return TCL_ERROR;
}

static int NoQiFlush_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"noqiflush\"");

  noqiflush();

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int QiFlush_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"qiflush\"");

  qiflush();

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NoTimeout_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"notimeout window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= notimeout(win, bf);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while notimeout", NULL);
  return TCL_ERROR;
}

static int Timeout_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"timeout value\"");

  int timeoutValue;
  Tcl_GetIntFromObj(interp, objv[1], &timeoutValue);

  timeout(timeoutValue);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WTimeout_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"wtimeout window value\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int timeoutValue;
  Tcl_GetIntFromObj(interp, objv[2], &timeoutValue);

  wtimeout(win, timeoutValue);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int TypeAhead_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"typeahead fileDescriptor\"");

  int fileDescriptor;
  Tcl_GetIntFromObj(interp, objv[1], &fileDescriptor);

  int result= typeahead(fileDescriptor);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while typeahead", NULL);
  return TCL_ERROR;
}

#endif /* TTY_MODES_H */
