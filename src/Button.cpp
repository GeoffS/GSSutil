/*
 Adapted from:
 http://www.arduino.cc/en/Tutorial/Debounce
 */

#include "Button.h"

Button::Button() {}

Button::Button(const int buttonPin) : Button(buttonPin, true) {}

Button::Button(const int buttonPin, const bool isPulldownButton)
{
	config(buttonPin, isPulldownButton);
}

Button::~Button() {}

void Button::config(const int buttonPin, const bool isPulldownButton)
{
	pin = buttonPin;

	if (isPulldownButton)
	{
		pinMode(pin, INPUT_PULLUP);
		repeatTime_ms = 300;
		buttonPressedValue = LOW;
		buttonReleasedValue = HIGH;
	}
	else
	{
		pinMode(pin, INPUT);
		repeatTime_ms = 300;
		buttonPressedValue = HIGH;
		buttonReleasedValue = LOW;
	}

	lastState = buttonReleasedValue;
}

void Button::checkButtonState()
{
	// Clicked only lasts one cycle:
	_wasClicked = false;

	// read the state of the switch into a local variable:
	int reading = digitalRead(pin);

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (reading != lastState)
	{
		// reset the debouncing timer
		lastDebounceTime_ms = millis();
	}

	if ((millis() - lastDebounceTime_ms) > debounceDelay_ms)
	{
		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:

		// if the button state has changed:
		if (reading != currState)
		{
			currState = reading;
			currStateTime_ms = millis();
			lastUpdateTime_ms = 0;
			repeatTime_ms = 300;

			// only toggle the LED if the new button state is HIGH
			if (currState == buttonPressedValue)
			{
				_wasClicked = true;
			}
		}
	}

	// save the reading.  Next time through the loop,
	// it'll be the lastButtonState:
	lastState = reading;
}

bool Button::isPressed()
{
	return (currState == buttonPressedValue) ? true : false;
}

long Button::pressedTime_ms()
{
	return millis() - currStateTime_ms;
}

bool Button::updateValue()
{
	if (wasClicked())
	{
		resetClicked();
		return true;
	}
	long pt = pressedTime_ms();
	if (pt > 4000)
		repeatTime_ms = 0;
	else if (pt > 3000)
		repeatTime_ms = 100;
	else if (pt > 1500)
		repeatTime_ms = 200;

	if ((pt - lastUpdateTime_ms) > repeatTime_ms)
	{
		lastUpdateTime_ms = pt;
		return true;
	}
	return false;
}

bool Button::wasClicked()
{
	return _wasClicked;
}

void Button::resetClicked()
{
	_wasClicked = false;
}

void Button::setDebounceDelay_ms(int newDebounceDelay_ms)
{
	debounceDelay_ms = newDebounceDelay_ms;
}
