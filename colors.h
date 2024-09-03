#ifndef COLORS_H
#define COLORS_H

static int ColorCode_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  char str[16];
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_BLACK") == 0) {
    sprintf(str, "%d", COLOR_BLACK);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_RED") == 0) {
    sprintf(str, "%d", COLOR_RED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_GREEN") == 0) {
    sprintf(str, "%d", COLOR_GREEN);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_YELLOW") == 0) {
    sprintf(str, "%d", COLOR_YELLOW);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_BLUE") == 0) {
    sprintf(str, "%d", COLOR_BLUE);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_MAGENTA") == 0) {
    sprintf(str, "%d", COLOR_MAGENTA);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_CYAN") == 0) {
    sprintf(str, "%d", COLOR_CYAN);
  }
  if (strcmp(Tcl_GetString(objv[0]), "COLOR_WHITE") == 0) {
    sprintf(str, "%d", COLOR_WHITE);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int Assume_Default_Colors_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int fg;
  Tcl_GetIntFromObj(interp, objv[1], &fg);

  int bg;
  Tcl_GetIntFromObj(interp, objv[2], &bg);

  int result= assume_default_colors(fg, bg);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while assume_default_colors", NULL);
  return TCL_ERROR;
}

static int Can_Change_Color_Cmd(ClientData cdata, Tcl_Interp *interp,
				int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"can_change_color\"");

  bool result= can_change_color();

  if(result) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("1", -1));
    return TCL_OK;
  }

    Tcl_SetObjResult(interp, Tcl_NewStringObj("0", -1));
    return TCL_OK;
}

static int Start_Color_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  start_color();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Init_Pair_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 4) {
    Tcl_AppendResult(interp, "wrong # args: should be \"init_pair pair foregroundColor backgroundColor\"", NULL);
    return TCL_ERROR;
  }

  int pair_number;
  if (Tcl_GetIntFromObj(interp, objv[1], &pair_number) == TCL_ERROR) {
    Tcl_AppendResult(interp, "pair number must be integer", NULL);
    return TCL_ERROR;
  }

  NCURSES_COLOR_T foreground_color;
  if (string_to_color(Tcl_GetString(objv[2]), &foreground_color) == (-1)) {
    Tcl_AppendResult(interp, "wrong foreground color", NULL);
    return TCL_ERROR;
  }

  NCURSES_COLOR_T background_color;
  if (string_to_color(Tcl_GetString(objv[3]), &background_color) == (-1)) {
    Tcl_AppendResult(interp, "wrong background color", NULL);
    return TCL_ERROR;
  }

  init_pair(pair_number, foreground_color, background_color);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* COLORS_H */
