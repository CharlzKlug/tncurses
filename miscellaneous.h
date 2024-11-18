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

#endif /* MISCELLANEOUS_H */
