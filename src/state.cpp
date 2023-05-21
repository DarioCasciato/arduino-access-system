// =========================================
// arduino-access-system | Dario Casciato
// =========================================

#include <Arduino.h>
#include "state.h"
#include "General.h"

using namespace General;




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
    EventsNoMaster::present,
    EventsNoMaster::edgeNeg
};

struct EdgeEvents eventsIdle
{
    EventsIdle::edgePos,
    EventsIdle::present,
    EventsIdle::edgeNeg
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

    // Function to drive the state machine
    void stateDriver()
    {
        switch (State::state)
        {
        case States::st_noMaster: State::stateNoMaster(); break;
        case States::st_idle: State::stateIdle(); break;
        case States::st_keying: State::stateKeying(); break;

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
    }

    // Handler for the keying state
    void stateKeying()
    {
        eventCaller(eventsKeying);
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

    }

    void present() // Event handling for tag present in the no master state
    {

    }

    void edgeNeg() // Event handling for negative edge in the no master state
    {

    }
} // namespace EventsNoMaster

// Event functions for the idle state
namespace EventsIdle
{
    void edgePos() // Event handling for positive edge in the idle state
    {

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

    }

    void present() // Event handling for tag present in the keying state
    {

    }

    void edgeNeg() // Event handling for negative edge in the keying state
    {

    }
} // namespace EventsKeying

//------------------------------------------------------------------------------
