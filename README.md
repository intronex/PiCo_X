# Pico-X: OLED Macro Keypad & Automation Tool
<img width="500" height="700" alt="image" src="https://github.com/user-attachments/assets/41884b7e-d5dc-4d5c-81d7-d98923de544e" />


## 📖 Introduction
**Pico-X** is a customizable hardware macro keypad built using the **Raspberry Pi Pico**. It features an OLED display interface to select and execute automation scripts instantly. 

This project demonstrates embedded systems programming, hardware interfacing (I2C OLED, Button Matrix), and USB HID (Human Interface Device) emulation. It is designed to help developers and IT professionals automate repetitive tasks.

## 📦 Bill of Materials (BOM)

| Component Name | Quantity | Specifications |
| :--- | :---: | :--- |
| **Raspberry Pi Pico** | 1 | RP2040 Chipset |
| **OLED Display** | 1 | 128x64, SSD1306, I2C |
| **Push Buttons** | 10 | 4-pin Tactile Switch |
| **Resistors** | 10 | 10k Ohm (Pull-up) |
| **Perfboard** | 1 | 5x7 cm Dot PCB |
| **Wires** | - | 30 AWG Single Strand |

 🚀 Features
*   **OLED Menu System:** Visual interface to scroll through available macros/scripts.
*   **10 Programmable Slots:** Supports up to 10 different automation profiles triggered by physical buttons.
*   **HID Emulation:** Acts as a standard Keyboard/Mouse, compatible with Windows, Linux, and macOS.
*   **Plug & Play:** No driver installation required on the target machine.

 🛠️ Hardware Used
*   **Microcontroller:** Raspberry Pi Pico (RP2040)
*   **Display:** SSD1306 OLED (128x64) via I2C
*   **Input:** 10 Push Buttons (Configured with Pull-up resistors)
*   **Connection:** Micro-USB Cable or Type-c cable 
  
 💻 Code Structure
The project is written in **C++ (Arduino Framework)**.
*   **`display logic`**: Manages menu navigation and animations using `Adafruit_SSD1306`.
*   **`payload logic`**: Each button triggers a specific sequence of keystrokes defined in the code.
    *   *Note:* The uploaded code contains "Demo Payloads" (e.g., opening Notepad, typing text). Users can replace these with their own automation scripts (e.g., git commands, IDE shortcuts, form filling).

 ⚙️ How to Customize
1.  Clone the repository.
2.  Open the `.ino` file in Arduino IDE.
3.  Navigate to the `loop()` function.
4.  Replace the code inside `if (digitalRead(BTN_X) == LOW)` with your custom `Keyboard.print()` commands.
5.  Upload to Pico.      ENJOY...

   
   CONTACT :- atheeqceh100@gmail.com



---
*Created by INTRONEX*
