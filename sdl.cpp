#include <sstream>
#include <stdlib.h>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
        SDL_Surface *surface;
        SDL_Texture *texture;

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

    SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

    // Set the color to Black, render that color and show it
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetWindowTitle(window, "Magic Drawing");

    SDL_ShowCursor(SDL_DISABLE);

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

            case SDL_KEYDOWN:
                surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);


                SDL_SetRenderTarget(renderer, texture);

                SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
                IMG_SavePNG(surface, "image.bmp");
                SDL_FreeSurface(surface);
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
                        SDL_RenderDrawLine(renderer, last_pix_X+1, last_pix_Y,
                                                     cur_pix_X+1, cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y-1,
                                                     cur_pix_X, cur_pix_Y-1);
                        SDL_RenderPresent(renderer);
                        last_pix_X = cur_pix_X;
                        last_pix_Y = cur_pix_Y;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = false;
                    last_pix_X = -1;
                }
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
                    last_pix_X = -1;
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
