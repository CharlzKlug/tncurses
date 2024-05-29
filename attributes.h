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
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

#endif	/* ATTRIBUTES_H */
