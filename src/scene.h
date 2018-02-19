
class Scene{
    public:
    Scene()
    {
        mesh.load("../../res/objs/teapot.obj",
                  "../../res/tex/grey.png");
        mesh.generate_kdtree();
        hdri.loadFromFile("../../res/hdris/road.jpg");
        lights.push_back(new Point(float3(2.0f, 3.0f, 0.0f), float3(0.5f, 0.7f, 1.0f), 10.5f, 0.5f));
        lights.push_back(new Point(float3(-2.0f, 3.0f, 0.0f), float3(1.0f, 0.7f, 0.5f), 10.5f, 0.5f));
    }
    Mesh mesh;
    std::vector<Light*> lights;
    sf::Image hdri;
};