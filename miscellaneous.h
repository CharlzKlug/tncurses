#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

static int UnCtrl_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"unctrl chtype\"");

  int chtype_char;
  Tcl_GetIntFromObj(interp, objv[1], &chtype_char);

  const char* result;
  result= unctrl(chtype_char);

  if (result == NULL) {
    Tcl_AppendResult(interp, "error occured while unctrl", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%s", result));
  return TCL_OK;
}

static int KeyName_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"keyname int_c\"");

  int c;
  Tcl_GetIntFromObj(interp, objv[1], &c);

  const char* result;
  result= keyname(c);

  if (result == NULL) {
    Tcl_AppendResult(interp, "error occured while keyname", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%s", result));
  return TCL_OK;
}

static int Filter_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"filter\"");

  filter();

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NoFilter_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"nofilter\"");

  nofilter();

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Use_Env_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"use_env boolValue\"");

  bool f;
  STRING_TO_BOOL(Tcl_GetString(objv[1]), f);

  use_env(f);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int PutWin_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"putwin window filename");

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

static int GetWin_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args : should be \"getwin filename\"");

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
    Tcl_AppendResult(interp,
		     "error occured while getwin (no window pointer)", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

#endif /* MISCELLANEOUS_H */
