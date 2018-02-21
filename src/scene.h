
class Scene{
    public:
    Scene(std::string filename)
    {
        mesh.load("../../res/objs/"+ filename,
                  "../../res/tex/grey.png");
        mesh.generate_kdtree();
        hdri.loadFromFile("../../res/hdris/road.jpg");
        lights.push_back(new Point(float3(2.0f, 3.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), 30.0f, 0.1f));
    }
    Mesh mesh;
    std::vector<Light*> lights;
    sf::Image hdri;
};