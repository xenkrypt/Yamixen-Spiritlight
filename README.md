# 🌀 Yamixen Spiritlight V1 – A DIY RGB Wearable Lighting System

> Made with passion, solder burns, and RGB dreams – by [Tharunkrishna T H](https://www.linkedin.com/in/tharunkrishna/)

**Yamixen Spiritlight V1** is a wearable, Bluetooth-controlled RGB lighting module designed to be mounted on shoes. It features custom LED animations triggered by foot taps or BLE commands, making it ideal for cosplay, performances, or just lighting up your walk – literally.

---

## 🚀 Features

- ⚡ **Bluetooth BLE Control** – Send commands from a custom mobile app
- 👣 **Tap-to-Trigger Animations** – Tactile button for foot-based activation
- 🎨 **Color Customization** – Change RGB values in real time
- 💡 **Animations**
  - `Fade`: Fades the whole strip from the selected color
  - `Converge`: Colored dots move from both ends and meet in the center
  - `Rainbow`: Flowing multicolor effect
  - `Solid Rainbow`: Uniform rainbow cycling across the strip
- 🔋 Runs on a rechargeable **1000mAh Li-Po battery**
- 🛠️ Built using **Arduino IDE** and **MIT App Inventor**

---

## 🧰 Components Used

| Component                     | Description                                         |
|------------------------------|-----------------------------------------------------|
| ESP32-C3 Mini Dev Board      | Core MCU with BLE support                          |
| WS2812B RGB LED Strip (46 LEDs) | Individually addressable LEDs                  |
| TP4056 USB-C Charging Module | For safe Li-Po battery charging                     |
| 1000mAh Li-Po Battery        | Power supply                                        |
| Tactile Button (4-pin)       | For triggering animations via foot tap             |
| Slide Switch (3-pin)         | On/Off control                                     |
| Flexible Wires + Jumper Wires| Wiring and connections                             |
| Normal Soldering Tools       | Solder iron, wire, flux, etc.                      |

---

## 📱 App Control (MIT App Inventor)

The mobile controller was built using [MIT App Inventor](https://appinventor.mit.edu/).  
It communicates with the ESP32 via **BLE** and sends simple command strings.

### BLE Command Reference:

| Command       | Function                              |
|---------------|---------------------------------------|
| `1`           | Trigger `fade()` animation            |
| `2:<0–100>`   | Set brightness (0–100%)               |
| `3:(R,G,B)`   | Set RGB color (e.g. `3:(255,0,255)`)  |
| `4`           | Enable flowing rainbow mode           |
| `5`           | Enable solid rainbow mode             |
| `6`           | Trigger `converge()` animation        |

---

## 🧠 Arduino Code Overview

- Written in **Arduino IDE**
- Uses `Adafruit_NeoPixel` for LED control
- Uses `BLEDevice`, `BLEUtils`, `BLEServer` for Bluetooth communication
- Maintains a current mode state and RGB color variables
- Supports both BLE input and tactile button control

---

## 📂 Repository Contents

Folder Structure:
- `Yamixen_Spiritlight_V1.ino` – Main Arduino sketch (200 lines!)
- `App/SpiritlightApp.aia` – MIT App Inventor project file
- `Docs/WiringDiagram.png` – Wiring layout (coming soon)
- `README.md` – This file

---

## 🧪 How to Use

1. Clone or download this repo
2. Upload `Yamixen_Spiritlight_V1.ino` to your **ESP32-C3** using Arduino IDE
3. Install the app on your phone using MIT App Companion or compile from `.aia`
4. Power on the module (via Li-Po and switch)
5. Connect via BLE and send commands
6. Enjoy stepping into a world of color!

---

## 🛠️ Planned Upgrades

The Yamixen Spiritlight project is still evolving. The current version is a working prototype, but several exciting upgrades are already planned to take it to the next level:

- **Pressure-Based Activation**: Replace the tactile switch with a **piezo sensor** or **force-sensitive resistor**
- **Battery Level Monitoring**: Display battery percentage via BLE
- **Advanced Animation Patterns**: More visual effects and programmable modes
- **Improved App Interface**: Smoother UI with real-time color previews
- **3D-Printed Integration**: Modular design with **3D-printed sole/housing**
- **Refined Wiring & Mounting**: Better internal layout using flexible wires

---

## 🙏 Acknowledgments

Special thanks to:
- **MIT App Inventor** – for making mobile app development so accessible
- **Adafruit** – for the amazing NeoPixel library
- Every failed wiring attempt that led to a better design

---

## 📸 Preview

*(Insert image/video/gif of the working prototype here)*

---

## 📢 Feedback & Suggestions

I'm open to improvements, ideas, or collaboration!  
📝 [Submit your suggestions here](https://forms.gle/vGdGT9GdUuKqkLbk6)

---

## 📜 License

MIT License – free to use, modify, and improve!  
Please credit this repo if you fork it or build on it.

---

Built with 💡, 🔥, and RGB by **Tharunkrishna T H**
