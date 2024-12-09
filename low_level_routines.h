#ifndef LOW_LEVEL_ROUTINES
#define LOW_LEVEL_ROUTINES

static int Curs_Set_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"curs_set visibility\"");

  int cursor_visibility;
  Tcl_GetIntFromObj(interp, objv[1], &cursor_visibility);

  int result= curs_set(cursor_visibility);

  if(result != ERR) {
    char str[4];
    sprintf(str, "%d", result);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while curs_set", NULL);
  return TCL_ERROR;
}

#endif /* LOW_LEVEL_ROUTINES */
