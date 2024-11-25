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

static int CopyWin_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(10, "wrong # args: should be \"copywin srcwin "
		  "dstwin sminrow smincol dminrow dmincol "
		  "dmaxrow dmaxcol overlay");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);

  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[3], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[4], &smincol);

  int dminrow;
  Tcl_GetIntFromObj(interp, objv[5], &dminrow);

  int dmincol;
  Tcl_GetIntFromObj(interp, objv[6], &dmincol);

  int dmaxrow;
  Tcl_GetIntFromObj(interp, objv[7], &dmaxrow);

  int dmaxcol;
  Tcl_GetIntFromObj(interp, objv[8], &dmaxcol);

  int overlay;
  Tcl_GetIntFromObj(interp, objv[9], &overlay);


  int result= copywin(srcwin, dstwin, sminrow,
		      smincol, dminrow, dmincol,
		      dmaxrow, dmaxcol, overlay);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured while copywin", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* OVERLAP_H */
