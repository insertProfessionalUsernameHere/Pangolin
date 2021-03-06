#include "Timer.hpp"
#include <math.h>
#include <iostream>

using namespace std::chrono;

void Timer::Start(long durationInMicro)
{
  active_ = true;
  currentTime_ = startTime_ = high_resolution_clock::now();
  durationInMicro_ = durationInMicro;
}

//place in any function called exactly once per frame
bool Timer::Update()
{
  if(active_)
  {
    //update clock
    currentTime_ = high_resolution_clock::now();
    if(duration_cast<microseconds>(currentTime_ - startTime_).count() >= durationInMicro_)
    {
      active_ = false;
    }
  }
  return active_;
}

bool Timer::IsActive()
{
  return active_;
}
