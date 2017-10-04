#include <sstream>
#include <stdlib.h>
#include <sstream>
#include <SDL2/SDL.h>

#include <iostream>
using namespace std;

class canvas
{
    private:
        int last_pix_X = -1;
        int last_pix_Y = -1;
        int cur_pix_X;
        int cur_pix_Y;
        int width;
        int height;
        bool leftMouseButtonDown = false;
        bool rightMouseButtonDown = false;
        SDL_Renderer * renderer;
        SDL_Window * window;
        SDL_Event event;
        SDL_bool done = SDL_FALSE;

    public:
        canvas(int w, int h);
        ~canvas();
        void create_window();
        void _draw();
};

canvas::canvas (int w, int h)
{
    width = w;
    height = h;
}

void canvas::create_window()
{

    // Start the SDL widget
    SDL_Init(SDL_INIT_VIDEO);
    
    // Draw the main window and instanciate the cursor
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

    // Set the color to Black, render that color and show it
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetWindowTitle(window, "Magic Drawing");
    SDL_RenderPresent(renderer);

}

void canvas::_draw()
{
    // Keep thw window open until it's explicitly closed
    while (!done)
    {
        // Wait for something to happen, then take the correct action
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                done = SDL_TRUE;
                break;

            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown)
                {
                    if (last_pix_X == -1)
                    {
                        SDL_GetMouseState(&last_pix_X, &last_pix_Y);
                    }
                    else
                    {
                        // Save current pointer position
                        SDL_GetMouseState(&cur_pix_X, &cur_pix_Y);
                        // Set the cursor color to white, in order to contrast with the background
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                        // Draw line from last point to current point and refresh the renderer
                        SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y,
                                                     cur_pix_X, cur_pix_Y);
                        SDL_RenderPresent(renderer);
                        last_pix_X = cur_pix_X;
                        last_pix_Y = cur_pix_Y;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                if (event.button.button == SDL_BUTTON_RIGHT)
                    rightMouseButtonDown = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = true;
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    // Color to black, and refresh to erase all the window
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    // Keep drawing in white afterwards
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    rightMouseButtonDown = true;
                }
                break;
        }
    }
}

canvas::~canvas()
{
    // Free all the used memory
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char ** argv)
{
    int width = 1360;
    int height = 710;

    canvas win(width, height);
    win.create_window();

    win._draw();

    return 0;
}
