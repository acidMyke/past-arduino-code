void reset() {
  for(int p=0;p<80;p++){
    Red[p]=0;
    Green[p]=0;
    Blue[p]=0;
  }
}
void allred(int bright){
  for(int p=0;p<80;p++){
    Red[p]=bright;
  }
}
void allblue(int bright){
  for(int p=0;p<80;p++){
    Blue[p]=bright;
  }
}
void allgreen(int bright){
  for(int p=0;p<80;p++){
    Green[p]=bright;
  }
}
void allone(int bright){
  for(int p=0;p<48;p++){
    RowA[p]=bright;
  }
}
void alltwo(int bright){
  for(int p=0;p<48;p++){
    RowB[p]=bright;
  }
}
void allthree(int bright){
  for(int p=0;p<48;p++){
    RowC[p]=bright;
  }
}
void allfour(int bright){
  for(int p=0;p<48;p++){
    RowD[p]=bright;
  }
}
void allfive(int bright){
  for(int p=0;p<48;p++){
    RowE[p]=bright;
  }
}
