/*
 * ESP32 TFT graph test
 *
 */

#include <TFT_eSPI.h>
#include <SPI.h>
#include <Button2.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
# include "graph.h"

#define BUTTON_1        35
#define BUTTON_2        0


// objects
TFT_eSPI tft = TFT_eSPI();
Graph graph = Graph(tft);

// settings
uint16_t fps = 100;
uint32_t margin = 1;
uint32_t legend_size = 4;

// vars
uint32_t us_old = 0;
float val1 = 0.0;
float val2 = 5;


// MAIN FUNCTIONS

void setup(void) {  
  init_screen();
  uint32_t w = TFT_HEIGHT;
  uint32_t h = TFT_WIDTH * 2/3;
  graph.init(0, 0, w, h, margin);
  graph.addTrace(&val1, 0.0, 1.0, TFT_YELLOW, "sig1");
  //graph.addTrace(&val2, 10.0, 20.0, TFT_RED, "sig2");
  graph.printLegend(0, h, legend_size);
}

void loop() {
  uint32_t us_curr = micros();
  if(us_curr - us_old > (1000000L / fps)) {
    us_old = us_curr;
    // read/generate variables
    val1 += 0.01;
    val2 += 0.1;
    if(val1 >= 1.0) val1 = 0.0;
    // refresh graph
    graph.update();
  }
}


// SETUP FUNCTIONS

void init_screen() {
  // setup screen etc
  tft.init();
  tft.setRotation(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.fillScreen(TFT_WHITE);
}
