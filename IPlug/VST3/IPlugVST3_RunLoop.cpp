/*
 ==============================================================================
 
 This file is part of the iPlug 2 library. Copyright (C) the iPlug 2 developers. 
 
 See LICENSE.txt for  more info.
 
 ==============================================================================
*/


#include "IPlugVST3_RunLoop.h"

BEGIN_IPLUG_NAMESPACE

struct VST3Timer : Steinberg::Linux::ITimerHandler, public Steinberg::FObject
{
  std::function<void()> callback;

  void PLUGIN_API onTimer() override
  {
    callback();
  }

  DELEGATE_REFCOUNT (Steinberg::FObject)
  DEFINE_INTERFACES
    DEF_INTERFACE (Steinberg::Linux::ITimerHandler)
  END_DEFINE_INTERFACES (Steinberg::FObject)
};

struct EventHandler : Steinberg::Linux::IEventHandler, public Steinberg::FObject
{
  IPlugVST3_RunLoop* ev;

  void PLUGIN_API onFDIsSet (Steinberg::Linux::FileDescriptor) override 
  { 

  }

  DELEGATE_REFCOUNT (Steinberg::FObject)
  DEFINE_INTERFACES
    DEF_INTERFACE (Steinberg::Linux::IEventHandler)
  END_DEFINE_INTERFACES (Steinberg::FObject)
};

struct TimerHandler : Steinberg::Linux::ITimerHandler, public Steinberg::FObject
{
  IPlugVST3_RunLoop* ev;

  void PLUGIN_API onTimer () override
  {
    ev->runLoop->unregisterTimer(this);
    ev->tHandlerSet = false;
  }

  DELEGATE_REFCOUNT (Steinberg::FObject)
  DEFINE_INTERFACES
    DEF_INTERFACE (Steinberg::Linux::ITimerHandler)
  END_DEFINE_INTERFACES (Steinberg::FObject)
};

IPlugVST3_RunLoop* IPlugVST3_RunLoop::Create(Steinberg::FUnknown *frame)
{
  auto ev = new IPlugVST3_RunLoop();

  Steinberg::FUnknownPtr<Steinberg::Linux::IRunLoop> runLoop(frame);
  ev->runLoop = runLoop;
  if(!ev->runLoop)
  {
    delete ev;
    return nullptr;
  }

  ev->eHandlerSet = false;
  ev->tHandlerSet = false;
  ev->eHandler = new EventHandler();
  ev->eHandler->ev = ev;
  ev->tHandler = new TimerHandler();
  ev->tHandler->ev = ev;
  
  return ev;
}

void IPlugVST3_RunLoop::Destroy(IPlugVST3_RunLoop* self)
{
    // printf("Releasing eHandeler %u\n", ev->eHandler->getRefCount()); // was checking refCounter is 1...
    // printf("Releasing tHandler %u\n", ev->tHandler->getRefCount());
    self->eHandler->release();
    self->tHandler->release();

    int i = 0;
    while ((i = self->mTimers.GetSize()) > 0)
    {
      self->DestroyTimer(self->mTimers.Get(i - 1));
    }

    delete self;

}

VST3Timer* IPlugVST3_RunLoop::CreateTimer(std::function<void()> callback, int msec)
{
  auto tm = new VST3Timer();
  tm->callback = callback;
  const int num =  mTimers.GetSize();
  if (runLoop->registerTimer(tm, msec) == Steinberg::kResultOk)
  {
    mTimers.Add(tm);
    return tm;
  }
  else
  {
    delete tm;
  }

  return {};
}

void IPlugVST3_RunLoop::DestroyTimer(VST3Timer* timer)
{
  runLoop->unregisterTimer(timer);
  mTimers.Delete(mTimers.FindR(timer));
  delete timer;
}

END_IPLUG_NAMESPACE
