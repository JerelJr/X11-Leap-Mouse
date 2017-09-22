#ifndef INPUTEVENTS_H
#define INPUTEVENTS_H

#include <stdio.h>
#include <X11/Xlib.h>

static int _XlibErrorHandler(Display* display, XErrorEvent* event){
  fprintf(stderr, "An error occured detecting the mouse position\n");
  return True;
}

class MouseEvent {
 public:
  int screenCount;
  int *height = NULL;
  int *width = NULL;
  int currentX, currentY;
  int win_x, win_y;
  unsigned int mask_return;
  Display *display = NULL;
  Window *root_windows = NULL;
  Window window_returned;

  MouseEvent();
  ~MouseEvent();
  void update();
  int mouseClick();
  int mousePress();
  int mouseRelease();
  int mouseMoveAbsolute(int x, int y);
  int mouseMoveRelative(int x, int y);
  
  
 private:
  int index;
  Bool result = False;

};
  
#endif
