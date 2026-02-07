#pragma once

class Boid;

class Point {
private:
  double xPoint;
  double yPoint;
  Boid* boid;


public:
  Point(double x, double y, Boid* b = nullptr);
  bool equals(Point p1);
  double getX();
  double getY();
  Boid* getBoid(); 
};
