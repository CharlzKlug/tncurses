#ifndef LOW_LEVEL_ROUTINES
#define LOW_LEVEL_ROUTINES

static int Def_Prog_Mode_Cmd(ClientData cdata, Tcl_Interp *interp,
			     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"def_prog_mode\"");

  int result= def_prog_mode();

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

#endif /* LOW_LEVEL_ROUTINES */
