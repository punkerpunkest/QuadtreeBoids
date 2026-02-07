#include "point.hpp"

Point::Point(double x, double y, Boid* b) {
  xPoint = x;
  yPoint = y;
  boid = b;
}

bool Point::equals(Point p1) {
  if (xPoint == p1.xPoint && yPoint == p1.yPoint) {
    return true;
  } else {
    return false;
  }
}

double Point::getX() { return xPoint; }

double Point::getY() { return yPoint; }

Boid* Point::getBoid() {
  return boid;
}
