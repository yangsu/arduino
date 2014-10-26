#define LATCH_PIN 8 //Pin connected to ST_CP of 74HC595
#define CLOCK_PIN 12 //Pin connected to SH_CP of 74HC595
#define DATA_PIN 11 //Pin connected to DS of 74HC595

// params
#define TIMES 10
#define DATA_LENGTH 128
#define DEFAULT_DELAY 1
#define SIZE 8

int index = 0;

int data[] = {
  0xFF,0xC1,0xBE,0xBE,0xBE,0xC1,0xFF,0xFF,/*"0", 1*/
  0xFF,0xDF,0xDF,0x80,0xFF,0xFF,0xFF,0xFF,/*"1", 2*/
  0xFF,0xDC,0xBC,0xBA,0xB6,0xCE,0xFF,0xFF,/*"2", 3*/
  0xFF,0xDD,0xBE,0xB6,0xB6,0xC9,0xFF,0xFF,/*"3", 4*/
  0xFB,0xF3,0xEB,0xDB,0x80,0xFB,0xFF,0xFF,/*"4", 5*/
  0xFF,0x8D,0xAE,0xAE,0xAE,0xB1,0xFF,0xFF,/*"5", 6*/
  0xFF,0xC1,0x96,0xB6,0xB6,0xD9,0xFF,0xFF,/*"6", 7*/
  0xFF,0xBF,0xBC,0xB3,0xAF,0x9F,0xFF,0xFF,/*"7", 8*/
  0xFF,0xC9,0xB6,0xB6,0xB6,0xC9,0xFF,0xFF,/*"8", 9*/
  0xFF,0xCD,0xB6,0xB6,0xB4,0xC1,0xFF,0xFF,/*"9", 10*/
  0xFC,0xF3,0xCB,0x9B,0xEB,0xF3,0xFC,0xFF,/*"A", 11*/
  0xFF,0x80,0xB6,0xB6,0xB6,0xB6,0xC9,0xFF,/*"B", 12*/
  0xFF,0xE3,0xDD,0xBE,0xBE,0xBE,0xBE,0xDD,/*"C", 13*/
  0xFF,0x80,0xBE,0xBE,0xBE,0xBE,0xDD,0xE3,/*"D", 14*/
  0xFF,0x80,0xB6,0xB6,0xB6,0xB6,0xBE,0xFF,/*"E", 15*/
  0xFF,0x80,0xB7,0xB7,0xB7,0xB7,0xBF,0xFF,/*"F", 16*/
};

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  addNewCreature();
}

void loop() {
  frame();
  clear();
  index = (index++) % DATA_LENGTH;
}

void frame() {
  for(int i = 0; i < TIMES; i++){
    draw(i);
  }
  runGameOfLife();
}

void clear() {
  drawRaw(0xFF, 0x00, DEFAULT_DELAY);
}

void draw(int i) {
  // gradient(i);
  drawGameOfLife();
  // drawCol(7);
  // drawRow(7);
  // drawChar(0xA);
  // cycleChars();
}

void gradient(int i) {
  drawCol(0 % 8);
  if ((i % 2) == 0) drawCol(1);
  if ((i % 4) == 0) drawCol(2);
  if ((i % 8) == 0) drawCol(3);
  if ((i % 16) == 0) drawCol(4);
  if ((i % 32) == 0) drawCol(5);
  if ((i % 64) == 0) drawCol(6);
  if ((i % 128) == 0) drawCol(7);
}

void drawCol(int col) {
  drawRaw(0x00, 0x01 << col, DEFAULT_DELAY);
}

void drawRow(int row) {
  drawRaw((0x01 << row) ^ 0xFF, 0xFF, DEFAULT_DELAY);
}

void drawChar(int i) {
  drawRange(i * SIZE, SIZE);
}

void cycleChars() {
  drawRange(index, SIZE);
}

void drawRange(int start, int range) {
  int dat = 0x01;
  for(int j = start, end = start + range; j < end; j++){
    drawRaw(data[j % DATA_LENGTH], dat, DEFAULT_DELAY);
    dat = dat << 1;
  }
}

void drawDot(int row, int col, int drawDelay) {
  drawRaw((0x01 << row) ^ 0xFF, 0x01 << col, DEFAULT_DELAY);
}

void drawRaw(int row, int col, int drawDelay) {
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, col);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, row);
  digitalWrite(LATCH_PIN, HIGH); //pull the LATCH_PIN to save the data
  delay(drawDelay); //wait for a microsecond
  digitalWrite(LATCH_PIN,LOW); //ground LATCH_PIN and hold low for as long as you are transmitting
}
