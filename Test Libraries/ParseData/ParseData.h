class ParseData {
  public:
    void begin(int (*r)());
    byte toByte();
    char toChar();
    unsigned int toUInt();
    int toInt();
    unsigned long toULong();
    long toLong(); 
  private:
    int (*read)();
}Data;

void ParseData::begin(int (*r)()){
  read = r;
}

byte ParseData::toByte(){
  return (byte)read();
}

char ParseData::toChar(){
  return (char)read();
}

unsigned int ParseData::toUInt(){
  return ((unsigned int)read() | (unsigned int)read() << 8);
}

int ParseData::toInt(){
  return ((int)read() | (int)read() << 8);
}

unsigned long ParseData::toULong(){
  return ((unsigned long)read() | (unsigned long)read() << 8 | (unsigned long)read() << 16 | (unsigned long)read() << 24);
}

long ParseData::toLong(){
  return ((long)read() | (long)read() << 8 | (long)read() << 16 | (long)read() << 24);
}
