enum Direction { UP,
                 DOWN,
                 LEFT,
                 RIGHT };

struct Vec2 {
  int x;
  int y;
};

int yDown = 8;
int yUp = 9;

int xLeft = 6;
int xRight = 7;

int yFullRot = 900;  // ms for one rotation
int xFullRot = 1200;

int yMaxDeg = 100;
int xMaxDeg = 100;

int xDeg = 0;
int yDeg = 0;

int topLight = 3;
int ledStrip = 2;
int buzzer = 4;

void setup() {
  pinMode(yDown, OUTPUT);
  pinMode(yUp, OUTPUT);
  pinMode(xLeft, OUTPUT);
  pinMode(xRight, OUTPUT);

  pinMode(topLight, OUTPUT);
  pinMode(ledStrip, OUTPUT);
  pinMode(buzzer, OUTPUT);

  zeroX();
  zeroY();

  Serial.begin(9600);
}

void loop() {
  Vec2 coord = readTomato();
  if (coord.x >= 0 && coord.y >= 0) {
    moveTo(coord);

    Serial.print("!");
    light(topLight, 0);
  }
}
