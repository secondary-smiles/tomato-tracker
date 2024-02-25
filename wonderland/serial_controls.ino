Vec2 readTomato() {
  Vec2 point;

  while (!Serial.available()) {}

  char buf[16];
  int rlen = Serial.readBytesUntil('?', buf, 16);

  int x;
  int y;

  sscanf(buf, "%d:%d", &x, &y);

  point.x = x;
  point.y = y;

  return point;
}