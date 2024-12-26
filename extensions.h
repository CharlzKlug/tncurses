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

#endif /* EXTENSIONS_H */
