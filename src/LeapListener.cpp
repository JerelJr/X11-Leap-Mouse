#include "InputEvents.h"
#include "LeapListener.h"

using namespace Leap;

CustomListener::CustomListener() {}

CustomListener::~CustomListener() {}

void CustomListener::onInit(const Controller &controller) {}

void CustomListener::onConnect(const Controller &controller)
{
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);

  /*Configurations*/
  controller.config().setFloat("Gesture.ScreenTap.MinForwardVelocity", 1.0);
  controller.config().setFloat("Gesture.ScreenTap.HistorySeconds", .1);
  controller.config().setFloat("Gesture.ScreenTap.MinDistance", .5);
  controller.config().save();
}

void CustomListener::onDisconnect(const Controller &controller) {}

void CustomListener::onExit(const Controller &controller) {}

void CustomListener::onFrame(const Controller &controller)
{
  /*Leap Declarations*/
  const Frame frame = controller.frame();
  InteractionBox box = frame.interactionBox();
  Leap::FingerList allFingers = frame.fingers();
  Leap::GestureList gestures = frame.gestures();
  MouseEvent me;
  /*Loop through fingers in frame*/
  for (FingerList::const_iterator fl = allFingers.begin();
       fl != allFingers.end(); fl++)
  {
    if ((*fl).type() == Finger::TYPE_INDEX)
    {
      Vector fingerPos = (*fl).tipPosition();
      Vector boxFingerPos = box.normalizePoint(fingerPos);

      me.mouseMoveAbsolute((me.width[0] * boxFingerPos.x),
                           me.height[0] * (1 - boxFingerPos.y));

      std::cout << "X:" << me.width[0] * boxFingerPos.x << std::endl;
      std::cout << "Y:" << me.height[0] * (1 - boxFingerPos.y) << std::endl;
    }
  }

  for (GestureList::const_iterator gl = gestures.begin();
       gl != gestures.end(); gl++)
  {
    switch ((*gl).type())
    {
    case Leap::Gesture::TYPE_SCREEN_TAP:
      std::cout << "Screen tap detected" << std::endl;
      me.mouseClick();
      break;
      
    default:
      break;
    }
  }
}
