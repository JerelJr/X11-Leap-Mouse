#include <iostream>
#include <signal.h>
#include "LeapListener.h"

static CustomListener listener;
static Leap::Controller controller;

/*handle interrupt signals*/
void handle_interrupt(int sig) {
  controller.removeListener(listener);
  std::cout << "Exiting with signal: " << sig << std::endl; 

  exit(sig);
}

int catch_signal(int sig, void (*handler) (int)) {
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  
  return sigaction(sig, &action, NULL);
}

int main(int argc, char const *argv[])
{
    
    controller.addListener(listener);
 
    signal(SIGINT, handle_interrupt); 
    std::cin.get();
    
    return 0;
}

