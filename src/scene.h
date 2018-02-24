struct SceneSettings
{
    std::string filename;
    std::string texture;
    std::string hdri;
    std::string material;
};
class Scene{
    public:
    Scene(SceneSettings settings)
    {
        info = settings;
        mesh.load("../../res/objs/"+ settings.filename,
                  "../../res/tex/" + settings.texture);
        mesh.generate_kdtree();
        hdri.loadFromFile("../../res/hdris/"+settings.hdri);
        lights.push_back(new Point(v3f(0.0f, 2.3f, 0.0f), v3f(1.0f, 0.4f, 0.15f), 100.0f, 1.0f));
    }
    Mesh mesh;
    SceneSettings info;
    std::vector<Light*> lights;
    sf::Image hdri;
};