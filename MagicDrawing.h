struct Image
{
    SDL_Texture * texture;
    SDL_Rect size;
    SDL_RWops * rwop;
    SDL_Surface * surface;
    SDL_PixelFormat * pixelFormat;
    Uint32 * pixels;
    Uint32 pix;
    int width;
    int height;
    bool active;
};

class canvas
{
    private:
        char name[256];
        time_t rawtime;
        struct tm * timeinfo;
        char date[128];
        int last_pix_X;
        int last_pix_Y;
        int cur_pix_X;
        int cur_pix_Y;
        int width;
        int height;
        Uint8 red, green, blue, alpha;
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
        struct Image colorpicker;
        struct Image eraser;
        struct Image rainbow;

    public:
        canvas(int w, int h);
        ~canvas();
        void create_window();
        void rainbow_progress();
        void draw_rainbow();
        void draw_eraser();
        void draw_colorpicker();
        void draw_mirror();
        void draw_green_tick(char *);
        void draw_red_cross(char *);
        void draw_classic_line();
        void draw_mirror_line();
        void clean_window();
        void check_mirror_state();
        void check_rainbow_state();
        void get_color();
        void _draw();
};
