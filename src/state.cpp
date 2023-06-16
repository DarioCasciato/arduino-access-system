// =============================================================================
// arduino-access-system | Dario Casciato
// =============================================================================

#include <Arduino.h>
#include <ctype.h>
#include "state.h"
#include "General.h"
#include "signalisation.h"
#include "Timer.h"

using namespace General;

Timer timeout;
Timer timeaccess;
Timer timepresented;
Timer timeKeypad;

void none();
void exitPinEntry();
void accessGranted();

bool flag_timeout = false;
bool flag_keyingStarted = false;
bool flag_resettedMaster = false;
bool flag_keyingResetWL = false;

extern RGBW color_red;
extern RGBW color_green;
extern RGBW color_off;

String pin = "";

//------------------------------------------------------------------------------

// Structure defining events for edge detection
struct EdgeEvents
{
    void (* onEdgePos)();    // Function pointer for positive edge event
    void (* onPresent)();    // Function pointer for present event
    void (* onEdgeNeg)();    // Function pointer for negative edge event
};

// Define events for different states
struct EdgeEvents eventsNoMaster
{
    EventsNoMaster::edgePos,
    none,
    EventsNoMaster::edgeNeg
};

struct EdgeEvents eventsIdle
{
    EventsIdle::edgePos,
    none,
    none
};

struct EdgeEvents eventsKeying
{
    EventsKeying::edgePos,
    EventsKeying::present,
    EventsKeying::edgeNeg
};


//------------------------------------------------------------------------------

namespace State
{
    States state = States::st_noMaster;

    void onStart()
    {
        if (whitelist.getRegisteredMaster() != 0 && whitelist.getRegisteredMaster() != 0xFFFF)
        {
            state = States::st_idle;
        }
        else
        {
            state = States::st_noMaster;
        }
    }


    // Function to drive the state machine
    void stateDriver()
    {
        switch (state)
        {
        case States::st_noMaster: State::stateNoMaster(); break;
        case States::st_idle: State::stateIdle(); break;
        case States::st_pinEntry: State::statePinEntry(); break;
        case States::st_keying: State::stateKeying(); break;
        case States::st_keypadConfig: State::stateKeypadConfig(); break;

        default:
            goto exception;
            break;
        }

        return;

        exception:
            for(;;) { signalize.exception(); }
    }


    // Handler for the no master state
    void stateNoMaster()
    {
        eventCaller(eventsNoMaster);
    }

    // Handler for the idle state
    void stateIdle()
    {
        eventCaller(eventsIdle);

        if(General::keypad_key)
        {
            if(General::whitelist.isPinRegistered())
            {
                if(isdigit(General::keypad_key))
                {
                    state = States::st_pinEntry;
                    pin += General::keypad_key;
                    signalize.pinEntry();
                    timeKeypad.start();
                }
            }
            else
            {
                signalize.reject();
            }
        }
    }

    // Handler for the pin entry state
    void statePinEntry()
    {
        if(General::keypad_key)
            timeKeypad.start();

        if(General::keypad_key && pin.length() < 7)
        {
            if(isdigit(General::keypad_key))
            {
                pin += General::keypad_key;
            }
        }

        if(General::keypad_key == 'C')
        {
            signalize.permDenied();
            exitPinEntry();
        }

        if(General::keypad_key == 'E')
        {
            if(whitelist.pinCheck(pin))
            {
                accessGranted();
            }
            else
            {
                signalize.permDenied();
            }

            exitPinEntry();
        }

        if(timeKeypad.elapsed(TIME_TIMEOUT * 1000))
        {
            signalize.permDenied();
            exitPinEntry();
        }
    }

    // Handler for the keying state
    void stateKeying()
    {
        eventCaller(eventsKeying);

        if(General::keypad_key)
        {
            if(isdigit(General::keypad_key))
            {
                pin += General::keypad_key;
                flag_timeout = false;
                timeKeypad.start();
                signalize.pinEntry();
                state = States::st_keypadConfig;
            }
        }

        // Timeout Handler
        if(flag_timeout)
        {
            if(timeout.elapsed(TIME_TIMEOUT * 1000))  // Round to ms
            {
                signalize.endKeying();
                flag_timeout = false;
                exitPinEntry();
            }
        }
    }

    // Handler for the keypad configuration state
    void stateKeypadConfig()
    {
        if(General::keypad_key)
            timeKeypad.start();

        if(General::keypad_key && pin.length() < 6)
        {
            if(isdigit(General::keypad_key))
            {
                pin += General::keypad_key;
            }
        }

        if(General::keypad_key == 'C')
        {
            signalize.endKeying();
            timeout.stop();
            exitPinEntry();
        }

        if(General::keypad_key == 'E')
        {
            if(pin.length() >= 4 && pin.length() <= 6)
            {
                whitelist.pinSet(pin);
                signalize.positive();
                pin = "";
                timeKeypad.stop();
                timeout.start();
                flag_timeout = true;
                state = States::st_keying;
            }
            else
            {
                signalize.permDenied();
                timeout.stop();
                exitPinEntry();
            }
        }

        if(timeKeypad.elapsed(TIME_TIMEOUT * 1000))
        {
            signalize.endKeying();
            exitPinEntry();
        }
    }


    // Function to call appropriate events based on state
    void eventCaller(EdgeEvents state)
    {
        if (tagAvailable.getEdgePos())
        {
            state.onEdgePos();
        }

        if (tagAvailable.getActState())
        {
            state.onPresent();
        }

        if (tagAvailable.getEdgeNeg())
        {
            state.onEdgeNeg();
        }
    }
} // namespace State

//------------------------------------------------------------------------------

// Event functions for the no master state
namespace EventsNoMaster
{
    void edgePos() // Event handling for positive edge in the no master state
    {
        if(!flag_resettedMaster && properties.isMaster)
        {
            whitelist.masterSet(properties.uid);

            flag_keyingStarted = true;
            State::state = State::st_keying;
        }
    }

    void present() // Event handling for tag present in the no master state
    {

    }

    void edgeNeg() // Event handling for negative edge in the no master state
    {
        if(flag_resettedMaster)
        {
            flag_resettedMaster = false;
        }
    }
} // namespace EventsNoMaster

// Event functions for the idle state
namespace EventsIdle
{
    void edgePos() // Event handling for positive edge in the idle state
    {
        if(properties.isMaster)
        {
            if(properties.uid == whitelist.getRegisteredMaster())
            {
                flag_keyingStarted = true;
                State::state = State::st_keying;
            }
            else
            {
                signalize.reject();
            }
        }
        else    // is User
        {
            if(whitelist.isMember(properties.uid))
            {
                if(VERIFICATION_ON_RFID)
                {
                    State::state = State::st_pinEntry;
                    signalize.pinEntry();
                    timeKeypad.start();
                }
                else
                {
                    accessGranted();
                }
            }
            else if(properties.uid != 0)
            {
                signalize.permDenied();
            }
        }
    }

    void present() // Event handling for tag present in the idle state
    {

    }

    void edgeNeg() // Event handling for negative edge in the idle state
    {

    }
} // namespace EventsIdle

// Event functions for the keying state
namespace EventsKeying
{
    void edgePos() // Event handling for positive edge in the keying state
    {
        // Not registered Master presented
        if(properties.isMaster && properties.uid != whitelist.getRegisteredMaster())
        {
            signalize.endKeying();
            timepresented.stop();
            flag_timeout = false;
            timeout.stop();
            State::state = State::st_idle;
        }
        else
        {
            timepresented.start();
        }
    }

    void present() // Event handling for tag present in the keying state
    {
        flag_timeout = false;   //  Reset timeout when Badge presented
        timeout.stop();         //

        if(!properties.isMaster || properties.uid == whitelist.getRegisteredMaster())
        {
            Hardware::ledSignalization.set_color(0, color_green);
        }

        // remove user
        if (timepresented.elapsed(5000) &&
            !properties.isMaster &&
            whitelist.isMember(properties.uid) )
        {
            whitelist.remove(properties.uid);
            signalize.removedMember();
        }

        // Reset options
        if(properties.isMaster)
        {   // Reset Whitelist after 10 seconds
            if(timepresented.elapsed(10000) && !flag_keyingResetWL)
            {
                flag_keyingResetWL = 1;

                Hardware::ledSignalization.set_color(0, color_off);
                signalize.resetWhitelist();

                whitelist.reset();
            }
            // Reset Master after 15 seconds
            if(timepresented.elapsed(15000) && !flag_resettedMaster)
            {
                flag_resettedMaster = 1;

                signalize.fullReset();
                whitelist.reset();
                whitelist.masterReset();
                whitelist.pinReset();

                timepresented.stop();
                State::state = State::st_noMaster;
            }
        }

    }

    void edgeNeg() // Event handling for negative edge in the keying state
    {
        if(!flag_resettedMaster)
        {
            flag_keyingResetWL = false;
            flag_timeout = false;

            Hardware::ledSignalization.set_color(0, color_off);

            if(properties.isMaster)
            {
                if(!timepresented.elapsed(10000))
                {
                    if(flag_keyingStarted)
                    {
                        signalize.positive();
                        timeout.start();
                        flag_timeout = true;
                        flag_keyingStarted = false;
                    }
                    else
                    {
                        signalize.endKeying();
                        flag_timeout = false;
                        timeout.stop();
                        State::state = State::st_idle;
                    }
                }
            }
            else
            {
                if(!timepresented.elapsed(5000))
                {
                    // add user to whitelist
                    if (whitelist.getWhitelistMemberCount() < WHITELIST_SIZE)
                    {
                        signalize.positiveSound();
                        whitelist.add(properties.uid);
                    }
                    else
                    {
                        signalize.whitelistFull();
                    }

                    timeout.start();
                    flag_timeout = true;
                }
            }
        }

        timepresented.stop();
    }
} // namespace EventsKeying


//------------------------------------------------------------------------------

void none()
{
    // Nothing
}

void accessGranted()
{
    timeaccess.start();
    Hardware::accessLED.on();
    signalize.positive();

    for(;;)
    {
        if(timeaccess.elapsed(OPEN_TIME * 1000))
            break;
    }

    timeaccess.stop();
    Hardware::accessLED.off();
}

void exitPinEntry()
{
    pin = "";
    timeKeypad.stop();
    State::state = State::st_idle;
}