
class Engine
{
    public:
    Engine(Camera *cam, Screen *screen,Scene* s) : m_cam(cam), m_screen(screen),
    scene(s)
    { 
        clock.restart();
        tile_size = 20; //default size
        temp_img = new float3[m_screen->width*m_screen->height];
    }
    ~Engine();
    void render();
    void restart();
    Scene* scene;
    unsigned int tile_size;
    private:
    Camera* m_cam;
    float3* temp_img;
    sf::Clock clock;
    float3 trace(Ray &ray,HitInfo &hit, int depth);
    float3 hdri_sky(Ray &ray);
    Screen* m_screen;
};

