/*
Adapted from:
http://www.arduino.cc/en/Tutorial/Debounce
*/


#include "Button.h"

Button::Button(const int buttonPin) : pin(buttonPin)
{
	pinMode(pin, INPUT_PULLUP);
}

Button::~Button()
{
}

void Button::checkButtonState()
{
	// read the state of the switch into a local variable:
	int reading = digitalRead(pin);

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (reading != lastState) {
		// reset the debouncing timer
		lastDebounceTime_ms = millis();
	}

	if ((millis() - lastDebounceTime_ms) > debounceDelay_ms) {
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:

		// if the button state has changed:
		if (reading != currState) {
			currState = reading;
		}
	}

	// save the reading.  Next time through the loop,
	// it'll be the lastButtonState:
	lastState = reading;
}

bool Button::isPressed()
{
	return (currState == HIGH) ? true : false;
}
