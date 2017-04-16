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
	Button(const int buttonPin, const bool isPulldownButton);
	~Button();

	void checkButtonState();
	bool isPressed();
	long pressedTime_ms();
	bool updateValue();
	bool wasClicked();
	void resetClicked();
	void setDebounceDelay_ms(int newDebounceDelay_ms);

private:
	int buttonPressedValue = LOW;
	int buttonReleasedValue = HIGH;
	const int pin;
	int currState;                  // the current reading from the input pin
	long currStateTime_ms;          // How long we've been in the current state.
	long lastUpdateTime_ms;
	long repeatTime_ms;
	bool _wasClicked = false;
	int lastState;            // the previous reading from the input pin
	unsigned long lastDebounceTime_ms = 0;      // the last time the output pin was toggled
	unsigned long debounceDelay_ms = 20;  // the debounce time; increase if the output flickers
};


#endif

