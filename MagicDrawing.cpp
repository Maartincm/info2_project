#include <sstream>
#include <stdlib.h>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "MagicDrawing.h"

using namespace std;

canvas::canvas (int w, int h)
{
    width = w;
    height = h;
    red=254;
    green=0;
    blue=0;
    eraser=0;
    state = SDL_GetKeyboardState(NULL);
    cursor = NULL;
    last_pix_X = -1;
    last_pix_Y = -1;
    leftMouseButtonDown = false;
    rightMouseButtonDown = false;
    mirror.active = false;
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

    this->draw_mirror();

    SDL_SetWindowTitle(window, "Magic Drawing");

    SDL_RenderPresent(renderer);

}

void canvas::draw_mirror()
{
    mirror.texture = IMG_LoadTexture(renderer, "images/mirror.png");
    SDL_QueryTexture(mirror.texture, NULL, NULL, &mirror.width, &mirror.height); // get the width and height of the texture
    mirror.size.w = mirror.width / 15;
    mirror.size.h = mirror.height / 15;
    mirror.size.x = width - mirror.size.w;
    mirror.size.y = height - mirror.size.h;

    SDL_RenderCopy(renderer, mirror.texture, NULL, &mirror.size);
    this -> draw_red_cross();
}

void canvas::draw_green_tick()
{
    greentick.texture = IMG_LoadTexture(renderer, "images/greentick.png");
    SDL_QueryTexture(greentick.texture, NULL, NULL, &greentick.width, &greentick.height); // get the width and height of the texture
    greentick.size.w = greentick.width / 14;
    greentick.size.h = greentick.height / 12;
    greentick.size.x = width - greentick.size.w;
    greentick.size.y = height - greentick.size.h;

    SDL_RenderCopy(renderer, greentick.texture, NULL, &greentick.size);
    SDL_RenderPresent(renderer);
}

void canvas::draw_red_cross()
{
    redcross.texture = IMG_LoadTexture(renderer, "images/redcross.png");
    SDL_QueryTexture(redcross.texture, NULL, NULL, &redcross.width, &redcross.height); // get the width and height of the texture
    redcross.size.w = redcross.width / 32;
    redcross.size.h = redcross.height / 32;
    redcross.size.x = width - redcross.size.w;
    redcross.size.y = height - redcross.size.h;

    SDL_RenderCopy(renderer, redcross.texture, NULL, &redcross.size);
    SDL_RenderPresent(renderer);
}

void canvas::draw_classic_line(){
    SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y,
        cur_pix_X, cur_pix_Y);

    SDL_RenderDrawLine(renderer, last_pix_X+1, last_pix_Y,
        cur_pix_X+1, cur_pix_Y);

    SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y-1,
        cur_pix_X, cur_pix_Y-1);

    SDL_RenderPresent(renderer);
}

void canvas::draw_mirror_line(){
    SDL_RenderDrawLine(renderer, last_pix_X+2*(unsigned int) (width/2 - last_pix_X),
        last_pix_Y, cur_pix_X+2*(unsigned int)(width/2 -  cur_pix_X), cur_pix_Y);

    SDL_RenderDrawLine(renderer, last_pix_X+2*(unsigned int) (width/2 - last_pix_X)+1,
        last_pix_Y, cur_pix_X+2*(unsigned int)(width/2 -  cur_pix_X), cur_pix_Y);

    SDL_RenderDrawLine(renderer, last_pix_X+2*(unsigned int)(width/2 - last_pix_X),
        last_pix_Y-1, cur_pix_X+2*(unsigned int)(width/2 -  cur_pix_X), cur_pix_Y-1);

    this -> draw_classic_line();
}

void canvas::check_mirror_state()
{
    if (mirror.active)
    {
        this -> draw_red_cross();
        mirror.active = false;
    }
    else
    {
        this -> draw_green_tick();
        mirror.active = true;
    }
}

void canvas::_draw()
{
    int i=0,T=1;
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
                // surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
                // if (state[SDL_SCANCODE_TAB])
                // {
                //     i++;
                //     eraser=0;
                // }
                //
                // if (state[SDL_SCANCODE_N])
                // {
                //     T=1;
                // }
                //
                // if (state[SDL_SCANCODE_M])
                // {
                //     T=2;
                // }

                // SDL_SetRenderTarget(renderer, texture);
                // SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
                // SDL_FreeSurface(surface);
                break;


            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown)
                {
					SDL_ShowCursor(SDL_DISABLE);
                    if (last_pix_X == -1)
                    {
                        SDL_GetMouseState(&last_pix_X, &last_pix_Y);
                    }
                    else
                    {
                        // Set the cursor color to white, in order to contrast with the background
                        // TODO rainbow
							// case(9):
                                if(red==254 && green<254 && blue==0)
                                {
                                    green+=2;
                                }
                                if(red>0 && green==254 && blue==0)
                                {
                                    red-=2;
                                }
                                if(red==0 && green==254 && blue<254)
                                {
                                    blue+=2;
                                }
                                if(red==0 && green>0 && blue==254)
                                {
                                    green-=2;
                                }
                                if(red<254 && green==0 && blue==254)
                                {
                                    red+=2;
                                }
                                if(red==254 && green==0 && blue>0)
                                {
                                    blue-=2;
                                }

                                SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);

                                if(T==1)
                                {
                                    SDL_SetWindowTitle(window, "Magic Drawing: RAINBOW");
                                }
                                else
                                {
                                    SDL_SetWindowTitle(window, "Magic Drawing: MIRROR RAINBOW");
                                }
                    }

                    if (eraser==1)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        // SDL_SetWindowTitle(window, "Magic Drawing: BORRADOR");
                    }

                    if (state[SDL_SCANCODE_N])
                    {
                        T=1;
                    }

                    if (state[SDL_SCANCODE_M])
                    {
                        T=2;
                    }

                    // Save current pointer position
                    SDL_GetMouseState(&cur_pix_X, &cur_pix_Y);
                    //Avoid Drawing on top of Mirror image
                    if (cur_pix_X > mirror.size.x && cur_pix_Y > mirror.size.y)
                    {
                        last_pix_X = -1;
                    }
                    else
                    {
                        if(!mirror.active)
                        {
                            this -> draw_classic_line();
                        }

                        if(mirror.active)
                        {
                            this -> draw_mirror_line();
                        }
                        last_pix_X = cur_pix_X;
                        last_pix_Y = cur_pix_Y;
                    }
                }
                break;


            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = false;
                    SDL_ShowCursor(SDL_ENABLE);
                    last_pix_X = -1;
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                    rightMouseButtonDown = false;
                break;


            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    leftMouseButtonDown = true;
                    SDL_GetMouseState(&cur_pix_X, &cur_pix_Y);
                    if (cur_pix_X > mirror.size.x && cur_pix_Y > mirror.size.y)
                    {
                        this -> check_mirror_state();
                    }
                }
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
				// 	SDL_Surface *sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
				// 	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
				// 	printf("ingrese el nombre con el que se guardara el dibujo \n");
				// 	scanf("%s",name);
				// 	SDL_SaveBMP(sshot, name);
				// 	SDL_FreeSurface(sshot);
                //     // Color to black, and refresh to erase all the window
                //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                //     SDL_RenderClear(renderer);
                //     SDL_RenderPresent(renderer);
                //     // Keep drawing in white afterwards
                //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    rightMouseButtonDown = true;
                //     last_pix_X = -1;
                //     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                //          "The creation was saved",
                //          "",
                //          NULL);
                //
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
    // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION ,
    //                      "Instrucciones",
    //                      "Con TAB se cambiara de color\nCon B se podra emplear el Borrador\nCon M se activara la funcion espejo y con N se volvera a la normalidad\nCon el boton izquierdo se dara por concluido y guardado el dibujo",
    //                      NULL);
    //

    canvas win(width, height);
    win.create_window();

    win._draw();

    return 0;
}
