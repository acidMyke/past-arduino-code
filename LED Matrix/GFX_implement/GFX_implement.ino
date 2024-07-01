#include <Adafruit_GFX.h>
#include <Tlc5940.h>

class TLC5940Matrix : public Tlc5940, public Adafruit_GFX{
  public:
  TLC5940Matrix(int16_t w, int16_t h, int16_t h2) : Adafruit_GFX(w, h){
    Tlc.init();
  }
  
  void drawPixel(int16_t x, int16_t y, uint16_t color){
    uint16_t r = map(((color >> 11) & 0x1F), 0, 31, 0, 4095);
    uint16_t g = map(((color >> 5 ) & 0x3F), 0, 31, 0, 4095);
    uint16_t b = map(((color >> 0 ) & 0x1F), 0, 31, 0, 4095);

    Tlc.set(x * 3)
  }

  private:
  
  
};




void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
