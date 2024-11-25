#ifndef OVERLAP_H
#define OVERLAP_H

static int Overlay_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"overlay srcwin dstwin\"");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);

  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);

  int result= overlay(srcwin, dstwin);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int OverWrite_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"overwrite srcwin dstwin\"");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);

  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);

  int result= overwrite(srcwin, dstwin);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* OVERLAP_H */
