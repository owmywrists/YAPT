
class Scene{
    public:
    Scene()
    {
        mesh.load("../../res/objs/Hamburger.obj",
                  "../../res/tex/Hamburger.png");
        mesh.generate_kdtree();
        hdri.loadFromFile("../../res/hdris/road.jpg");
        lights.push_back(new Point(float3(3.0f, 0.5f, -4.0f), float3(0.2f, 0.4f, 0.4f), 2.5f, 0.1f));
    }
    Mesh mesh;
    std::vector<Light*> lights;
    sf::Image hdri;
};