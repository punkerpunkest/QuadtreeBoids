#include <SFML/Graphics.hpp>
#include "Boid.hpp"
#include "quadtree.hpp"
#include "quadtreenode.hpp"
#include "point.hpp"
#include <vector>
#include <iostream>

int main() {
    constexpr int WIDTH = 1200;
    constexpr int HEIGHT = 800;    

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Boids Flocking");
    window.setFramerateLimit(60);
    
    std::vector<Boid> boids;
    boids.reserve(200);
    
    int frameCount = 0;
    bool showQuadTree = true; 
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePress->button == sf::Mouse::Button::Left) {
                    boids.emplace_back(mousePress->position.x, mousePress->position.y);
                }
            }
            
            if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPress->code == sf::Keyboard::Key::Space) {
                    showQuadTree = !showQuadTree;
    
                }
            }
        }
        
        frameCount++;
    
        QuadTreeNode boundary(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
        QuadTree tree(boundary, 1);
        
        for (auto& boid : boids) {
            Point p(boid.getX(), boid.getY(), &boid);
            tree.insertPoint(p);
        }
        
    
        for (auto& boid: boids) {
            boid.flock(tree);
            boid.update();
            boid.edges(WIDTH, HEIGHT);
        }
        
        window.clear(sf::Color::Black);
        
        if (showQuadTree) {
            tree.draw(window, sf::Color(100, 100, 100, 128));
        }
        
        for (auto& boid: boids) {
            boid.draw(window);
        }
        
       window.display();
    }

    return 0;
}
