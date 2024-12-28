#ifndef EXTENSIONS_H
#define EXTENSIONS_H

static int Curses_Version_Cmd(ClientData cdata, Tcl_Interp *interp,
			      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"curses_version\"");

  const char* my_curses_version;
  my_curses_version= curses_version();

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%s", my_curses_version));
  return TCL_OK;
}

static int Use_Extended_Names_Cmd(ClientData cdata, Tcl_Interp *interp,
				  int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"use_extended_names bool\"");

  bool status;
  STRING_TO_BOOL(Tcl_GetString(objv[1]), status);

  int result= use_extended_names(status);

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d", result));
  return TCL_OK;
}

#endif /* EXTENSIONS_H */
