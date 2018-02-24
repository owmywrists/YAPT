class Material;

inline v3f sample_texture(const sf::Image &img, float u, float v)
{
    int width = img.getSize().x;
    int height = img.getSize().y;
    sf::Color temp = img.getPixel(int(u*width) % width, int(v*height) % height);
    return v3f(temp.r, temp.g, temp.b)/255.0;
}

inline v3f make_orthonormal_basis(v3f dir, v3f &normal)
{
    v3f axis[3];
    axis[2] = unit(normal);
    v3f a;
    if (fabs(axis[2].x) > 0.9) 
        a = v3f(0,1,0);
    else
        a = v3f(1,0,0);
    axis[1] = unit(axis[2].cross(a));
    axis[0] = axis[2].cross(axis[1]);
    return unit(axis[0]*dir.x + axis[1]*dir.y + axis[2]*dir.z);
}

struct HitInfo
{
    float t;
    v3f normal;
    std::shared_ptr<Material> mat;
    v3f colour;
    float costheta;
    float u, v;
};

class Material
{
    public:
    virtual bool BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const = 0;
    virtual v3f colour(){return v3f();}
};

class Emissive : public Material
{
    public:
    Emissive(v3f c) : m_colour(c){}
    bool BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const;
    v3f colour(){ return m_colour; }
    
    private:
    v3f m_colour;
};

class Lambertian : public Material
{
    public:
    Lambertian(sf::Image t):texture(t) {}
    bool BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const;
    
    private:
    sf::Image texture;
};

class Mirror : public Material
{
    public:
    Mirror(v3f c, float glossiness = 0.0f): m_colour(c), glossiness(glossiness){}
    bool BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const;
    
    private:
    v3f m_colour;
    float glossiness;
};

class Mix : public Material
{
    public:
    Mix(std::shared_ptr<Material> mat1, std::shared_ptr<Material> mat2, float mix) :mat1(mat1), mat2(mat2), mix(mix) {}
    bool BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const;
    private:
    std::shared_ptr<Material> mat1, mat2;
    float mix;
};

class Glass: public Material
{
    public:
    Glass(v3f c, float glossiness = 0.0f): m_colour(c), glossiness(glossiness){}
    bool BRDF(Ray &ray, HitInfo &hit, v3f &attenuation, Ray &new_ray) const;
    
    private:
    v3f m_colour;
    float glossiness;
};