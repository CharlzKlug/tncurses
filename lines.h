#ifndef LINES_H
#define LINES_H

static int Border_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(9, "wrong # args: should be \"border leftSide\
rightSide topSide bottomSide topLeftHandCorner topRightHandCorner\
bottomLeftHandCorner bottomRightHandCorner\"");

  int ls;
  Tcl_GetIntFromObj(interp, objv[1], &ls);

  int rs;
  Tcl_GetIntFromObj(interp, objv[2], &rs);

  int ts;
  Tcl_GetIntFromObj(interp, objv[3], &ts);

  int bs;
  Tcl_GetIntFromObj(interp, objv[4], &bs);

  int tl;
  Tcl_GetIntFromObj(interp, objv[5], &tl);

  int tr;
  Tcl_GetIntFromObj(interp, objv[6], &tr);

  int bl;
  Tcl_GetIntFromObj(interp, objv[7], &bl);

  int br;
  Tcl_GetIntFromObj(interp, objv[8], &br);

  int result= border(ls, rs, ts, bs, tl, tr, bl, br);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while border", NULL);
  return TCL_ERROR;
}

#endif /* LINES_H */
