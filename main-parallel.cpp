#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
// Define maze dimensions
const int ROWS = 10;
const int COLS = 10;

// Define maze structure
char maze[ROWS][COLS] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

// Define particle structure
struct Particle {
    int x;
    int y;
};

// Function to move particles randomly
void moveParticle(Particle& particle) {
    int direction = rand() % 4; // 0: up, 1: down, 2: left, 3: right

    // Move particle according to the direction
    switch(direction) {
        case 0:
            if (maze[particle.x - 1][particle.y] != '#')
                particle.x--;
            break;
        case 1:
            if (maze[particle.x + 1][particle.y] != '#')
                particle.x++;
            break;
        case 2:
            if (maze[particle.x][particle.y - 1] != '#')
                particle.y--;
            break;
        case 3:
            if (maze[particle.x][particle.y + 1] != '#')
                particle.y++;
            break;
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    std::vector<Particle> particles;

    // Initialize particles at starting position
    for (int i = 0; i < 100; ++i) {
        particles.push_back({1, 1}); // Start from (1,1)
    }

    // Move particles randomly until one reaches the exit
    while (true) {
#pragma omp parallel for default(shared)
        for (Particle& particle : particles) {
            moveParticle(particle);
            printf("Thread n:%d x %d y %d \n", omp_get_thread_num(), particle.x, particle.y);
            if (particle.x == ROWS - 2 && particle.y == COLS - 2) { // Exit found
                printf("Exit found at position: (%d, %d)", particle.x , particle.y);
            }
        }
    }

    return 0;
}