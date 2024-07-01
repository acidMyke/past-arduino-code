typedef enum {BUTTON, SWITCH} digitalType;

class Digital {
  public:
//         Value      Size    Position     Type
//Default: 0    1    2    2   -1   -1
  Digital(int, int, int, int, int, int, digitalType, WebInterface*);
  Digital(int, int, int, int,           digitalType, WebInterface*);
  Digital(int, int,                     digitalType, WebInterface*);
  Digital(                              digitalType, WebInterface*);

  int getValue();
  boolean changed();
  void setColor(CColor);

  private:
  int value;
  int min;
  int max;
  int width;
  int height;
  int x;
  int y;
  CColor color;
  digitalType type;
};


Digital::Digital(int Vmin, int Vmax, int Vwidth, int Vheight, int Vx, int Vy, digitalType Vtype, WebInterface* wi) {
  min = Vmin;
  max = Vmax;
  width = Vwidth;
  height = Vheight;
  x = Vx;
  y = Vy;
  type = Vtype;
}

Digital::Digital(int Vmin, int Vmax, int Vwidth, int Vheight, digitalType Vtype, WebInterface* wi) {
  min = Vmin;
  max = Vmax;
  width = Vwidth;
  height = Vheight;
  x = -1;
  y = -1;
  type = Vtype;
}

Digital::Digital(int Vmin, int Vmax, digitalType Vtype, WebInterface* wi) {
  min = Vmin;
  max = Vmax;
  width = 2;
  height = 2;
  x = -1;
  y = -1;
  type = Vtype;
}

Digital::Digital(digitalType Vtype, WebInterface* wi) {
  min = 0;
  max = 1;
  width = 2;
  height = 2;
  x = -1;
  y = -1;
  type = Vtype;
}

void Digital::setColor(CColor c) {
  color = c;
}
