/* 
Simple test program to determine whether ESP32 DMA is enabled
for the TFT_eSPI library

PlatformIO using ESP-IDF framework with Arduino as component
*/

#include <Arduino.h>

#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

#if !CONFIG_AUTOSTART_ARDUINO
void arduinoTask(void *pvParameter) {
    tft.init();

    int startTime = micros();

    tft.fillScreen(TFT_RED);
    tft.fillScreen(TFT_GREEN);
    tft.fillScreen(TFT_BLUE);

    int drawTime = micros() - startTime;

    Serial.begin(115200);
    Serial.println("Hello from ESP-IDF!");
    Serial.print("Draw time was: ");
    Serial.print(drawTime);
    Serial.println(" microseconds.");
    while(1) {
        delay(1);
    }
}
extern "C" void app_main() {
    #ifdef ESP32_DMA
    log_d("ESP32 DMA enabled");
    #else
    log_d("ESP32 DMA not enabled");
    #endif
    
    // initialize arduino library before we start the tasks
    initArduino();

    xTaskCreate(&arduinoTask, "arduino_task", 4096, NULL, 5, NULL);
}
#else
void setup() {
    #ifdef ESP32_DMA
    log_d("ESP32 DMA enabled");
    #else
    log_d("ESP32 DMA not enabled");
    #endif

    tft.init();

    int startTime = micros();

    tft.fillScreen(TFT_RED);
    tft.fillScreen(TFT_GREEN);
    tft.fillScreen(TFT_BLUE);

    int drawTime = micros() - startTime;

    Serial.begin(115200);
    Serial.println("Hello from Arduino!");
    Serial.print("Draw time was: ");
    Serial.print(drawTime);
    Serial.println(" microseconds.");
}
void loop() {
    delay(1);
}
#endif
