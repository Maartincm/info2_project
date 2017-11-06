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
    red=255;
    green=255;
    blue=255;
    state = SDL_GetKeyboardState(NULL);
    cursor = NULL;
    last_pix_X = -1;
    last_pix_Y = -1;
    leftMouseButtonDown = false;
    rightMouseButtonDown = false;
    mirror.active = false;
    rainbow.active = false;
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

    // this -> draw_rainbow();
    // this -> draw_eraser();
    // this -> draw_colorpicker();
    // this -> draw_mirror();

    SDL_SetWindowTitle(window, "Magic Drawing");

    // SDL_RenderPresent(renderer);
    this -> clean_window();

}

void canvas::rainbow_progress()
{
    if(red>=253 && green>=253 && blue<=255)
    {
        blue-=3;
    }
    if(red>=253 && green<=255 && blue<=2)
    {
        green-=3;
    }
    if(red<=255 && green<=2 && blue<=2)
    {
        red-=3;
    }
    if(red<=2 && green<=2 && blue>=0)
    {
        blue+=3;
    }
    if(red<=2 && green>=0 && blue>=253)
    {
        green+=3;
    }
    if(red<=2 && green>=253 && blue<=255)
    {
        blue-=3;
    }
    if(red>=0 && green>=253 && blue<=2)
    {
        red+=3;
    }
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);

}

void canvas::check_rainbow_state()
{
    if (rainbow.active)
    {
        this -> draw_red_cross("R");
        rainbow.active = false;
    }
    else
    {
        this -> draw_green_tick("R");
        rainbow.active = true;
    }
    SDL_RenderPresent(renderer);
}

void canvas::draw_rainbow()
{
    rainbow.texture = IMG_LoadTexture(renderer, "images/rainbow.png");
    rainbow.rwop = SDL_RWFromFile("images/rainbow.png", "rb");
    rainbow.surface = IMG_LoadPNG_RW(rainbow.rwop);
    SDL_QueryTexture(rainbow.texture, NULL, NULL, &rainbow.width, &rainbow.height); // get the width and height of the texture
    rainbow.size.w = rainbow.width / 25;
    rainbow.size.h = rainbow.height / 20;
    rainbow.size.x = width / 128;
    rainbow.size.y = height / 64;

    SDL_RenderCopy(renderer, rainbow.texture, NULL, &rainbow.size);
    this -> draw_red_cross("R");
}

void canvas::draw_eraser()
{
    eraser.texture = IMG_LoadTexture(renderer, "images/eraser.png");
    eraser.rwop = SDL_RWFromFile("images/eraser.png", "rb");
    eraser.surface = IMG_LoadPNG_RW(eraser.rwop);
    SDL_QueryTexture(eraser.texture, NULL, NULL, &eraser.width, &eraser.height); // get the width and height of the texture
    eraser.size.w = eraser.width / 6;
    eraser.size.h = eraser.height / 6;
    eraser.size.x = width - eraser.size.w;
    eraser.size.y = height / 512;

    SDL_RenderCopy(renderer, eraser.texture, NULL, &eraser.size);
}

void canvas::clean_window()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    this -> draw_eraser();
    this -> draw_colorpicker();
    this -> draw_mirror();
    this -> draw_rainbow();
    rainbow.active = false;
    mirror.active = false;
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void canvas::draw_colorpicker()
{
    colorpicker.texture = IMG_LoadTexture(renderer, "images/colorpicker.png");
    colorpicker.rwop = SDL_RWFromFile("images/colorpicker.png", "rb");
    colorpicker.surface = IMG_LoadPNG_RW(colorpicker.rwop);
    SDL_QueryTexture(colorpicker.texture, NULL, NULL, &colorpicker.width, &colorpicker.height); // get the width and height of the texture
    colorpicker.size.w = colorpicker.width * 2;
    colorpicker.size.h = colorpicker.height / 2;
    colorpicker.size.x = width / 1024;
    colorpicker.size.y = height - colorpicker.size.h;

    SDL_RenderCopy(renderer, colorpicker.texture, NULL, &colorpicker.size);
}

void canvas::get_color()
{
    colorpicker.pixelFormat = colorpicker.surface -> format;
    colorpicker.pixels = (Uint32 *)colorpicker.surface -> pixels;
    colorpicker.pix = colorpicker.pixels[(((cur_pix_Y - colorpicker.size.y) * 2 * colorpicker.width) + (cur_pix_X - colorpicker.size.x) / 2 )];
    SDL_GetRGBA(colorpicker.pix, colorpicker.pixelFormat, &red, &green, &blue, &alpha);
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
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
    this -> draw_red_cross("M");
}

void canvas::draw_green_tick(char * source)
{
    greentick.texture = IMG_LoadTexture(renderer, "images/greentick.png");
    SDL_QueryTexture(greentick.texture, NULL, NULL, &greentick.width, &greentick.height); // get the width and height of the texture
    if (source == "M")
    {
        greentick.size.w = greentick.width / 14;
        greentick.size.h = greentick.height / 12;
        greentick.size.x = width - greentick.size.w;
        greentick.size.y = height - greentick.size.h;
    }
    if (source == "R")
    {
        greentick.size.w = greentick.width / 14;
        greentick.size.h = greentick.height / 12;
        greentick.size.x = 0;
        greentick.size.y = 0;
    }

    SDL_RenderCopy(renderer, greentick.texture, NULL, &greentick.size);
    // SDL_RenderPresent(renderer);
}

void canvas::draw_red_cross(char * source)
{
    redcross.texture = IMG_LoadTexture(renderer, "images/redcross.png");
    SDL_QueryTexture(redcross.texture, NULL, NULL, &redcross.width, &redcross.height); // get the width and height of the texture

    if (source == "M")
    {
        redcross.size.w = redcross.width / 32;
        redcross.size.h = redcross.height / 32;
        redcross.size.x = width - redcross.size.w;
        redcross.size.y = height - redcross.size.h;
    }
    if (source == "R")
    {
        redcross.size.w = redcross.width / 32;
        redcross.size.h = redcross.height / 32;
        redcross.size.x = 0;
        redcross.size.y = 0;
    }

    SDL_RenderCopy(renderer, redcross.texture, NULL, &redcross.size);
    // SDL_RenderPresent(renderer);
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
        this -> draw_red_cross("M");
        mirror.active = false;
    }
    else
    {
        this -> draw_green_tick("M");
        mirror.active = true;
    }
    SDL_RenderPresent(renderer);
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
                break;


            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown)
                {
					SDL_ShowCursor(SDL_DISABLE);
                    if (last_pix_X == -1)
                    {
                        SDL_GetMouseState(&last_pix_X, &last_pix_Y);
                    }
                    // Save current pointer position
                    SDL_GetMouseState(&cur_pix_X, &cur_pix_Y);
                    //Avoid Drawing on top of Mirror image
                    if ((cur_pix_X > mirror.size.x && cur_pix_Y > mirror.size.y) || 
                        ((cur_pix_X > colorpicker.size.x) && (cur_pix_Y > colorpicker.size.y) &&
                        (cur_pix_X < (colorpicker.size.x + colorpicker.size.w)) &&
                        (cur_pix_Y < (colorpicker.size.y + colorpicker.size.h))) ||
                        (cur_pix_X > eraser.size.x) && (cur_pix_Y < eraser.size.y + eraser.size.h) ||
                        (cur_pix_X < rainbow.size.w && cur_pix_Y < rainbow.size.h))
                    {
                        last_pix_X = -1;
                    }
                    else
                    {
                        if (rainbow.active)
                        {
                            this -> rainbow_progress();
                        }

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
                    if (cur_pix_X > colorpicker.size.x && cur_pix_Y > colorpicker.size.y &&
                        cur_pix_X < colorpicker.size.x + colorpicker.size.w - 45 &&
                        cur_pix_Y < colorpicker.size.y + colorpicker.size.h)
                    {
                        this -> get_color();
                    }
                    if (cur_pix_X > eraser.size.x && cur_pix_Y < eraser.size.y + eraser.size.h)
                    {
                        this -> clean_window();
                    }
                    if (cur_pix_X < rainbow.size.w && cur_pix_Y < rainbow.size.h)
                    {
                        this -> check_rainbow_state();
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
