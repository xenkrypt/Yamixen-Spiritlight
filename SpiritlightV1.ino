//Created by Tharunkrishna T H, with a love for technology.

#include <Adafruit_NeoPixel.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define LED_PIN 1
#define NUMPIXELS 46
#define BUTTON_PIN 2

#define SERVICE_UUID "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-ab12-cd34-ef56-abcdef123456"
#define DEVICE_NAME "SpiritlightV1"

Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
BLECharacteristic *pCharacteristic;

int buttonMode = 0;
int brightness = 255;
int lastR = 255, lastG = 255, lastB = 255;
bool staticColorActive = false;
bool rainbowMode = false;
bool solidRainbowMode = false;
unsigned long lastRainbowTime = 0;
byte hue = 0;

void applyStaticColor() {
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(lastR, lastG, lastB));
  strip.setBrightness(brightness);
  strip.show();
}

void converge() {
  staticColorActive = false;
  rainbowMode = false;
  solidRainbowMode = false;
  strip.clear();
  strip.show();
  int delayTime = 10;
  for (int i = 0; i <= 22; i++) {
    strip.clear();
    if (i < 3) {
      for (int j = 0; j <= i; j++) {
        int left = 23 - j;
        int right = 22 + j;
        strip.setPixelColor(left, strip.Color(lastR, lastG, lastB));
        strip.setPixelColor(right, strip.Color(lastR, lastG, lastB));
      }
    } else {
      for (int j = 0; j < 3; j++) {
        int left = 23 - (i - j);
        int right = 22 + (i - j);
        if (left >= 0 && right < NUMPIXELS) {
          strip.setPixelColor(left, strip.Color(lastR, lastG, lastB));
          strip.setPixelColor(right, strip.Color(lastR, lastG, lastB));
        }
      }
    }
    strip.setBrightness(brightness);
    strip.show();
    delay(delayTime);
  }
  for (int b = 255; b >= 0; b -= 15) {
    for (int i = 0; i < 3; i++) {
      int left = 0 + i;
      int right = NUMPIXELS - 1 - i;
      strip.setPixelColor(left, strip.Color((lastR * b) / 255, (lastG * b) / 255, (lastB * b) / 255));
      strip.setPixelColor(right, strip.Color((lastR * b) / 255, (lastG * b) / 255, (lastB * b) / 255));
    }
    strip.show();
    delay(10);
  }
  strip.clear();
  strip.show();
}

void fade() {
  if (brightness == 0){
    return;
  }
  staticColorActive = false;
  rainbowMode = false;
  solidRainbowMode = false;
  for (int i = 0; i < strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(lastR,lastG,lastB));
  strip.setBrightness(brightness);
  strip.show();
  for (int b = 255;b >= 0;b -= 3) {
    for (int i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, strip.Color((lastR*b)/255,(lastG*b)/255,(lastB*b)/255));
    }
    strip.setBrightness(brightness);
    strip.show();
    delay(10);
  }
  strip.clear();
  strip.show();
}

void setColorFromString(String rgbString) {
  rgbString.trim();
  rgbString.replace("(", "");
  rgbString.replace(")", "");
  int c1 = rgbString.indexOf(',');
  int c2 = rgbString.indexOf(',', c1 + 1);
  int r = rgbString.substring(0, c1).toInt();
  int g = rgbString.substring(c1 + 1, c2).toInt();
  int b = rgbString.substring(c2 + 1).toInt();
  lastR = r;
  lastG = g;
  lastB = b;
  staticColorActive = true;
  rainbowMode = false;
  solidRainbowMode = false;
  applyStaticColor();
}

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) {
    String input = String(pChar->getValue().c_str());
    input.trim();
    int colon = input.indexOf(':');
    String cmd = colon == -1 ? input : input.substring(0, colon);
    String arg = colon == -1 ? "" : input.substring(colon + 1);
    if (cmd == "1") {
      fade();
      buttonMode = 0;
    } else if (cmd == "2") {
      float value = arg.toFloat();
      value = constrain(value, 0, 100);
      brightness = (255 * value) / 100;
      strip.setBrightness(brightness);
      if (staticColorActive) applyStaticColor();
    } else if (cmd == "3") {
      setColorFromString(arg);
    } else if (cmd == "4") {
      rainbowMode = true;
      staticColorActive = false;
      solidRainbowMode = false;
    } else if (cmd == "5") {
      solidRainbowMode = true;
      staticColorActive = false;
      rainbowMode = false;
    } else if (cmd == "6") {
      converge();
      buttonMode = 1;
    }
  }
};

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.clear();
  strip.setBrightness(brightness);
  strip.show();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
  Serial.println("Spiritlight Ready");
}

void loop() {
  unsigned long now = millis();
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    if (buttonMode == 0){
      fade();
    }
    else if (buttonMode == 1){
      converge();
    }
  }
  lastButtonState = currentButtonState;
  if (rainbowMode && now - lastRainbowTime > 20) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.ColorHSV((hue * 256 + i * 65536L / NUMPIXELS), 255, brightness));
    }
    strip.show();
    hue++;
    lastRainbowTime = now;
  }
  if (solidRainbowMode && now - lastRainbowTime > 30) {
    uint32_t color = strip.ColorHSV(hue*256,255,brightness);
    for (int i = 0; i < strip.numPixels(); i++){
      strip.setPixelColor(i, color);
    }
    strip.show();
    hue++;
    lastRainbowTime = now;
  }
}
