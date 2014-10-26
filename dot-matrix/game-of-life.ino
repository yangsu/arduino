#define T true
#define F false

boolean board[SIZE][SIZE];

#define BOARDS 5
boolean boards[][SIZE][SIZE] = {
  // R-pentomino
  {
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, T, T, F, F},
    {F, F, F, T, T, F, F, F},
    {F, F, F, F, T, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
  },

  // die hard
  {
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, T, F},
    {T, T, F, F, F, F, F, F},
    {F, T, F, F, F, T, T, T},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
  },

  // acorn
  {
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, T, F, F, F, F, F},
    {F, F, F, F, T, F, F, F},
    {F, T, T, F, F, T, T, T},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
  },

  // box
  {
    {F, F, F, F, F, F, F, F},
    {F, T, T, T, F, T, F, F},
    {F, T, F, F, F, F, F, F},
    {F, F, F, F, T, T, F, F},
    {F, F, T, T, F, T, F, F},
    {F, T, F, T, F, T, F, F},
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
  },

  // min
  {
    {F, F, F, F, F, F, F, F},
    {F, F, F, F, F, F, T, F},
    {F, F, F, F, T, F, T, T},
    {F, F, F, F, T, F, T, F},
    {F, F, F, F, T, F, F, F},
    {F, F, T, F, F, F, F, F},
    {T, F, T, F, F, F, F, F},
    {F, F, F, F, F, F, F, F},
  },
};

int wrap(int x, int m) {
  return (x + m) % m;
}

int getNeighborCount(int x, int y) {
  int nc = 0;
  for (int xi = x - 1, xEnd = x + 1; xi <= xEnd; xi++) {
    for (int yi = y - 1, yEnd = y + 1; yi <= yEnd; yi++) {
      if (
        !(xi == x && yi == y) &&
        xi >= 0 && xi < SIZE &&
        yi >= 0 && yi < SIZE &&
        board[xi][yi]
      ) {
        nc++;
      }
    }
  }
  return nc;
}

boolean getDot(int x, int y) {
  return (board[x][y] && getNeighborCount(x, y) == 2) || getNeighborCount(x, y) == 3;
}

void runGameOfLife() {
  boolean next[SIZE][SIZE];
  boolean changed = false;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      next[i][j] = getDot(i, j);
    }
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (board[i][j] != next[i][j]) {
        board[i][j] = next[i][j];
        changed = true;
      }
    }
  }

  if (!changed) {
    addNewCreature();
  }
}

void addNewCreature() {
  int choice = random(BOARDS);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      board[i][j] = boards[choice][i][j];
    }
  }
}

void drawGameOfLife() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (board[i][j]) drawDot(i, j, DEFAULT_DELAY);
    }
  }
}
