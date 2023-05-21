// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#ifndef ARDUINO_ACCESS_SYSTEM_KEY_
#define ARDUINO_ACCESS_SYSTEM_KEY_

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"	// for digitalRead, digitalWrite, etc
#else
#include "WProgram.h"
#endif

#define OPEN LOW
#define CLOSED HIGH

typedef unsigned int uint;
typedef enum { IDLE, PRESSED, HOLD, RELEASED } KeyState;

const char NO_KEY = '\0';

class Key {
public:
	/// @brief Key constructor
	Key();

	/// @brief Key constructor with key character
	///
	/// @param userKeyChar The character representing the key
	Key(char userKeyChar);

	/// @brief Update the key with new state and status
	///
	/// @param userKeyChar The character representing the key
	/// @param userState The state of the key
	/// @param userStatus The status of the key
	void key_update(char userKeyChar, KeyState userState, boolean userStatus);

	// members
	char kchar;
	int kcode;
	KeyState kstate;
	boolean stateChanged;

private:
};

#endif // ARDUINO_ACCESS_SYSTEM_KEY_