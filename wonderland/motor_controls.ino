void zeroX() {
  move(LEFT, xFullRot * 1.5);
}

void zeroY() {
  move(DOWN, yFullRot * 1.5);
}


void setXDeg(int angle) {
  int timePerDeg = xFullRot / xMaxDeg;
  if (xDeg < angle) {
    int wantedAngle = angle - xDeg;
    move(RIGHT, timePerDeg * wantedAngle);
  } else if (xDeg > angle) {
    int wantedAngle = xDeg - angle;
    move(LEFT, timePerDeg * wantedAngle);
  }

  xDeg = angle;
}

void setYDeg(int angle) {
  int timePerDeg = yFullRot / yMaxDeg;
  if (yDeg < angle) {
    int wantedAngle = angle - yDeg;
    move(UP, timePerDeg * wantedAngle);
  } else if (yDeg > angle) {
    int wantedAngle = yDeg - angle;
    move(DOWN, timePerDeg * wantedAngle);
  }

  yDeg = angle;
}

void move(Direction dir, int ms) {
  switch (dir) {
    case RIGHT:
      digitalWrite(xRight, HIGH);
      digitalWrite(xLeft, LOW);
      delay(ms);
      digitalWrite(xRight, LOW);
      break;

    case LEFT:
      digitalWrite(xLeft, HIGH);
      digitalWrite(xRight, LOW);
      delay(ms);
      digitalWrite(xLeft, LOW);
      break;

    case UP:
      digitalWrite(yUp, HIGH);
      digitalWrite(yDown, LOW);
      delay(ms);
      digitalWrite(yUp, LOW);
      break;

    case DOWN:
      digitalWrite(yDown, HIGH);
      digitalWrite(yUp, LOW);
      delay(ms);
      digitalWrite(yDown, LOW);
      break;
  }
}

void moveTo(Vec2 point) {
  point.x = min(point.x, xMaxDeg);
  point.y = min(point.y, yMaxDeg);

  while (true) {
    if (xDeg == point.x && yDeg == point.y) {
      break;
    }

    if (xDeg < point.x) {
      setXDeg(xDeg + 1);
    } else if (xDeg > point.x) {
      setXDeg(xDeg - 1);
    }

    if (yDeg < point.y) {
      setYDeg(yDeg + 1);
    } else if (yDeg > point.y) {
      setYDeg(yDeg - 1);
    }
  }

  buzz(127);
  light(topLight, 255);
  light(ledStrip, 255);
  delay(10);
  buzz(0);
  light(topLight, 0);
  light(ledStrip, 0);

  light(topLight, 0);
}