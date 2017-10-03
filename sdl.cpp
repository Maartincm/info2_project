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
        int x = 0;
        int y = 0;
        SDL_Texture * texture;
        SDL_Renderer * renderer;
        SDL_Window * window;
        SDL_Event event;
        Uint32 * pixels;
        bool leftMouseButtonDown = false;
        bool rightMouseButtonDown = false;
        bool quit = false;

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

    SDL_Init(SDL_INIT_VIDEO);

    // window = SDL_CreateWindow("SDL2 Pixel Drawing",
    //     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    //
    // renderer = SDL_CreateRenderer(window, -1, 0);
    
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // texture = SDL_CreateTexture(renderer,
    //     SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
    // pixels = new Uint32[width * height];

    // memset(pixels, 255, width * height * sizeof(Uint32));

}

void canvas::_draw()
{
    while (!quit)
    {
        // SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:  x--; break;
                    case SDLK_RIGHT: x++; break;
                    case SDLK_UP:    y--; break;
                    case SDLK_DOWN:  y++; break;
                }
                break;

            case SDL_QUIT:
                quit = true;
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
                    rightMouseButtonDown = true;

            case SDL_MOUSEMOTION:
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                std::stringstream ss;
                ss << "X: " << mouseX << " Y: " << mouseY;

                SDL_SetWindowTitle(window, ss.str().c_str());
              
                if (leftMouseButtonDown)
                {
                    if (last_pix_X == -1)
                    {
                        SDL_GetMouseState(&last_pix_X, &last_pix_Y);
                        // cout << "\n" << last_pix_X << "\t" << last_pix_Y;
                    }
                    else{
                        SDL_GetMouseState(&cur_pix_X, &cur_pix_Y);

                        // cout << "\n" << last_pix_X << "\t" << last_pix_Y;
                        // cout << "\n" << cur_pix_X << "\t" << cur_pix_Y;
                        // cout << "\n\n";
                        SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y,
                                                     cur_pix_X, cur_pix_Y);
                        last_pix_X = cur_pix_X;
                        last_pix_Y = cur_pix_Y;
                    }

                    // pixels[mouseY * width + mouseX+2] = 0;                    
                    // pixels[mouseY * width + mouseX+1] = 0;
                    // pixels[mouseY * width + mouseX] = 0;
                    // pixels[mouseY * width + mouseX-1] = 0;
                    // pixels[mouseY * width + mouseX-2] = 0;
                    // pixels[mouseY * width + width + mouseX+2] = 0;
                    // pixels[mouseY * width + width + mouseX+1] = 0;
                    // pixels[mouseY * width + width + mouseX] = 0;
                    // pixels[mouseY * width + width + mouseX-1] = 0;
                    // pixels[mouseY * width + width + mouseX-2] = 0;
                    // pixels[mouseY * width - width + mouseX+2] = 0;  
                    // pixels[mouseY * width - width + mouseX+1] = 0;
                    // pixels[mouseY * width - width + mouseX] = 0;
                    // pixels[mouseY * width - width + mouseX-1] = 0;
                    // pixels[mouseY * width - width + mouseX-2] = 0;
                    // //pixels[mouseY * width + width * 2 + mouseX+2] = 0;
                    // pixels[mouseY * width + width * 2 + mouseX+1] = 0;
                    // pixels[mouseY * width + width * 2 + mouseX] = 0;
                    // pixels[mouseY * width + width * 2 + mouseX-1] = 0;
                    // //pixels[mouseY * width + width * 2 + mouseX-2] = 0;
                    // //pixels[mouseY * width - width * 2 + mouseX+2] = 0;  
                    // pixels[mouseY * width - width * 2 + mouseX+1] = 0;
                    // pixels[mouseY * width - width * 2 + mouseX] = 0;
                    // pixels[mouseY * width - width * 2 + mouseX-1] = 0;
                    // //pixels[mouseY * width - width * 2 + mouseX-2] = 0;
                }
                  if (rightMouseButtonDown)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                     
                 // memset(pixels, 255, width * height * sizeof(Uint32));
                /*	
                    int mouseX = event.motion.x;
                    int mouseY = event.motion.y;
                    pixels[mouseY * 640 + mouseX+2] = 1;
                    pixels[mouseY * 640 + mouseX+1] =1;
                    pixels[mouseY * 640 + mouseX] = 1;
                */}
                break;
        }

        // SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

canvas::~canvas()
{
    // delete[] pixels;
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char ** argv)
{
    int width = 1366;
    int height = 768;

    canvas win(width, height);
    win.create_window();

    win._draw();

    return 0;
}
