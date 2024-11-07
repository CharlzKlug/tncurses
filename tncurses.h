#ifndef TNCURSES_H
#define TNCURSES_H

#include <ncurses.h>

#define COLORS_COUNT 8
char *colors_strings[(COLORS_COUNT)] = {
  "COLOR_BLACK",
  "COLOR_RED",
  "COLOR_GREEN",
  "COLOR_YELLOW",
  "COLOR_BLUE",
  "COLOR_MAGENTA",
  "COLOR_CYAN",
  "COLOR_WHITE"
};

NCURSES_COLOR_T ncurses_colors[(COLORS_COUNT)] = {
  COLOR_BLACK,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
  COLOR_WHITE
};

#define CHECK_ARGUMENTS(arg_num, err_msg) do {		\
    if (objc != (arg_num)) {				\
      Tcl_AppendResult(interp, (err_msg), NULL);	\
      return TCL_ERROR;					\
    }							\
  } while (0)

#define CHECK_ARGUMENTS_GE(arg_num, err_msg) do {		\
    if (objc < (arg_num)) {				\
      Tcl_AppendResult(interp, (err_msg), NULL);	\
      return TCL_ERROR;					\
    }							\
  } while (0)

#define STRING_TO_WINDOW(string_buffer, window) do {		\
    if (strcmp(string_buffer, "stdscr") == 0 ||		\
	strcmp(string_buffer, "STDSCR") == 0) {		\
      window= stdscr;						\
    } else {							\
      if (strcmp(string_buffer, "curscr") == 0 ||		\
	  strcmp(string_buffer, "CURSCR") == 0 ) {		\
	window= curscr;					\
      } else {							\
	void* pointer= NULL;					\
	if (string_buffer == NULL ||				\
	    sscanf(string_buffer, "%p", &pointer) != 1) {	\
	  Tcl_AppendResult(interp, "Bad scan", NULL);		\
	  return TCL_ERROR;					\
	}							\
	window= (WINDOW*)pointer;				\
      }							\
    }								\
  } while (0)

#define STRING_TO_VOID(string_buffer, voidptr) do {			\
    if (strcmp(string_buffer, "NULL") == 0) {				\
      voidptr= NULL;							\
    } else {								\
      void* pointer= NULL;						\
      if (string_buffer == NULL ||					\
	  sscanf(string_buffer, "%p", &pointer) != 1) {			\
	Tcl_AppendResult(interp, "Bad scan", NULL);			\
	return TCL_ERROR;						\
      }									\
      voidptr= (void*)pointer;						\
    }									\
  } while (0)

#define STRING_TO_BOOL(string_buffer, bool_value) do {		\
    if (strcmp(string_buffer, "true") == 0 ||			\
	strcmp(string_buffer, "TRUE") == 0) {			\
      bool_value= TRUE;						\
    } else if (strcmp(string_buffer, "false") == 0 ||		\
	       strcmp(string_buffer, "FALSE") == 0) {		\
      bool_value= FALSE;					\
    } else {							\
      Tcl_AppendResult(interp, "Bad scan bool value", NULL);	\
      return TCL_ERROR;						\
    }								\
  } while (0)

#define STRING_TO_MMASK_T(string_buffer, somemask) do {			\
    if (strcmp(string_buffer, "NULL") == 0) {				\
      somemask= NULL;							\
    } else {								\
      void* pointer= NULL;						\
      if (string_buffer == NULL ||					\
	  sscanf(string_buffer, "%p", &pointer) != 1) {			\
	Tcl_AppendResult(interp, "Bad scan", NULL);			\
	return TCL_ERROR;						\
      }									\
      somemask= (mmask_t*)pointer;					\
    }									\
  } while (0)

/* Auxiliary function. Maps string to color */
int string_to_color(char *input_string,
		    NCURSES_COLOR_T *output_color) {
  for (int i = 0; i < (COLORS_COUNT); i++) {
    if (strcmp(input_string, colors_strings[i]) == 0) {
      *output_color= ncurses_colors[i];
      return i;
    }
  }
  return (-1);
}

#endif /* TNCURSES_H */
