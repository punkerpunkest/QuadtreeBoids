#include "point.hpp"
#pragma once

class QuadTreeNode {
private:
  int width;
  int height;
  int xCoord;
  int yCoord;

public:
  QuadTreeNode(int width, int height, int xCoord, int yCoord);
  bool canContain(Point p);
  int getWidth();
  int getHeight();
  int getXCoord();
  int getYCoord();
  bool intersects(QuadTreeNode node);
  bool contains(QuadTreeNode node);
};
