int rand() {
  return random(SIZE);
}

int oscillate(int min, int max) {
  return oscillate(min, max, 0);
}

int oscillate(int min, int max, int frameOffset) {
  int range = abs(max - min);
  int fc = frameCount + frameOffset;
  boolean even = (fc / range & 0x01) == 0;
  int offset = fc % range;
  return even ? max - offset : min + offset;
}
