#include "quadtreenode.hpp"

QuadTreeNode::QuadTreeNode(int w, int h, int x, int y) {
  width = w;
  height = h;
  xCoord = x;
  yCoord = y;
}

bool QuadTreeNode::canContain(Point p) {
  auto pointXVal = p.getX();
  auto pointYVal = p.getY();

  if (pointXVal >= xCoord - width && pointXVal <= xCoord + width &&
      pointYVal >= yCoord - height && pointYVal <= yCoord + height) {
    return true;
  }
  return false;
}

bool QuadTreeNode::contains(QuadTreeNode node) {
  return (node.xCoord + node.width < xCoord + width &&
          node.xCoord - node.width > xCoord - width &&
          node.yCoord + node.height < yCoord + height &&
          node.yCoord - node.height > yCoord - height);
}

int QuadTreeNode::getWidth() { return width; }

int QuadTreeNode::getHeight() { return height; }

int QuadTreeNode::getXCoord() { return xCoord; }

int QuadTreeNode::getYCoord() { return yCoord; }

bool QuadTreeNode::intersects(QuadTreeNode node) {
  return !(node.xCoord - node.width > xCoord + width ||
           node.xCoord + node.width < xCoord - width ||
           node.yCoord - node.height > yCoord + height ||
           node.yCoord + node.height < yCoord - height);
}
