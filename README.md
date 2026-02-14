# Flocking Simulator

![Flocking Simulator](https://github.com/user-attachments/assets/3c0b21fc-bd78-42ef-82b1-e52142cace2e)

From the land to the sea to the air, flocking behavior can be seen in many animals. We found it fascinating that by just modeling our agents to follow a couple of rules to avoid collision, this behavior can be closely mirrored. The project also allowed us to optimize many features. As of late, we've improved neighbor queries with the QuadTree data structure, reduced allocation overhead with a custom arena memory allocator, and benchmarked the results with a custom profiler.

## Flocking Features

### Performance and Spatial Optimizations
- **Quad Tree Partitioning**: Space subdivision for O(n log n) neighbor queries
- **Circular Range Queries**: Intersection tests with early pruning
- **Arena Allocator**: Reduced allocation overhead and improved cache locality
- **Custom Profile**: Benchmarking tool validates 4x speedup

### Boid behaviors
- **Alignment**: Boids steer toward the average velocity of their neighbors
- **Cohesion**: Boids move towards the center of local flocks
- **Separation**: Boids avoid crowding

To try out this project, the following are necessary:

## Prerequisites

- C++20 compatible compiler
- SFML

## Installation

### macOS
```bash
brew install sfml 
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsfml-dev
```

## To run

```bash
make
make run
```
