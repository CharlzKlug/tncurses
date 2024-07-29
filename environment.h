#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

static int BaudRate_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"environment\"");

  int result= baudrate();

  char str[16];
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int EraseChar_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"erasechar\"");

  char erase_char= erasechar();

  char str[4];
  sprintf(str, "%c", erase_char);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int Has_Ic_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"has_ic\"");

  int result= has_ic();

  char str[4];
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int Has_Il_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"has_il\"");

  int result= has_il();

  char str[4];
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int KillChar_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"killchar\"");

  char kllCh= killchar();

  char str[4];
  sprintf(str, "%c", kllCh);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int LongName_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"longname\"");

  char *name;
  name= longname();

  if (NULL == name) {
    Tcl_AppendResult(interp, "error occured while longname", NULL);
    return TCL_ERROR;
  }

  char str[256];
  sprintf(str, "%s", name);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int TermAttrs_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"termattrs\"");

  chtype attributes;
  attributes= termattrs();

  char str[64];
  sprintf(str, "%d", attributes);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int TermName_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"termname\"");

  char *terminal_name;
  terminal_name= termname();

  if (terminal_name == NULL) {
    Tcl_AppendResult(interp, "error occured while termname", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj(terminal_name, -1));
  return TCL_OK;
}

#endif /* ENVIRONMENT_H */
