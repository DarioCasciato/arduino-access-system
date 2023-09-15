
# Arduino Access Control System

This repository contains the code for an Arduino-based access control system that uses an RFID reader, a keypad, and a status LED for real-time feedback. The system is designed for secure access management, allowing for user whitelisting via a master RFID card and access via a unique PIN or registered RFID cards.

## Features

- RFID-based access control
- Keypad for PIN entry
- Status LED for immediate visual feedback
- Master RFID card for system configuration and user whitelisting
- Modular codebase for easy customization and scaling

## Prerequisites

To use this repository, you need to have the following installed:

- [Arduino IDE](https://www.arduino.cc/en/software)
- [PlatformIO Core](https://platformio.org/platformio-ide) (Optional)
- [Git](https://git-scm.com/)

## Getting Started

1. Clone the repository to your local machine.
   ```
   git clone https://github.com/DarioCasciato/arduino-access-system.git
   ```
2. Navigate to the project directory.
   ```
   cd arduino-access-system
   ```
3. Open the project in Arduino IDE or your preferred IDE.
4. Build and upload the firmware to your Arduino board.

## Directory Structure

```
├───include
│       README
│
├───lib
│   ├───Buzzer
│   ├───EdgeDetection
│   ├───Keypad
│   ├───LED
│   ├───SK6812
│   └───Timer
│
├───src
│       configurations.cpp
│       configurations.h
│       General.cpp
│       General.h
│       hardware.cpp
│       hardware.h
│       main.cpp
│       rfid_utility.cpp
│       rfid_utility.h
│       signalisation.cpp
│       signalisation.h
│       state.cpp
│       state.h
│       whitelist.cpp
│       whitelist.h
│
└───test
        README
```

- **`src/`**: Contains the main firmware code, including configurations, hardware interactions, and state management.
- **`lib/`**: Contains libraries for various hardware components like the buzzer, keypad, and LED.
- **`include/`**: Additional header files can be placed here.
- **`test/`**: For test-related code and documentation.

## Contributing

Contributions to improve this repository are always welcome. If you find any issues or have suggestions for enhancements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to use it as a starting point for your own access control projects.

## Resources

- [Arduino Reference](https://www.arduino.cc/reference/en/)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [Arduino Forum](https://forum.arduino.cc/)
