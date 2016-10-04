#include "Blinker.h"

Blinker::Blinker(const unsigned long period_ms, const unsigned long duration_ms): period_ms(period_ms), duration_ms(duration_ms)
{
	nextTime_ms = 0;
	ledOn = false;
}

Blinker::~Blinker(){}

void Blinker::updateLedOnFlag(unsigned long int * now)
{
  if(*now >= nextTime_ms)
  {
    if(ledOn)
    {
      ledOn = false;
      nextTime_ms += (period_ms - duration_ms);
    }
    else
    {
      ledOn = true;
      nextTime_ms += duration_ms;
    }
  }
}
