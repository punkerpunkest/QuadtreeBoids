#include "profiler.hpp"
#include <SFML/Graphics.hpp>
#include "Boid.hpp"
#include "quadtree.hpp"
#include "quadtreenode.hpp"
#include "arena.hpp"
#include "point.hpp"
#include <vector>
#include <iostream>

int main() {
    constexpr int WIDTH = 1200;
    constexpr int HEIGHT = 800;    

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Boids Flocking");
    window.setFramerateLimit(60);
    
    std::vector<Boid> boids;
    boids.reserve(30);

    int frameCount = 0;
    bool showQuadTree = true; 
    sf::Clock printClock;
    for (int i = 0; i < 30; i++) {
        float x = rand() % WIDTH;
        float y = rand() % HEIGHT;
        boids.emplace_back(x, y);
    }
    Arena* arena = createArena(1024 * 1024);

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
        resetArena(arena);

        QuadTreeNode boundary(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
        QuadTree tree(boundary, 4, arena);

        {
            PROFILE("QuadTree Build");
            for (auto& boid : boids) {
                Point p(boid.getX(), boid.getY(), &boid);
                tree.insertPoint(p);
            }
        }
        
        {
            PROFILE("Flocking");
            for (auto& boid: boids) {
                boid.flock(tree);
                boid.update();
                boid.edges(WIDTH, HEIGHT);
            }
        }
        
        window.clear(sf::Color::Black);
        
        if (showQuadTree) {
            tree.draw(window, sf::Color(100, 100, 100, 128));
        }
        
        for (auto& boid: boids) {
            boid.draw(window);
        }
        
       window.display();

        if (printClock.getElapsedTime().asSeconds() >= 5.0f) {
            Profiler::get().print();
            printClock.restart();
        }
    }

    freeArena(arena);
    return 0;
}
