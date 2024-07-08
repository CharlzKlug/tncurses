#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

static int Attribute_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  char str[16];
  if (strcmp(Tcl_GetString(objv[0]), "A_ATTRIBUTES") == 0) {
    sprintf(str, "%d", A_ATTRIBUTES);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_NORMAL") == 0) {
    sprintf(str, "%d", A_NORMAL);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_STANDOUT") == 0) {
    sprintf(str, "%d", A_STANDOUT);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_UNDERLINE") == 0) {
    sprintf(str, "%d", A_UNDERLINE);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_REVERSE") == 0) {
    sprintf(str, "%d", A_REVERSE);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_BLINK") == 0) {
    sprintf(str, "%d", A_BLINK);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_DIM") == 0) {
    sprintf(str, "%d", A_DIM);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_BOLD") == 0) {
    sprintf(str, "%d", A_BOLD);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_ALTCHARSET") == 0) {
    sprintf(str, "%d", A_ALTCHARSET);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_INVIS") == 0) {
    sprintf(str, "%d", A_INVIS);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_PROTECT") == 0) {
    sprintf(str, "%d", A_PROTECT);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_HORIZONTAL") == 0) {
    sprintf(str, "%d", A_HORIZONTAL);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_LEFT") == 0) {
    sprintf(str, "%d", A_LEFT);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_LOW") == 0) {
    sprintf(str, "%d", A_LOW);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_RIGHT") == 0) {
    sprintf(str, "%d", A_RIGHT);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_TOP") == 0) {
    sprintf(str, "%d", A_TOP);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_VERTICAL") == 0) {
    sprintf(str, "%d", A_VERTICAL);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_ITALIC") == 0) {
    sprintf(str, "%d", A_ITALIC);
  }
  if (strcmp(Tcl_GetString(objv[0]), "A_COLOR") == 0) {
    sprintf(str, "%d", A_COLOR);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int Attr_Get_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  attr_t attributes;
  short cpair;
  int result= attr_get(&attributes, &cpair, NULL);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d %d", attributes, cpair));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while attr_get", NULL);
  return TCL_ERROR;
}

static int AttrSet_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"attrset attributes\"");

  int attrs;
  Tcl_GetIntFromObj(interp, objv[1], &attrs);

  /* return value is not important */
  int result= attrset(attrs);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while attr_set", NULL);
  return TCL_ERROR;
}

static int Attr_Off_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int attrs;
  Tcl_GetIntFromObj(interp, objv[1], &attrs);

  /* return value is not important */
  int result= attr_off(attrs, NULL);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while attr_off", NULL);
  return TCL_ERROR;
}

static int Attr_On_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int attrs;
  Tcl_GetIntFromObj(interp, objv[1], &attrs);

  /* return value is not important */
  int result= attr_on(attrs, NULL);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while attr_on", NULL);
  return TCL_ERROR;
}

static int AttrOff_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int attrs;
  Tcl_GetIntFromObj(interp, objv[1], &attrs);

  /* return value is not important */
  int result= attroff(attrs);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while attroff", NULL);
  return TCL_ERROR;
}

static int WAttrOff_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"wattroff window attributes\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int attrs;
  Tcl_GetIntFromObj(interp, objv[2], &attrs);

  /* return value is not important */
  int result= wattroff(win, attrs);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while wattroff", NULL);
  return TCL_ERROR;
}

static int AttrOn_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"attron attributes\"");

  int attrs;
  Tcl_GetIntFromObj(interp, objv[1], &attrs);

  /* return value is not important */
  int result= attron(attrs);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while attron", NULL);
  return TCL_ERROR;
}

static int WAttrOn_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"wattron window attributes\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int attrs;
  Tcl_GetIntFromObj(interp, objv[2], &attrs);

  /* return value is not important */
  int result= wattron(win, attrs);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while wattron", NULL);
  return TCL_ERROR;
}

static int WAttrSet_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"wattrset window attributes\"");

  WINDOW* window;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), window);

  int attrs;
  Tcl_GetIntFromObj(interp, objv[2], &attrs);

  /* return value is not important */
  int result= wattrset(window, attrs);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while wattrset", NULL);
  return TCL_ERROR;
}

static int Color_Set_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"color_set color_pair_number\"");

  int color_pair_number;
  Tcl_GetIntFromObj(interp, objv[1], &color_pair_number);

  int result= color_set(color_pair_number, NULL);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while color_set", NULL);
  return TCL_ERROR;
}

static int WColor_Set_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"wcolor_set window color_pair_number\"");

  WINDOW* window;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), window);
  
  int color_pair_number;
  Tcl_GetIntFromObj(interp, objv[2], &color_pair_number);

  int result= wcolor_set(window, color_pair_number, NULL);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while wcolor_set", NULL);
  return TCL_ERROR;
}

static int Standend_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"standend\"");

  int result= standend();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while standend", NULL);
  return TCL_ERROR;
}

#endif	/* ATTRIBUTES_H */
