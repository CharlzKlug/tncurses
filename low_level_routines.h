#ifndef LOW_LEVEL_ROUTINES
#define LOW_LEVEL_ROUTINES

static int Def_Prog_Mode_Cmd(ClientData cdata, Tcl_Interp *interp,
			     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"def_prog_mode\"");

  int result= def_prog_mode();

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"def_prog_mode\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Def_Shell_Mode_Cmd(ClientData cdata, Tcl_Interp *interp,
			      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"def_shell_mode\"");

  int result= def_shell_mode();

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"def_shell_mode\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Curs_Set_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"curs_set visibility\"");

  int cursor_visibility;
  Tcl_GetIntFromObj(interp, objv[1], &cursor_visibility);

  int result= curs_set(cursor_visibility);

  if(result != ERR) {
    Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d", result));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while curs_set", NULL);
  return TCL_ERROR;
}

static int Reset_Prog_Mode_Cmd(ClientData cdata, Tcl_Interp *interp,
			       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"reset_prog_mode\"");

  int result= reset_prog_mode();

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"reset_prog_mode\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Reset_Shell_Mode_Cmd(ClientData cdata, Tcl_Interp *interp,
				int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"reset_shell_mode\"");

  int result= reset_shell_mode();

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"reset_shell_mode\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int ReseTTY_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"resetty\"");

  int result= resetty();

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"resetty\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int SaveTTY_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"savetty\"");

  int result= savetty();

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"savetty\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int GetsYX_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"getsyx\"");

  int y, x;
  getsyx(y, x);

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d %d", y, x));
  return TCL_OK;
}

static int SetsYX_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"setsyx y x\"");

  int y, x;
  Tcl_GetIntFromObj(interp, objv[1], &y);
  Tcl_GetIntFromObj(interp, objv[2], &x);

  setsyx(y, x);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NapMS_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"napms milliseconds\"");

  int ms;
  Tcl_GetIntFromObj(interp, objv[1], &ms);

  int result= napms(ms);

  if (ERR == result) {
    Tcl_AppendResult(interp, "Error occured in \"napms\"", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* LOW_LEVEL_ROUTINES */
