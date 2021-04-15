/*
  graph.h - Library for drawing graphs and plots on a TFT display
  Riccardo Miccini, July 7, 2020.
*/

#include "graph.h"


void Graph::init(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t margin) {
  // init plottable area dimentions
  _m = margin;
  _x = x + _m;
  _y = y + _m;
  _w = w - _m * 2;
  _h = h - _m * 2;
  // TODO get current rotation, font heigth, etc
  _fh = _tft.fontHeight();
  // precalculate stuff
  // TODO
  // draw border
  _tft.drawRect(_x, _y, _w, _h, TFT_BLACK);
  // reinit plottable area to account for border
  _x += 1;
  _y += 1;
  _w -= 2;
  _h -= 2;
#if GRAPH_DBG
  Serial.begin(115200);
  Serial.println("graph init");
  Serial.print("position: ");
  Serial.print(_x);
  Serial.print(", ");
  Serial.println(_y);
  Serial.print("size: ");
  Serial.print(_w);
  Serial.print(", ");
  Serial.println(_h);
  Serial.print("font height: ");
  Serial.println(_fh);
#endif
}

void Graph::addTrace(float* var, float ymin, float ymax, uint32_t color, char* name) {
#if GRAPH_DBG
  Serial.print("add trace #");
  Serial.print(int(_trace_n));
  Serial.print(": ");
  Serial.print(name);
  Serial.print("... ");
#endif
  
  // if out of traces, abort
  if (_trace_n >= MAX_TRACES) {
#if GRAPH_DBG
    Serial.println("failed");
#endif
    return;
  }
  // store trace settings
  _traces[_trace_n].var = var;
  _traces[_trace_n].ymin = ymin;
  _traces[_trace_n].ymax = ymax;
  _traces[_trace_n].color = color;
  _traces[_trace_n].name = name;
  // increase trace counter
  _trace_n++;
#if GRAPH_DBG
  Serial.println("success");
#endif
}

void Graph::update() {
  if(_w == 0) {
    return;
  }
  // for each trace
  for(uint8_t i=0; i<_trace_n; i++) {
    GraphTrace &t = _traces[i];
    // map value
    uint32_t var_scaled = uint32_t((*t.var - t.ymin) / (t.ymax - t.ymin) * _h);
    var_scaled = min(var_scaled, _h) - 1;  // TODO why the -1 tho?
    // convert to screen coordinates
    int32_t yy = _y + _h - var_scaled;
    int32_t xx = _x + _t;
    
#if GRAPH_DBG
    Serial.print("trace # ");
    Serial.print(int(i));
    Serial.print(" :  ");
    Serial.print(double(*t.var));
    Serial.print(" > ");
    Serial.println(yy);
#endif
    // draw
    _tft.drawPixel(xx, yy, t.color);
  }
  // increase and reset cursor
  _t++;
  if(_t >= _w) {
    _t = 0;
  }
  // clean up next cols
  // TODO
}

uint32_t Graph::printLegend(uint32_t x, uint32_t y, uint32_t size) {
  uint32_t h = 0;
#if GRAPH_DBG
  Serial.println("printing legend...");
#endif

//  // store useful vars
//  graph_offs = text_height*3 + margin*2;
//  graph_height = TFT_WIDTH - graph_offs - margin;
//  // draw graph edges
//  // draw graph legend
//  uint32_t legend_orig_x = (legend_width-legend_size)/2;
//  uint32_t legend_orig_y = (text_height-legend_size)/2 + margin;
//  tft.fillRect(legend_orig_x, legend_orig_y, legend_size, legend_size, TFT_RED);
//  tft.fillRect(legend_orig_x, text_height+legend_orig_y, legend_size, legend_size, TFT_ORANGE);
//  tft.fillRect(legend_orig_x, text_height*2+legend_orig_y, legend_size, legend_size, TFT_PINK);

  // return height
  return h;
}
