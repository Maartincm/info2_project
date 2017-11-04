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

    SDL_RenderPresent(renderer);

}

void canvas::_draw()
{	   
     SDL_GetKeyboardState(NULL);
    SDL_Cursor *cursor = NULL;
    char nombre[24];
    int i=0,r=254,g=0,b=0,ERASER=0,T=1;
    // Keep thw window open until it's explicitly closed
	 SDL_RenderSetScale(renderer,
                       1,
                       1);

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
			if (state[SDL_SCANCODE_TAB])
			{i++;
			 ERASER=0;}
			  if (state[SDL_SCANCODE_N])
                        T=1;
              if (state[SDL_SCANCODE_M])
                        T=2;
				switch(i)
                        {
							case(1):if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: WHITE");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR WHITE");
							break;
							case(2): if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: RED");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR RED");
							break;
							case(3): if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: ORANAGE");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR ORANGE");
							break;
							case(4): if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: YELLOW");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR YELLOW");
							break;
							case(5): if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: GREEN");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR GREEN");
							break;
							case(6): if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: CIAM");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR CIAM");
							break;
							case(7): if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: BLUE");
									 else
				{i=0;
				 ERASER=1;
				}
                SDL_SetRenderTarget(renderer, texture);

                SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
                //IMG_SavePNG(surface, "image.bmp");
                SDL_FreeSurface(surface);
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
                        // Save current pointer position
                        SDL_GetMouseState(&cur_pix_X, &cur_pix_Y);
                        // Set the cursor color to white, in order to contrast with the background
                        switch(i)
                        {
							case(1): SDL_SetRenderDrawColor(renderer,255,255,255, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: WHITE");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR WHITE");
							break;
							case(2): SDL_SetRenderDrawColor(renderer,255,0,0, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: RED");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR RED");
							break;
							case(3): SDL_SetRenderDrawColor(renderer,255,80,0, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: ORANGE");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR ORANGE");
							break;
							case(4): SDL_SetRenderDrawColor(renderer,255,255,0, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: YELLOW");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR YELLOW");
							break;
							case(5): SDL_SetRenderDrawColor(renderer,0,255,0, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: GREEN");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR GREEN");
							break;
							case(6): SDL_SetRenderDrawColor(renderer,0,255,255, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: CIAM");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR CIAM");
							break; 
							case(7): SDL_SetRenderDrawColor(renderer,0,0,255, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: BLUE");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR BLUE");
							break;
							case(8): SDL_SetRenderDrawColor(renderer,255,0,255, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: VIOLET");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR VIOLET");
							break;
							case(9): if(red==254 && green<254 && blue==0)
									 green+=2;
									 if(red>0 && green==254 && blue==0)
									 red-=2;
									 if(red==0 && green==254 && blue<254)
									 blue+=2;
									 if(red==0 && green>0 && blue==254)
									 green-=2;
									 if(red<254 && green==0 && blue==254)
									 red+=2;
									 if(red==254 && green==0 && blue>0)
									 blue-=2;
									 SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
									 if(T==1)
									 SDL_SetWindowTitle(window, "Magic Drawing: RAINBOW");
									 else
									 SDL_SetWindowTitle(window, "Magic Drawing: MIRROR RAINBOW");
							break;
							default: if(i>0) i=1;
						}
						if (eraser==1)
				{
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_SetWindowTitle(window, "Magic Drawing: BORRADOR");
				}
                        if (state[SDL_SCANCODE_N])
                        T=1;
						if (state[SDL_SCANCODE_M])
                        T=2;
                        if(T==1)
					    {
                        SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y,
                                                     cur_pix_X, cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X+1, last_pix_Y,
                                                     cur_pix_X+1, cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y-1,
                                                     cur_pix_X, cur_pix_Y-1);
                        SDL_RenderPresent(renderer);
                      
						}
						if(T==2)
						{
						SDL_RenderDrawLine(renderer, last_pix_X+2*(unsigned int) (width/2 - last_pix_X), last_pix_Y,
                                                     cur_pix_X+2*(unsigned int)(width/2 -  cur_pix_X), cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X+2*(unsigned int) (width/2 - last_pix_X)+1, last_pix_Y,
                                                     cur_pix_X+2*(unsigned int)(width/2 -  cur_pix_X), cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X+2*(unsigned int)(width/2 - last_pix_X), last_pix_Y-1,
                                                     cur_pix_X+2*(unsigned int)(width/2 -  cur_pix_X), cur_pix_Y-1);
                        SDL_RenderPresent(renderer);
						
					   SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y,
                                                     cur_pix_X, cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X+1, last_pix_Y,
                                                     cur_pix_X+1, cur_pix_Y);
                        SDL_RenderDrawLine(renderer, last_pix_X, last_pix_Y-1,
                                                     cur_pix_X, cur_pix_Y-1);
                        SDL_RenderPresent(renderer);
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
                    leftMouseButtonDown = true;
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
					SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
					printf("ingrese el nombre con el que se guardara el dibujo \n");
					scanf("%s",nombre);
					SDL_SaveBMP(sshot, nombre);
					SDL_FreeSurface(sshot);
                    // Color to black, and refresh to erase all the window
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    // Keep drawing in white afterwards
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    rightMouseButtonDown = true;
                    last_pix_X = -1;
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "The creation was saved",
                         "",
                         NULL);

                }
                break;
        }
                    leftMouseButtonDown = true;
                if (event.button.button == SDL_BUTTON_RIGHT)
                {
					SDL_Surface *sshot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
					SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
					printf("ingrese el nombre con el que se guardara el dibujo \n");
					scanf("%s",nombre);
					SDL_SaveBMP(sshot, nombre);
					SDL_FreeSurface(sshot);
                    // Color to black, and refresh to erase all the window
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    // Keep drawing in white afterwards
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    rightMouseButtonDown = true;
                    last_pix_X = -1;
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "The creation was saved",
                         "",
                         NULL);

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
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION ,
                         "Instrucciones",
                         "Con TAB se cambiara de color\nCon B se podra emplear el Borrador\nCon M se activara la funcion espejo y con N se volvera a la normalidad\nCon el boton izquierdo se dara por concluido y guardado el dibujo",
                         NULL);


    canvas win(width, height);
    win.create_window();

    win._draw();

    return 0;
}
