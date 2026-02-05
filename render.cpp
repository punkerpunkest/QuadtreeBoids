
#include <SFML/Graphics.hpp>
#include <vector>
#include "point.hpp"
#include "quadtree.hpp"
#include "circle.hpp"
#include "quadtreenode.hpp"

// just for example guys 
struct Boid {
    Point position;

    Boid(double x, double y) : position(x, y) {}
    double getX() { return position.getX(); }
    double getY() { return position.getY(); }
};

// just drawing the quadree rectanlge for better understanding 
void drawQuadTree(sf::RenderWindow &window, QuadTree &qt) {
    
    QuadTreeNode boundary = qt.boundary;
    sf::RectangleShape rect(sf::Vector2f(boundary.getWidth()*2, boundary.getHeight()*2));
    rect.setPosition(boundary.getXCoord() - boundary.getWidth(), boundary.getYCoord() - boundary.getHeight());
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(1);
    window.draw(rect);

    if (qt.divided) {
        drawQuadTree(window, *qt.nodes.northEast);
        drawQuadTree(window, *qt.nodes.northWest);
        drawQuadTree(window, *qt.nodes.southEast);
        drawQuadTree(window, *qt.nodes.southWest);
    }
}

int main() {
    // the main screen 
    sf::RenderWindow window(sf::VideoMode(800, 600), "Boids Simulation");

    // will replace this with the main points after jordan finishes
    std::vector<Boid> boids;
    for (int i = 0; i < 50; i++) {
        boids.emplace_back(rand() % 800, rand() % 600);
    }

    // chose circle shape initially but i think triangles would be better
    std::vector<sf::CircleShape> boidShapes;
    for (auto &boid : boids) {
        sf::CircleShape shape(5); /
        shape.setOrigin(5, 5);    
        shape.setFillColor(sf::Color::White);
        boidShapes.push_back(shape);
    }

    /
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Drawing the boids
        for (size_t i = 0; i < boids.size(); i++) {
            boidShapes[i].setPosition(boids[i].getX(), boids[i].getY());
            window.draw(boidShapes[i]);
        }

        
        window.display();
    }

    return 0;
}
