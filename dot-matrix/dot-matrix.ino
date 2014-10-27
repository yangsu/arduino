#define LATCH_PIN 8 //Pin connected to ST_CP of 74HC595
#define CLOCK_PIN 12 //Pin connected to SH_CP of 74HC595
#define DATA_PIN 11 //Pin connected to DS of 74HC595

// params
#define TIMES 30
#define SIZE 8
#define DRAW_DELAY 0

#define ON 0x00
#define OFF 0xFF

int layers[SIZE][SIZE];

int frameCount = 0;

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  addNewCreature();

  for (int i = 0; i < SIZE; i++) {
    clearLayer(i);
  }
}

void loop() {
  update();
  draw();
  for (int i = 0; i < TIMES; i++){
    drawLayers(i);
  }
  pushFrame(0, 0);
  frameCount++;
  clear();
}

void pushFrame(int dx, int dy) {
  for (int i = SIZE - 1; i > 0; i--) {
    for (int x = 0; x < SIZE; x++) {
      int before = layers[x][i - 1];
      int nx = x + dx;
      if (nx >= 0 && nx <= SIZE) {
        if (dy > 0) {
          layers[nx][i] = before << dy ^ 0x01; // need to make sure the right most bit is off
        } else if (dy < 0) {
          layers[nx][i] = before >> abs(dy) | 0x80; // need to make sure the left most bit is on
        } else {
          layers[nx][i] = before;
        }
      }
    }
  }
}

void update() {
  // runGameOfLife();
}

void clear() {
  clearLayer(0);
}

void clearLayer(int i) {
  for (int c = 0; c < SIZE; c++) {
    layers[c][i] = OFF;
  }
}

void draw() {
  // drawGameOfLife();

  // verticalLine(7);
  // horizontalLine(7 - frameCount % 8);
  // dot(frameCount % 8, frameCount % 8);
  // dot(0, oscillate(0, 8));
  // dot(7, oscillate(0, 8));
  // majorDiagonal(oscillate(-8, 8));
  // minorDiagonal(oscillate(-8, 8, 8));
  int count = random(10);
  for (int i = 0; i < count; i++) {
    randomDot();
  }

  // drawChar(0x1);
  // cycleChars();
}

void drawLayers(int iteration) {
  for (int c = 0; c < SIZE; c++) {
    int col = layers[c][0];
    if ((iteration % 2) == 0) col &= layers[c][1];
    if ((iteration % 4) == 0) col &= layers[c][2];
    if ((iteration % 8) == 0) col &= layers[c][3];
    if ((iteration % 16) == 0) col &= layers[c][4];
    if ((iteration % 32) == 0) col &= layers[c][5];
    if ((iteration % 64) == 0) col &= layers[c][6];
    if ((iteration % 128) == 0) col &= layers[c][7];
    drawCol(c, col);
  }
}

void dot(int row, int col) {
  unsigned char mask = (0x01 << row) ^ 0xFF;
  layers[col][0] &= mask;
}

void setCol(int col, int data) {
  layers[col][0] = data;
}

void drawCol(int col, int row) {
  flush(row, 0x01 << col);
}

void flush(int row, int col) {
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, col);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, row);
  digitalWrite(LATCH_PIN, HIGH); //pull the LATCH_PIN to save the data
  delay(DRAW_DELAY); //wait for a microsecond
  digitalWrite(LATCH_PIN,LOW); //ground LATCH_PIN and hold low for as long as you are transmitting
}
