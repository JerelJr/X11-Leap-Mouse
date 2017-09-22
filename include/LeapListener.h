#ifndef LEAPLISTENER_H
#define LEAPLISTENER_H

#include "Leap.h"

class CustomListener : public Leap::Listener {
 public:
  CustomListener();
  ~CustomListener();
  virtual void onInit(const Leap::Controller &);
  virtual void onConnect(const Leap::Controller &);
  virtual void onDisconnect(const Leap::Controller &);
  virtual void onExit(const Leap::Controller &);
  virtual void onFrame(const Leap::Controller &);
  
 private:
};

#endif
