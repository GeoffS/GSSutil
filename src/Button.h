#ifndef _DEBOUNCE_h
#define _DEBOUNCE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Button
{
public:
	Button(const int buttonPin);
	~Button();

	void checkButtonState();
	bool isPressed();
	bool wasClicked();

private:
	const int pin;
	int currState;                  // the current reading from the input pin
	bool _wasClicked = false;
	int lastState = LOW;            // the previous reading from the input pin
	long lastDebounceTime_ms = 0;      // the last time the output pin was toggled
	const long debounceDelay_ms = 20;  // the debounce time; increase if the output flickers
};


#endif

