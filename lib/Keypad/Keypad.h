// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#ifndef ARDUINO_ACCESS_SYSTEM_KEYPAD_
#define ARDUINO_ACCESS_SYSTEM_KEYPAD_

#include "Key.h"

// Arduino versioning.
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#ifndef INPUT_PULLUP
#warning "Using  pinMode() INPUT_PULLUP AVR emulation"
#define INPUT_PULLUP 0x2
#define pinMode(_pin, _mode) _mypinMode(_pin, _mode)
#define _mypinMode(_pin, _mode)    \
	do                             \
	{                              \
		if (_mode == INPUT_PULLUP) \
			pinMode(_pin, INPUT);  \
		digitalWrite(_pin, 1);     \
		if (_mode != INPUT_PULLUP) \
			pinMode(_pin, _mode);  \
	} while (0)
#endif

#define OPEN LOW
#define CLOSED HIGH

typedef char KeypadEvent;
typedef unsigned int uint;
typedef unsigned long ulong;


typedef struct
{
	byte rows;
	byte columns;
} KeypadSize;

#define LIST_MAX 10 // Max number of keys on the active list.
#define MAPSIZE 10	// MAPSIZE is the number of rows (times 16 columns)
#define makeKeymap(x) ((char *)x)

// class Keypad : public Key, public HAL_obj {
class Keypad : public Key
{
public:
	/// @brief Keypad constructor
	///
	/// @param userKeymap The keymap to use for the keypad
	/// @param row An array of pins connected to the keypad rows
	/// @param col An array of pins connected to the keypad columns
	/// @param numRows The number of rows in the keypad
	/// @param numCols The number of columns in the keypad
	Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);

	/// @brief Set the pin mode for a specific pin
	///
	/// @param pinNum The pin number
	/// @param mode The mode to set for the pin
	virtual void pin_mode(byte pinNum, byte mode) { pinMode(pinNum, mode); }

	/// @brief Write a level to a specific pin
	///
	/// @param pinNum The pin number
	/// @param level The level to write to the pin
	virtual void pin_write(byte pinNum, boolean level) { digitalWrite(pinNum, level); }

	/// @brief Read the level from a specific pin
	///
	/// @param pinNum The pin number
	/// @return The level read from the pin
	virtual int pin_read(byte pinNum) { return digitalRead(pinNum); }


	uint bitMap[MAPSIZE]; // 10 row x 16 column array of bits. Except Due which has 32 columns.
	Key key[LIST_MAX];
	unsigned long holdTimer;


	/// @brief Get the key value from the keypad
	///
	/// @return The key value as a character
	char getKey();

	/// @brief Update the state of the keys
	///
	/// @return True if any keys have changed state, false otherwise
	bool getKeys();

	/// @brief Get the state of the keypad
	///
	/// @return The current state of the keypad
	KeyState getState();

	/// @brief Initialize the keypad with the specified keymap
	///
	/// @param userKeymap The keymap to use for the keypad
	void begin(char *userKeymap);

	/// @brief Check if a specific key is pressed
	///
	/// @param keyChar The character representing the key
	/// @return True if the key is pressed, false otherwise
	bool isPressed(char keyChar);

	/// @brief Set the debounce time for the keypad
	///
	/// @param debounceTime The debounce time in milliseconds
	void setDebounceTime(uint);

	/// @brief Set the hold time for the keypad
	///
	/// @param holdTime The hold time in milliseconds
	void setHoldTime(uint);

	/// @brief Add an event listener for keypad events
	///
	/// @param listener The event listener function to add
	void addEventListener(void (*listener)(char));

	/// @brief Find the index of a key in the active key list by character value
	///
	/// @param keyChar The character representing the key
	/// @return The index of the key in the active key list, or -1 if not found
	int findInList(char keyChar);

	/// @brief Find the index of a key in the active key list by key code
	///
	/// @param keyCode The key code representing the key
	/// @return The index of the key in the active key list, or -1 if not found
	int findInList(int keyCode);

	/// @brief Wait for a key press and return the pressed key
	///
	/// @return The pressed key as a character
	char waitForKey();

	/// @brief Check if the state of any key has changed
	///
	/// @return True if the state of any key has changed, false otherwise
	bool keyStateChanged();

	/// @brief Get the number of keys in the active key list
	///
	/// @return The number of keys in the active key list
	byte numKeys();

private:
	unsigned long startTime;
	char *keymap;
	byte *rowPins;
	byte *columnPins;
	KeypadSize sizeKpd;
	uint debounceTime;
	uint holdTime;
	bool single_key;

	void scanKeys();
	bool updateList();
	void nextKeyState(byte n, boolean button);
	void transitionTo(byte n, KeyState nextState);
	void (*keypadEventListener)(char);
};

#endif // ARDUINO_ACCESS_SYSTEM_KEYPAD_