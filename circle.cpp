#include "circle.hpp"

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

bool Circle::completeContains(
    QuadTreeNode
        node) { // for recursive call, save time on canContain function, if
                // circle bigger than entire subnode, return all points
  int width = node.getWidth();
  int height = node.getHeight();
  int nodeX = node.getXCoord();
  int nodeY = node.getYCoord();

  int dx = std::max(xCoord + radius, nodeX + width);
  int dy = std::max(yCoord + radius, nodeY + height);

  return (dx * dx + dy * dy <= radius * radius);
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
