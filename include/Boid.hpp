#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Boid {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    float maxSpeed = 4.0f;
    float maxForce = 0.1f;
    float perceptionRadius = 50.0f;

    Boid(float x, float y) noexcept;
    
    sf::Vector2f align(const std::vector<Boid*>& boids) const noexcept;
    sf::Vector2f cohesion(const std::vector<Boid*>& boids) const noexcept;
    sf::Vector2f separation(const std::vector<Boid*>& boids) const noexcept;
    void flock(const std::vector<Boid*>& boids) noexcept;
    void update() noexcept;
    void edges(const float width, const float height) noexcept;
    void draw(sf::RenderWindow& window) const;

private:
    constexpr float magnitude(const sf::Vector2f& v) const noexcept;
    constexpr sf::Vector2f normalize(const sf::Vector2f& v) const noexcept;
    constexpr sf::Vector2f setMag(const sf::Vector2f& v, const float newMag) const noexcept;
    constexpr sf::Vector2f limit(const sf::Vector2f& v, const float max) const noexcept;
};

#endif