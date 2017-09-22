#include <assert.h>
#include <stdlib.h>
#include <X11/extensions/XTest.h>

#include "InputEvents.h"

MouseEvent::MouseEvent() {
  XSetErrorHandler(_XlibErrorHandler);
  update();
}
MouseEvent::~MouseEvent() {
  if (height != NULL)
    free(height);
  if (width != NULL)
    free(width);
  if (root_windows != NULL)
    free(root_windows);
  if (display != NULL)
    XCloseDisplay(display);

}

void MouseEvent::update() {
  if (height != NULL)
    free(height);
  if (width != NULL)
    free(width);
  if (root_windows != NULL)
    free(root_windows);
  if (display != NULL)
    XCloseDisplay(display);

  display = XOpenDisplay(NULL);
  assert(display);
  screenCount = XScreenCount(display);
  height = (int *)malloc(sizeof(int) * screenCount);
  width = (int *)malloc(sizeof(int) * screenCount);
  root_windows = (Window *)malloc(sizeof(Window) * screenCount);

  for (index = 0; index < screenCount; index++)
    {
      root_windows[index] = XRootWindow(display, index);
    }
  for (index = 0; index < screenCount && result != True; index++)
    {
      result = XQueryPointer(display, root_windows[index], &window_returned,
			     &window_returned, &currentX, &currentY,
			     &win_x, &win_y, &mask_return);
      width[index] = XDisplayWidth(display, index);
      height[index] = XDisplayHeight(display, index);
    }
  if (result != True)
    {
      fprintf(stderr, "No mouse found.\n");
    }
}

int MouseEvent::mouseClick() {
  XLockDisplay(display);
  
  XTestFakeButtonEvent(display, Button1, True, CurrentTime);
  XFlush(display);
	  
  XTestFakeButtonEvent(display, Button1, False, CurrentTime);
  XFlush(display);
  
  XUnlockDisplay(display);
  
  return 0;
}

int MouseEvent::mousePress() {
  XLockDisplay(display);

  XTestFakeButtonEvent(display, Button1, True, CurrentTime);
  XFlush(display);

  XUnlockDisplay(display);

  return 0;
}

int MouseEvent::mouseRelease() {
  XLockDisplay(display);

  XTestFakeButtonEvent(display, Button1, False, CurrentTime);
  XFlush(display);

  XUnlockDisplay(display);
  
  return 0;
}

int MouseEvent::mouseMoveAbsolute(int x, int y) {
  XLockDisplay(display);
  
  XTestFakeMotionEvent(display, -1, x, y, CurrentTime);
  XFlush(display);

  XUnlockDisplay(display);
  
  return 0;
}

int MouseEvent::mouseMoveRelative(int x, int y) {
  XLockDisplay(display);
  
  XTestFakeRelativeMotionEvent(display, x, y, CurrentTime);
  XFlush(display);

  XUnlockDisplay(display);
  
  return 0;
}
