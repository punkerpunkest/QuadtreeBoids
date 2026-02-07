#include "circle.hpp"
#include <algorithm>

Circle::Circle(int x, int y, int r) {
  xCoord = x;
  yCoord = y;
  radius = r;
}

bool Circle::canContain(Point p) {
  auto xPoint = p.getX() - xCoord;
  auto yPoint = p.getY() - yCoord;
  auto distSquared = xPoint * xPoint + yPoint * yPoint;
  return distSquared <= radius * radius;
}

bool Circle::completeContains(QuadTreeNode node) {
  int width = node.getWidth();
  int height = node.getHeight();
  int nodeX = node.getXCoord();
  int nodeY = node.getYCoord();

  int corners[4][2] = {
    {nodeX - width, nodeY - height}, 
    {nodeX + width, nodeY - height}, 
    {nodeX - width, nodeY + height},
    {nodeX + width, nodeY + height}
  };

  for (int i = 0; i < 4; i++) {
    int dx = corners[i][0] - xCoord;
    int dy = corners[i][1] - yCoord;
    if (dx * dx + dy * dy > radius * radius) {
      return false;
    }
  }
  return true;
}

bool Circle::intersects(QuadTreeNode treeNode) {
  int width = treeNode.getWidth();
  int height = treeNode.getHeight();
  int xTree = treeNode.getXCoord();
  int yTree = treeNode.getYCoord();

  int closestX = std::max(xTree - width, std::min(xCoord, xTree + width));
  int closestY = std::max(yTree - height, std::min(yCoord, yTree + height));

  int dx = xCoord - closestX;
  int dy = yCoord - closestY;

  return (dx * dx + dy * dy <= radius * radius);
}
