/*
 * ======================================================================================
 * PROJECT:     Pico-X (OLED Macro Keypad Framework)
 * AUTHOR:      [ Althaf Atheeq / Intronex ]
 * GITHUB:      https://github.com/intronex/Pico_X
 * VERSION:     2.0 (Stable Build)
 * LICENSE:     MIT Open Source
 * ======================================================================================
 * DESCRIPTION:
 * This firmware transforms a Raspberry Pi Pico (RP2040) into a programmable 
 * USB HID Macro Keypad with an OLED interface. It is designed for IT automation, 
 * coding workflows, and productivity enhancement.
 * 
 * FEATURES:
 * - 10 Programmable Macro Buttons
 * - OLED Display Menu (SSD1306)
 * - Plug & Play HID Emulation (Keyboard/Mouse)
 * 
 * DISCLAIMER:
 * This project is for educational and automation purposes only. 
 * Please use responsibly.
 * ======================================================================================
 */

/*
 * ======================================================================================
 * PROJECT:     Pico-X (OLED Macro Keypad Framework)
 * AUTHOR:      [ Althaf Atheeq / Intronex ]
 * GITHUB:      https://github.com/intronex/Pico_X
 * VERSION:     2.0 (Stable Build)
 * LICENSE:     MIT Open Source
 * ======================================================================================
 * DESCRIPTION:
 * This firmware transforms a Raspberry Pi Pico (RP2040) into a programmable 
 * USB HID Macro Keypad with an OLED interface. It is designed for IT automation, 
 * coding workflows, and productivity enhancement.
 * 
 * FEATURES:
 * - 10 Programmable Macro Buttons
 * - OLED Display Menu (SSD1306)
 * - Plug & Play HID Emulation (Keyboard/Mouse)
 * 
 * DISCLAIMER:
 * This project is for educational and automation purposes only. 
 * Please use responsibly.
 * ======================================================================================
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keyboard.h>
#include <Mouse.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- CONFIGURATION --------
const char* WEBHOOK_URL = "YOUR WEBHOOK URL"; //ENTER YOUR WEBHOOK LINK HERE

// -------- BUTTON PINS --------
#define BTN1 1
#define BTN2 2
#define BTN3 3
#define BTN4 4
#define BTN5 5
#define BTN6 6
#define BTN7 7
#define BTN8 8
#define BTN9 9
#define BTN10 10


const unsigned char epd_bitmap_real_skull [] PROGMEM = {
  0x00, 0x07, 0xE0, 0x00, 0x00, 0x3F, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 0x80, 
  0x03, 0xFF, 0xFF, 0xC0, 0x07, 0xFF, 0xFF, 0xE0, 0x07, 0xF8, 0x1F, 0xE0, 0x0F, 0xC0, 0x03, 0xF0, 
  0x0F, 0x00, 0x00, 0xF0, 0x1E, 0x00, 0x00, 0x78, 0x1E, 0x00, 0x00, 0x78, 0x1C, 0x00, 0x00, 0x38, 
  0x3C, 0x00, 0x00, 0x3C, 0x3C, 0x18, 0x18, 0x3C, 0x38, 0x3C, 0x3C, 0x1C, 0x38, 0x7E, 0x7E, 0x1C, 
  0x38, 0xFF, 0xFF, 0x1C, 0x3C, 0xFF, 0xFF, 0x3C, 0x1C, 0xFF, 0xFF, 0x38, 0x1E, 0xFF, 0xFF, 0x78, 
  0x0F, 0x7F, 0xFE, 0xF0, 0x07, 0x3F, 0xFC, 0xE0, 0x03, 0x0F, 0xF0, 0xC0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x66, 0x66, 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x3C, 0x3C, 0x00, 
  0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00
};


// -------- Page Control --------
unsigned long lastPageSwitch = 0; 
int currentPage = 0;               
const unsigned long pageInterval = 3000;

// -------- HELPER FUNCTIONS --------

void typeSlow(const char *text, int delayTime) {
  while (*text) {
    Keyboard.print(*text);
    delay(delayTime);
    text++;
  }
}

void showExec(const char* name) {
  display.clearDisplay();
  display.drawBitmap(4, 0, epd_bitmap_real_skull, 32, 32, SSD1306_WHITE);
  display.setCursor(40, 5); display.setTextSize(1); display.println("INJECTING...");
  display.setCursor(35, 15); display.println("DONT DISCONNECT"); 
  display.setCursor(0, 40); display.setTextSize(1); display.println("PAYLOAD:");
  display.setCursor(0, 52); display.println(name);
  display.display();
}

// -------- BOOT SCREEN --------
void bootScreen() {
  display.clearDisplay();
  
  // --- PHASE 1: LOADING ANIMATION ---
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 25);
  display.println("Initializing...");
  
  // Progress Bar Animation
  display.drawRect(14, 40, 100, 8, SSD1306_WHITE); // Border
  for(int i=0; i<96; i+=4) {
    display.fillRect(16, 42, i, 4, SSD1306_WHITE); // Filling
    display.display();
    delay(30); 
  }
  delay(200);

  // --- PHASE 2: LOGO REVEAL ---
  display.clearDisplay();
  
  // 1. Draw Skull (Center)
  display.drawBitmap(48, 0, epd_bitmap_real_skull, 32, 32, SSD1306_WHITE);
  
  // 2. Right Side Text (Version)
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(85, 20); 
  display.println("v2.0");

  display.setCursor(5, 20);
  display.println("ROOT>>");

  // 4. Title (_PiCo_X)
  display.setTextSize(2);
  display.setTextColor(SSD1306_INVERSE); 
  display.setCursor(15, 36);
  display.println("_PiCo_X");
  
  // 5. Owner Name
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 56);
  display.println("Own: ALTHAF ATHEEQ");//YOU CAN CHANGE YOUR NAME HERE 
  
  display.display();
  delay(4000);
}

void showPage1() {
  display.clearDisplay();
  display.setTextSize(1); display.setTextColor(SSD1306_INVERSE);
  display.setCursor(0, 0);  display.println("- PAGE 1 -");
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 15); display.println("1: payload 1");
  display.setCursor(0, 25); display.println("2: payload 2");
  display.setCursor(0, 35); display.println("3: payload 3");
  display.setCursor(0, 45); display.println("4: payload 4");
  display.setCursor(0, 55); display.println("5: payload 5");
  display.display();
}

void showPage2() {
  display.clearDisplay();
  display.setTextSize(1); display.setTextColor(SSD1306_INVERSE);
  display.setCursor(0, 0);  display.println("-  PAGE 2 -");
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 15); display.println("6: payload 6");
  display.setCursor(0, 25); display.println("7: payload 7");
  display.setCursor(0, 35); display.println("8: payload 8");
  display.setCursor(0, 45); display.println("9: payload 9");
  display.setCursor(0, 55); display.println("10:payload 10");
  display.display();
}

void setup() {
  Wire.setSDA(28); Wire.setSCL(29); Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Keyboard.begin();
  Mouse.begin();
  bootScreen();
  showPage1();
  for (int i = 1; i <= 10; i++) pinMode(i, INPUT_PULLUP);
}

void loop() {
  if (millis() - lastPageSwitch > pageInterval) {
    lastPageSwitch = millis();
    currentPage = !currentPage;
    if (currentPage == 0) showPage1(); else showPage2();
  }

  // ================= PAYLOAD 1: =================
  if (digitalRead(BTN1) == LOW) {
    showExec("payload 1");

Keyboard.press(KEY_LEFT_GUI);
Keyboard.press('r');
delay(200);
Keyboard.releaseAll();
delay(500);


Keyboard.print("notepad");
delay(100);
Keyboard.press(KEY_RETURN);
Keyboard.releaseAll();
delay(1000); 


Keyboard.print("Hello! This is a test from Pico-X.");

  // ================= PAYLOAD 2:  =================
  if (digitalRead(BTN2) == LOW) {
    showExec("PAYLOAD 2");

    //your code here ============================

    lastPageSwitch = millis(); while (digitalRead(BTN2) == LOW);
  }

// ================= PAYLOAD 3 =================
if (digitalRead(BTN3) == LOW) {
    showExec("MACRO 3");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN3) == LOW);
}

// ================= PAYLOAD 4 =================
if (digitalRead(BTN4) == LOW) {
    showExec("MACRO 4");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN4) == LOW);
}

// ================= PAYLOAD 5 =================
if (digitalRead(BTN5) == LOW) {
    showExec("MACRO 5");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN5) == LOW);
}

// ================= PAYLOAD 6 =================
if (digitalRead(BTN6) == LOW) {
    showExec("MACRO 6");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN6) == LOW);
}

// ================= PAYLOAD 7 =================
if (digitalRead(BTN7) == LOW) {
    showExec("MACRO 7");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN7) == LOW);
}

// ================= PAYLOAD 8 =================
if (digitalRead(BTN8) == LOW) {
    showExec("MACRO 8");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN8) == LOW);
}

// ================= PAYLOAD 9 =================
if (digitalRead(BTN9) == LOW) {
    showExec("MACRO 9");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN9) == LOW);
}

// ================= PAYLOAD 10 =================
if (digitalRead(BTN10) == LOW) {
    showExec("MACRO 10");
    
    // [ENTER YOUR PAYLOAD HERE]
    
    lastPageSwitch = millis(); while (digitalRead(BTN10) == LOW);
}
  }

}