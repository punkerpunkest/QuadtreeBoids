#pragma once
#include "quadtreenode.hpp"
#include <vector>
class Circle {
private:
  int xCoord;
  int yCoord;
  int radius;

public:
  Circle(int x, int y, int radius);
  bool canContain(Point p);
  bool completeContains(QuadTreeNode node);
  bool intersects(QuadTreeNode tree);
  std::vector<Point> query(Circle c, std::vector<Point> &found);
  int getXCoord();
  int getYCoord();
  int getRadius();
};
