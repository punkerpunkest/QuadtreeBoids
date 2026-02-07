#include "profiler.hpp"
#include "Boid.hpp"
#include "circle.hpp"
#include "quadtree.hpp"
#include "point.hpp"
#include <cmath>
#include <iostream>

Boid::Boid(const float x, const float y) noexcept 
    : position(x, y)
    , acceleration(0.0f, 0.0f)
    , velocity(
        (rand() % 200 - 100) / 50.0f,
        (rand() % 200 - 100) / 50.0f
    ) {}

sf::Vector2f Boid::align(QuadTree& tree) const noexcept {
    PROFILE("Boid::align");
    Circle range(position.x, position.y, perceptionRadius);
    std::vector<Point> nearbyPoints;
    tree.queryCircle(tree, range, nearbyPoints);
    
    sf::Vector2f steering(0.0f, 0.0f);
    int total = 0;
    
    for (auto& point : nearbyPoints) {
        Boid* other = point.getBoid();
        if (!other || other == this) {
            continue;
        }
        
        steering += other->velocity;
        ++total;
    }
    
    if (total > 0) {
        steering /= static_cast<float>(total);
        steering = setMag(steering, maxSpeed);
        steering -= velocity;
        steering = limit(steering, maxForce);
    }
    
    return steering;
}

sf::Vector2f Boid::cohesion(QuadTree& tree) const noexcept {
    PROFILE("Boid::cohesion");
    Circle range(position.x, position.y, perceptionRadius);
    std::vector<Point> nearbyPoints;
    tree.queryCircle(tree, range, nearbyPoints);
    
    sf::Vector2f steering(0.0f, 0.0f);
    int total = 0;
    
    for (auto& point : nearbyPoints) {
        Boid* other = point.getBoid();
        if (!other || other == this) continue;
        
        const float d = magnitude(position - other->position);
        if (d < perceptionRadius && d > 0) {
            steering += other->position;
            ++total;
        }
    }
    
    if (total > 0) {
        steering /= static_cast<float>(total);
        steering -= position;
        steering = setMag(steering, maxSpeed);
        steering -= velocity;
        steering = limit(steering, maxForce);
    }
    
    return steering;
}

sf::Vector2f Boid::separation(QuadTree& tree) const noexcept {
    PROFILE("Boid::separation");
    Circle range(position.x, position.y, perceptionRadius);
    std::vector<Point> nearbyPoints;
    tree.queryCircle(tree, range, nearbyPoints);
    
    sf::Vector2f steering(0.0f, 0.0f);
    int total = 0;
    
    for (auto& point : nearbyPoints) {
        Boid* other = point.getBoid();
        if (!other || other == this) continue;
        
        const float d = magnitude(position - other->position);
        if (d < perceptionRadius && d > 0) {
            sf::Vector2f diff = position - other->position;
            diff /= (d * d);
            steering += diff;
            ++total;
        }
    }
    
    if (total > 0) {
        steering /= static_cast<float>(total);
        steering = setMag(steering, maxSpeed);
        steering -= velocity;
        steering = limit(steering, maxForce);
    }
    
    return steering;
}

void Boid::flock(QuadTree& tree) noexcept {
    PROFILE("Boid::flock");
    const sf::Vector2f alignment = align(tree);
    const sf::Vector2f cohesionForce = cohesion(tree);
    const sf::Vector2f separationForce = separation(tree);
    
    acceleration += alignment * 1.5f;
    acceleration += cohesionForce * 1.2f;
    acceleration += separationForce * 1.2f;
}

void Boid::update() noexcept {
    velocity += acceleration;
    velocity = limit(velocity, maxSpeed);
    position += velocity;
    acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Boid::edges(const float width, const float height) noexcept {
    if (position.x > width) position.x = 0.0f;
    else if (position.x < 0.0f) position.x = width;

    if (position.y > height) position.y = 0.0f;
    else if (position.y < 0.0f) position.y = height;
}

void Boid::draw(sf::RenderWindow& window) const {
    sf::ConvexShape triangle(3);
    
    const float angle = std::atan2(velocity.y, velocity.x);
    
    triangle.setPoint(0, sf::Vector2f(10.0f, 0.0f));
    triangle.setPoint(1, sf::Vector2f(-5.0f, 5.0f));
    triangle.setPoint(2, sf::Vector2f(-5.0f, -5.0f));
    
    triangle.setFillColor(sf::Color::White);
    triangle.setPosition(position);
    triangle.setRotation(sf::degrees(angle * 180.0f / 3.14159f));
    window.draw(triangle);
}

constexpr float Boid::magnitude(const sf::Vector2f& v) const noexcept {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

constexpr sf::Vector2f Boid::normalize(const sf::Vector2f& v) const noexcept {
    const float mag = magnitude(v);
    if (mag > 0.0f) return v / mag;
    return v;
}

constexpr sf::Vector2f Boid::setMag(const sf::Vector2f& v, const float newMag) const noexcept {
    return normalize(v) * newMag;
}

constexpr sf::Vector2f Boid::limit(const sf::Vector2f& v, const float max) const noexcept {
    const float mag = magnitude(v);
    if (mag > max) {
        return (v / mag) * max;
    }
    return v;
}