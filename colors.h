#ifndef COLORS_H
#define COLORS_H

static int ColorCode_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args : should be \"color_name\"");

  char str[16]= "";
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_BLACK") == 0) {
    sprintf(str, "%d", COLOR_BLACK);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_RED") == 0) {
    sprintf(str, "%d", COLOR_RED);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_GREEN") == 0) {
    sprintf(str, "%d", COLOR_GREEN);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_YELLOW") == 0) {
    sprintf(str, "%d", COLOR_YELLOW);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_BLUE") == 0) {
    sprintf(str, "%d", COLOR_BLUE);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_MAGENTA") == 0) {
    sprintf(str, "%d", COLOR_MAGENTA);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_CYAN") == 0) {
    sprintf(str, "%d", COLOR_CYAN);
  }
  if (strcmp(Tcl_GetString(objv[0]), "tncurses::COLOR_WHITE") == 0) {
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

  int foreground_color;
  Tcl_GetIntFromObj(interp, objv[2], &foreground_color);

  int background_color;
  Tcl_GetIntFromObj(interp, objv[3], &background_color);

  init_pair(pair_number, foreground_color, background_color);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Init_Color_Cmd(ClientData cdata, Tcl_Interp *interp,
			  int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args: should be \"init_color color "
		  "value_r value_g value_b\", values must be "
		  "between 0 and 1000");

  int color;
  Tcl_GetIntFromObj(interp, objv[1], &color);

  int value_r;
  Tcl_GetIntFromObj(interp, objv[2], &value_r);
  if (value_r < 0 || 1000 < value_r) {
    Tcl_AppendResult(interp, "value_r must be between 0 and 1000", NULL);
    return TCL_ERROR;
  }

  int value_g;
  Tcl_GetIntFromObj(interp, objv[3], &value_g);
  if (value_g < 0 || 1000 < value_g) {
    Tcl_AppendResult(interp, "value_g must be between 0 and 1000", NULL);
    return TCL_ERROR;
  }

  int value_b;
  Tcl_GetIntFromObj(interp, objv[4], &value_b);
  if (value_b < 0 || 1000 < value_b) {
    Tcl_AppendResult(interp, "value_b must be between 0 and 1000", NULL);
    return TCL_ERROR;
  }

  int result= init_color(color, value_r, value_g, value_b);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while init_color", NULL);
  return TCL_ERROR;
}

static int Has_Colors_Cmd(ClientData cdata, Tcl_Interp *interp,
			  int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"has_colors\"");

  bool result= has_colors();

  if(result) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("1", -1));
    return TCL_OK;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("1", -1));
  return TCL_OK;
}

static int Color_Content_Cmd(ClientData cdata, Tcl_Interp *interp,
			     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"color_content color\"");

  int color;
  Tcl_GetIntFromObj(interp, objv[1], &color);

  short int r, g, b;

  int result= color_content(color, &r, &g, &b);

  if(result == OK) {
    char str[64];
    sprintf(str, "%d %d %d", r, g, b);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while color_content", NULL);
  return TCL_ERROR;
}

#endif /* COLORS_H */
