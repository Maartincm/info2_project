struct Image
{
    SDL_Texture * texture;
    SDL_Rect size;
    int width;
    int height;
    bool active;
};

class canvas
{
    private:
        char name[256];
        int last_pix_X;
        int last_pix_Y;
        int cur_pix_X;
        int cur_pix_Y;
        int width;
        int height;
        int red;
        int green;
        int blue;
        int eraser;
        const Uint8 * state;
        bool leftMouseButtonDown;
        bool rightMouseButtonDown;
        SDL_bool done = SDL_FALSE;
        SDL_Window * window;
        SDL_Surface * surface;
        SDL_Texture * texture;
        SDL_Renderer * renderer;
        SDL_Cursor * cursor;
        SDL_Event event;
        struct Image mirror;
        struct Image greentick;
        struct Image redcross;

    public:
        canvas(int w, int h);
        ~canvas();
        void create_window();
        void draw_mirror();
        void draw_green_tick();
        void draw_red_cross();
        void draw_classic_line();
        void draw_mirror_line();
        void check_mirror_state();
        void _draw();
};
