#include "quadtreenode.hpp"
#include <memory>
#include <vector>

class QuadTree {
private:
  int capacity;
  bool divided;
  QuadTreeNode boundary;
  struct QuadTreeNodes {
    std::unique_ptr<QuadTree> northEast = nullptr;
    std::unique_ptr<QuadTree> northWest = nullptr;
    std::unique_ptr<QuadTree> southEast = nullptr; // std make unique here
    std::unique_ptr<QuadTree> southWest = nullptr;
  };
  QuadTreeNodes nodes;
  std::vector<Point> points;

public:
  QuadTree(QuadTreeNode boundary, int capacity);
  bool canContain(Point p);
  void insertPoint(Point p);
  void subDivide();
  std::vector<Point> query(QuadTree &node, std::vector<Point> &);
};
