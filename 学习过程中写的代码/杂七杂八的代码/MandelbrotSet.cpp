#include "SDL2/SDL.h"
// #include "SDL_render.h"

#include <complex>
#include <numeric>
// #include <cmath>
#include <iostream>

int is_in_set(std::complex<double> c) {
    std::complex<double> z { 0.0, 0.0 };
    for (int i {}; i < 25; ++i) {
        z = std::pow(z, 2) + c;
        if (std::norm(z) > 10) {
            return i;
        }
    }
    return 0;
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window {};
    SDL_Renderer *renderer {};
    SDL_CreateWindowAndRenderer(2000, 2000, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 2, 2);

    for (double x {}; x < 1.0; x += 0.0001) {
        for (double y {}; y < 1.0; y += 0.0001) {
            auto point_x { std::lerp(-2.0, 2.0, x) };
            auto point_y { std::lerp(-2.0, 2.0, y) };
            auto iters { is_in_set({ point_x, point_y }) };
            if (iters == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            } else {
                SDL_SetRenderDrawColor(renderer, 255 - iters, 255 - iters,
                                       255 - iters, 255);
                SDL_RenderDrawPointF(renderer, x * 1000, y * 1000);
            }
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);

    return 0;
}
