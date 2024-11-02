#include "Arduino_LED_Matrix.h"
ArduinoLEDMatrix matrix;
int x = 0;
int y = 0;
int n;
int si;
int i;
int b;
int j;
int k;
int go;
int cnt;
int cnt2;
int left, right, up, down;
int point;
int speedrun;
byte frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
byte frame2[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0 },
  { 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
  { 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0 },
  { 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0 },
};
byte g[3][2] = {
  { 1, 0 },
  { 1, 0 },
  { 1, 1 },
};

void gameover() {
  for (k = 0; k < 8; k++) {
    go = 0;
    for (int n = 0; n < 12; n++)
      if (frame[k][n] == 1)
        go++;
    if (go == 12) {
      matrix.renderBitmap(frame2, 8, 12);
      delay(1000);
    }
  }
}
void setup() {
  Serial.begin(9600);
  matrix.begin();
  pinMode(2, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(0, INPUT_PULLUP);
}

void loop() {

  frame[y][x] = 0;
  si++;
  if (si >= speedrun) {
    x--;
    si = 0;
  }
  if (digitalRead(2) == 0) {
    speedrun = 10;
  } else {
    speedrun = 20;
  }

  if (digitalRead(0) == 0) {
    if (up == 0)
      if ((y > 0) && (frame[y - 1][x] == 0))
        y--;
    up = 1;
  } else up = 0;

  if (digitalRead(1) == 0) {
    if (down == 0)
      if ((y < 7) && (frame[y + 1][x] == 0))
        y++;
    down = 1;
  } else down = 0;

 
  frame[y][x] = 1;

  if ((x <= 0) || (frame[y][x - 1] == 1)) {
    gameover();
    cnt = 0;
    for (i = 0; i < 8; i++)
      if (frame[i][0] == 1)
        cnt++;
      else break;
    if (cnt == 8)
      for (i = 0; i < 8; i++) {
        for (j = 0; j < 11; j++)
          frame[i][j] = frame[i][j + 1];
        frame[i][11] = 0;
      }
    if (cnt == 8) {
      point++;
      Serial.print("баллов");
      Serial.println(point);
    }

    x = 11;
    y = 3;
    frame[y][x] = 1;
  }
  //new
  delay(10);
  matrix.renderBitmap(frame, 8, 12);
}