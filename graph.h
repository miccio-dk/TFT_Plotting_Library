/*
  graph.h - Library for drawing graphs and plots on a TFT display
  Riccardo Miccini, July 7, 2020.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "Arduino.h"
#include <TFT_eSPI.h>

#define MAX_TRACES 2
#define GRAPH_DBG 1


struct GraphTrace {
  float *var;
  float ymin;
  float ymax;
  uint32_t color;
  char *name;
};

class Graph {
  public:
    Graph(TFT_eSPI& tft) : _tft(tft), _x(0), _y(0), _w(0), _h(0), _t(0), _fh(0), _m(0), _trace_n(0) {};
    void init(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t margin);
    void update();
    
    void addTrace(float* var, float ymin, float ymax, uint32_t color, char* name);
    uint32_t printLegend(uint32_t x, uint32_t y, uint32_t size);
    
  private:
    TFT_eSPI& _tft;
    // plot top-left corner
    uint32_t _x;
    uint32_t _y;
    // plot dimentions
    uint32_t _w;
    uint32_t _h;
    // horizontal cursor position (time)
    uint32_t _t;
    // text height
    uint32_t _fh;
    // margin
    uint32_t _m;
    
    GraphTrace _traces[MAX_TRACES];
    uint8_t _trace_n;
};


/*
  TODO:
  - auto min/max
  - different graph types
*/

#endif
