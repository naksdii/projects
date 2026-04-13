#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>

#include <cmath>
#include <iostream>

struct Pos {
    double x;
    double y;
    double z;
};

struct Momentum {
    double yaw = 0;
    double pitch = 0;
    double roll = 0;
    double friction = 0.90;
    double acceleration = 0.03;
};

struct Cam {
    int distance = 50;
    int fov = 90;
};
struct Angle {
    double yaw;
    double pitch;  // ts is in radians
    double roll;
};

class Cube {
   public:
    Pos p[8];
};

Cube rotate(Cube& cubeBase, Angle& radians);
void draw(Cam cam, Cube& cube, SDL_Renderer* r, int WIDTH, int HEIGHT);
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("goon", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (window == NULL) {
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == NULL) {
        return 1;
    }

    Cube cube;
    Cube GHOSTcube;
    Cam cam;
    const double TWO_PI = 2.0 * M_PI;
    Angle angle = {0.5, 0.6, 0.2};
    Momentum momentum;
    bool running = true;
    SDL_Event event;
    GHOSTcube.p[0] = {-10, -10, -10};
    GHOSTcube.p[1] = {10, -10, -10};
    GHOSTcube.p[2] = {10, 10, -10};
    GHOSTcube.p[3] = {-10, 10, -10};
    GHOSTcube.p[4] = {-10, -10, 10};
    GHOSTcube.p[5] = {10, -10, 10};
    GHOSTcube.p[6] = {10, 10, 10};
    GHOSTcube.p[7] = {-10, 10, 10};
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        momentum.yaw -= momentum.acceleration;
                        break;
                    case SDLK_RIGHT:
                        momentum.yaw += momentum.acceleration;
                        break;
                    case SDLK_UP:
                        momentum.yaw -= momentum.acceleration;
                        break;
                    case SDLK_DOWN:
                        momentum.pitch += momentum.acceleration;
                        break;
                    case SDLK_q:
                        momentum.roll -= momentum.acceleration;
                        break;
                    case SDLK_e:
                        momentum.roll += momentum.acceleration;
                        break;
                }
            }
        }
        cube = rotate(GHOSTcube, angle);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw(cam, cube, renderer, 800, 600);

        SDL_RenderPresent(renderer);
        SDL_Delay(32);
        angle.yaw += momentum.yaw;
        angle.roll += momentum.roll;
        angle.pitch += momentum.pitch;
        momentum.yaw *= momentum.friction;
        momentum.pitch *= momentum.friction;
        momentum.roll *= momentum.friction;
        angle.yaw = fmod(angle.yaw, TWO_PI);
        angle.pitch = fmod(angle.pitch, TWO_PI);
        angle.roll = fmod(angle.roll, TWO_PI);
        std::cout << "\nyaw: " << angle.yaw << "\npitch: " << angle.pitch
                  << "\nroll: " << angle.roll;
    }

    SDL_Quit();
}

Cube rotate(Cube& cubeBase, Angle& angle) {
    Cube result;

    double cy = cos(angle.yaw);
    double sy = sin(angle.yaw);

    double cp = cos(angle.pitch);
    double sp = sin(angle.pitch);

    double cr = cos(angle.roll);
    double sr = sin(angle.roll);

    for (int i = 0; i < 8; i++) {
        double x = cubeBase.p[i].x;
        double y = cubeBase.p[i].y;
        double z = cubeBase.p[i].z;

        // yaw
        double x1 = cy * x - sy * z;
        double z1 = sy * x + cy * z;
        double y1 = y;

        // pitch
        double y2 = cp * y1 - sp * z1;
        double z2 = sp * y1 + cp * z1;
        double x2 = x1;

        // roll
        double x3 = cr * x2 - sr * y2;
        double y3 = sr * x2 + cr * y2;
        double z3 = z2;

        result.p[i] = {x3, y3, z3};
    }

    return result;
};
void draw(Cam cam, Cube& cube, SDL_Renderer* r, int WIDTH, int HEIGHT) {
    double fovRad = cam.fov * M_PI / 180.0;
    double f = 1 / tan(fovRad / 2.0);  // fator de projeção

    // 1. Projetar todos os vértices
    struct Vec2 {
        int x, y;
    };
    Vec2 verts2D[8];

    for (int i = 0; i < 8; i++) {
        double x = cube.p[i].x;
        double y = cube.p[i].y;
        double z = cube.p[i].z;

        double z_c = z + cam.distance;
        if (z_c <= 0.1) z_c = 0.1;  // evita divisão por zero

        int x2D = (int)((x / z_c) * f * WIDTH / 2 + (double)WIDTH / 2);
        int y2D = (int)((-y / z_c) * f * HEIGHT / 2 + (double)HEIGHT / 2);

        verts2D[i] = {x2D, y2D};
    }

    // 2. Arestas do cubo
    int edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},  // inferior
        {4, 5}, {5, 6}, {6, 7}, {7, 4},  // superior
        {0, 4}, {1, 5}, {2, 6}, {3, 7}   // verticais
    };

    // 3. Desenhar linhas
    for (int i = 0; i < 12; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        SDL_RenderDrawLine(r, verts2D[a].x, verts2D[a].y, verts2D[b].x,
                           verts2D[b].y);
    }
}
