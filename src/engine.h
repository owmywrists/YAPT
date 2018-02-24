
class Engine
{
    public:
    Engine(Camera *cam, Screen *screen,Scene* s) : m_cam(cam), m_screen(screen),
    scene(s)
    { 
        clock.restart();
        tile_size = 20; //default size
        temp_img = new v3f[m_screen->width*m_screen->height];
    }
    ~Engine();
    void render();
    void restart();
    Scene* scene;
    unsigned int tile_size;
    private:
    Camera* m_cam;
    v3f* temp_img;
    sf::Clock clock;
    v3f trace(Ray &ray,HitInfo &hit, int depth);
    v3f hdri_sky(Ray &ray);
    Screen* m_screen;
};

