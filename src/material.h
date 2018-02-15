class Material;

inline float3 sample_texture(const sf::Image &img, float u, float v)
{
    int width = img.getSize().x;
    int height = img.getSize().y;
    sf::Color temp = img.getPixel(int(u*width) % width, int(v*height) % height);
    return float3(temp.r, temp.g, temp.b)/255.0;
}

struct HitInfo
{
    float t;
    float3 normal;
    std::shared_ptr<Material> mat;
    float3 colour;
    float u, v;
};

class Material
{
    public:
    virtual bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const = 0;
    virtual float3 colour(){return float3();}
};

class Emissive : public Material
{
    public:
    Emissive(float3 c) : m_colour(c){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;
    float3 colour() const { return m_colour; }
    
    private:
    float3 m_colour;
};

class Lambertian : public Material
{
    public:
    Lambertian(sf::Image t):texture(t) {}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;
    
    private:
    sf::Image texture;
};

class Mirror : public Material
{
    public:
    Mirror(float3 c, float glossiness = 0.0f): m_colour(c), glossiness(glossiness){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;
    
    private:
    float3 m_colour;
    float glossiness;
};

class Mix : public Material
{
    public:
    Mix(std::shared_ptr<Material> mat1, std::shared_ptr<Material> mat2, float mix) :mat1(mat1), mat2(mat2), mix(mix) {}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;
    private:
    std::shared_ptr<Material> mat1, mat2;
    float mix;
};

class Glass: public Material
{
    public:
    Glass(float3 c, float glossiness = 0.0f): m_colour(c), glossiness(glossiness){}
    bool scatter(Ray &ray, HitInfo &hit, float3 &attenuation, Ray &new_ray) const;
    
    private:
    float3 m_colour;
    float glossiness;
};