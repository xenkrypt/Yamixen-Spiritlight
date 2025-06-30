# Yamixen Spiritlight V1 – A DIY RGB Wearable Lighting System

Made with passion, perseverance, and a love for technology – by Tharunkrishna T H

**Yamixen Spiritlight V1** is a wearable, Bluetooth-controlled RGB lighting module designed for footwear. It features custom LED animations triggered by foot taps or BLE commands, intended for creative expression in dance, cosplay, or everyday tech flair.

## Features

- Bluetooth BLE control via mobile app
- Tactile button for real-time animation trigger
- Adjustable brightness and color using RGB values
- Multiple animations:
  - `Fade`: Smoothly fades out from selected color
  - `Diverge`: Colored dots emerge from heel and move forward towards the toes
  - `Rainbow`: Continuous flowing rainbow
  - `Solid Rainbow`: Uniform rainbow cycling
- Powered by a 1000mAh rechargeable Li-Po battery
- Built with Arduino IDE and MIT App Inventor

## Components Used

| Component                     | Description                                         |
|------------------------------|-----------------------------------------------------|
| ESP32-C3 Mini Dev Board      | Core MCU with BLE support                          |
| WS2812B RGB LED Strip (46 LEDs) | Individually addressable LEDs                  |
| TP4056 USB-C Charging Module | Safe Li-Po battery charging                         |
| 1000mAh Li-Po Battery        | Power source                                        |
| Tactile Button (4-pin)       | For foot-triggered control                         |
| Slide Switch (3-pin)         | On/Off functionality                                |
| Flexible Wires + Jumpers     | For connections                                     |
| Basic Soldering Equipment    | Solder iron, wire, flux, etc.                      |

## App Control

Developed using MIT App Inventor, the app allows wireless control through BLE.

### BLE Command Reference

| Command     | Function                                |
|-------------|-----------------------------------------|
| `1`         | Trigger `fade()` animation              |
| `2:<0–100>` | Set brightness (percentage)             |
| `3:(R,G,B)` | Set RGB color values                    |
| `4`         | Enable flowing rainbow mode             |
| `5`         | Enable solid rainbow mode               |
| `6`         | Trigger `diverge()` animation           |

## Arduino Code Overview

- Uses `Adafruit_NeoPixel` for LED control
- BLE libraries from `BLEDevice`, `BLEUtils`, and `BLEServer`
- Central color state and animation mode control
- Modular structure for future upgrades

## Repository Contents

- `Yamixen_Spiritlight_V1.ino` – Arduino code
- `App/SpiritlightApp.aia` – App Inventor source
- `README.md` – Project documentation

## How to Use

1. Flash the Arduino code to the ESP32-C3 Mini board
2. Power with Li-Po battery through TP4056 module
3. Install and run the MIT App Inventor app
4. Connect via BLE and use the app to control lights
5. Use foot tap (tactile button) to trigger effects

## Planned Upgrades

The Spiritlight project is still in active development. Upcoming improvements include:

- Replacement of tactile button with piezo or force-sensitive resistor for better comfort
- Battery level indicator with BLE updates
- Additional animation effects and smoother transitions
- Enhanced mobile UI with better user experience
- 3D-printed sole or housing for compact integration
- Modular plug-and-play architecture

## Feedback

If you’d like to contribute suggestions or improvements, please use this form:  
[Feedback Form](https://forms.gle/vGdGT9GdUuKqkLbk6)

## License

MIT License. Feel free to fork and modify with attribution.

Built with curiosity and creativity by Tharunkrishna T H
