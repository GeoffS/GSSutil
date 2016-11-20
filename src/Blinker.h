#ifndef BLINKER_H
#define BLINKER_H

#define ULONG unsigned long

class Blinker
{
public:
	Blinker(const unsigned long period_ms, const unsigned long duration_ms);
	~Blinker();
	void updateLedOnFlag(unsigned long int * now);
	bool ledOn;


private:
	const unsigned long period_ms;
	const unsigned long duration_ms;
	unsigned long nextTime_ms;
};

#endif // BLINKER_H



