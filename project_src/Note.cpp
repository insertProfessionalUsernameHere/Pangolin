#include "Note.hpp"
#include <math.h>
#include "Debug.hpp"
#include <cstdlib>

#define TABLE_SIZE (1600)

Note::Note()
  : active_(false), 
    noteNum_(69), phase_(0), samplingIncrement_(0), waveform_(0), 
    velocity_(1.0f)
{
  //this constructor intentionally left blank
}

void Note::Init(float *waveform)
{
  waveform_ = waveform;
}

void Note::Play(int noteNum, int velocity, long durationInMicro)
{
  currentVolume_ = velocity_ = static_cast<float>(velocity);
  noteNum_ = noteNum;
  samplingIncrement_ = powf(2, (static_cast<float>(noteNum_) - 21.0f) / 12.0f);
  active_ = true;
  adsr_.Init(durationInMicro, velocity_);
}

void Note::Stop()
{
  active_ = false;
}

float Note::GetSample()
{
  float sample = 0;
  if(waveform_)
  {
    //fix the phase drop-off when freshly inactive
    if(active_)
    {
      phase_ += samplingIncrement_;
      if(phase_ >= TABLE_SIZE)
      {
        currentVolume_ = adsr_.GetEnvelope();
        phase_ -= TABLE_SIZE;
      }
      sample = waveform_[(int)phase_];
    }
    else if(phase_ != 0)
    {
      phase_ += samplingIncrement_;
      if(phase_ >= TABLE_SIZE)
      {
        phase_ = 0;
      }
      else
      {
        sample = waveform_[(int)phase_];
      }
    }
  } 
  return sample * currentVolume_;
}

bool Note::IsPlaying()
{
  return active_;
}

bool Note::IsNote(int noteNum)
{
  return noteNum_ == noteNum;
}
