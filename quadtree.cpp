#include "quadtree.hpp"
#include "circle.hpp"
#include "quadtreenode.hpp"
#include <memory>
#include <vector>

QuadTree::QuadTree(QuadTreeNode boundary, int capacity)
    : boundary(boundary), capacity(capacity), divided(false) {};

bool QuadTree::canContain(Point p) {
  if (boundary.canContain(p)) {
    return true;
  } else {
    return false;
  }
}

void QuadTree::insertPoint(Point p) {
  if (points.size() < capacity) {
    points.push_back(p);
  } else {
    if (!divided) {
      this->subDivide();
    } else {
      if (nodes.northEast->canContain(p)) {
        nodes.northEast->insertPoint(p);
      } else if (nodes.northWest->canContain(p)) {
        nodes.northWest->insertPoint(p);
      } else if (nodes.southEast->canContain(p)) {
        nodes.southEast->insertPoint(p);
      } else {
        nodes.southWest->insertPoint(p);
      };
      // is it worth doing else if above and throwing ? not sure if worth
      // accounting for out of range of entire area, or if we account for that
      // at the start
    };
  }
}

void QuadTree::subDivide() {
  auto width = boundary.getWidth();
  auto height = boundary.getHeight();
  auto xCoord = boundary.getXCoord();
  auto yCoord = boundary.getYCoord();

  auto northEastBoundary = QuadTreeNode(
      width / 2, height / 2, xCoord + width / 2, yCoord + height / 2);
  auto northWestBoundary = QuadTreeNode(
      width / 2, height / 2, xCoord - width / 2, yCoord + height / 2);
  auto southEastBoundary = QuadTreeNode(
      width / 2, height / 2, xCoord + width / 2, yCoord - height / 2);
  auto southWestBoundary = QuadTreeNode(
      width / 2, height / 2, xCoord - width / 2, yCoord - height / 2);

  nodes.northEast = std::make_unique<QuadTree>(northEastBoundary, capacity);
  nodes.northWest = std::make_unique<QuadTree>(northWestBoundary, capacity);
  nodes.southEast = std::make_unique<QuadTree>(southEastBoundary, capacity);
  nodes.southWest = std::make_unique<QuadTree>(southWestBoundary, capacity);
}

void QuadTree::query(QuadTree &node, std::vector<Point> &found) {
  if (!node.boundary.intersects(boundary)) {
    return;
  }

  if (boundary.contains(
          node.boundary)) { // if we call subnodes and they are within the
                            // boundary, just add all their points
    for (auto &p : node.points) {
      found.push_back(p);
    }
    return;
  }
  // this should be correct :)
  for (auto &p : node.points) {
    if (boundary.canContain(p)) {
      found.push_back(p);
    }
  }

  if (node.divided) {
    query(*node.nodes.northEast, found);
    query(*node.nodes.northWest, found);
    query(*node.nodes.southEast, found);
    query(*node.nodes.southWest, found);
  }
}

void QuadTree::queryCircle(QuadTree &node, Circle &c,
                           std::vector<Point> &found) {
  if (!c.intersects(node.boundary)) { // circle doesn't overlap anything
    return;
  }
  if (c.completeContains(node.boundary)) {
    for (auto &p : node.points) {
      found.push_back(p);
    }
    return;
  }
  for (auto &p : node.points) {
    if (c.canContain(p)) {
      found.push_back(p);
    }
  }

  if (divided) {
    queryCircle(*node.nodes.northEast, c, found);
    queryCircle(*node.nodes.northWest, c, found);
    queryCircle(*node.nodes.southEast, c, found);
    queryCircle(*node.nodes.southWest, c, found);
  }
}
