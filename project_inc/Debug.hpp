#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <stdio.h>
#include "MidiEvent.h"

class MidiEvent;

namespace Debug
{
  enum MESSAGE_TYPE
  {
    NOTE_OFF,
    NOTE_ON,
    VOLUME_CHANGE,
    TEMPO_CHANGE,
  };
  
  class Stats
  {
    public:
      Stats();
      ~Stats();
      void AddNoteToStats(int keyNum, int channel, int velocity);
      void RemoveNoteFromStats(int keyNum, int channel);
      void SetTempo(double tempo);
      void SetFilename(const char* name);
      void Print_Stats();
      
    private:
      int keyNum_[32];
      int channel_[32];
      int velocity_[32];
      bool occupied_[32];
      double tempo_;
      const char* filename_;
  };
}

extern Debug::Stats stats;

#endif
