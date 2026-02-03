#include <SFML/Graphics.hpp>
#include "Boid.hpp"
#include <vector>

int main() {
    constexpr int WIDTH = 1200;
    constexpr int HEIGHT = 800;
    
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Boids Flocking");
    window.setFramerateLimit(60);
    
    std::vector<Boid> boids;
    boids.reserve(200);
    
    std::vector<Boid*> boidPtrs;
    boidPtrs.reserve(200);
    
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
        }
        
        boidPtrs.clear();
        for (auto& boid: boids) {
            boidPtrs.push_back(&boid);
        }
        
        for (auto& boid: boids) {
            boid.flock(boidPtrs);
            boid.update();
            boid.edges(WIDTH, HEIGHT);
        }
        
        window.clear(sf::Color::Black);
        
        for (auto& boid: boids) {
            boid.draw(window);
        }
        
        window.display();
    }
    
    return 0;
}