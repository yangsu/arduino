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

int rand() {
  return random(SIZE);
}

void randomDot() {
  dot(rand(), rand());
}

void randomDotInRow(int row) {
  dot(row, rand());
}

void randomDotInCol(int col) {
  dot(rand(), col);
}
