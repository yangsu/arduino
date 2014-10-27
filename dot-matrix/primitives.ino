void verticalLine(int col) {
  setCol(col, ON);
}

void horizontalLine(int row) {
  for (int c = 0; c < SIZE; c++) {
    dot(row, c);
  }
}

void majorDiagonal(int offset) {
  for (int x = 0; x < SIZE; x++) {
    int y = SIZE - x + offset;
    if (y >= 0 && y < SIZE) dot(x, y);
  }
}

void minorDiagonal(int offset) {
  for (int x = 0; x < SIZE; x++) {
    int y = x + offset;
    if (y >= 0 && y < SIZE) dot(x, y);
  }
}

void randomDot() {
  int x = random(SIZE);
  int y = random(SIZE);
  dot(x, y);
}
