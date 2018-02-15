enum ray_type
{
    SCATTER,
    SHADOW
};


class Engine
{
    public:
    Engine(Camera cam, Screen *screen, std::shared_ptr<Scene> s) : m_cam(cam), m_screen(screen),
    scene(s)
    { 
        clock.restart();
        scene->mesh.generate_kdtree();
        scene->mesh.calculate_normals();
        
    }
    ~Engine();
    void render();
    void restart();
    std::shared_ptr<Scene> scene;
    private:
    Camera m_cam;
    sf::Clock clock;
    float3 trace(Ray &ray,HitInfo &hit, int depth, ray_type type=SCATTER);
    float3 hdri_sky(Ray &ray);
    void loadBuffer(std::vector<float3> image);
    Screen *m_screen;
};
