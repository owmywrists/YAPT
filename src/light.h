class Light
{
    public:
    virtual Ray get_light_ray(float3 hitpos, float3 normal)const = 0;
    virtual float3 get_contribution(Ray &ray, HitInfo &hit)const = 0;
    virtual void update(float3 p){};
};

class Directional : public Light
{
    public:
    Directional(){};
    Directional(float3 direction, float3 colour, float power, float size): m_direction(direction),m_colour(colour), m_power(power), m_size(size){}
    
    Ray get_light_ray(float3 hitpos, float3 normal)const
    {
        float3 sample = float3(drand48(), drand48(), drand48());
        return Ray(hitpos + normal*(1e-5), unit(m_direction + sample*m_size));
    }
    float3 get_contribution(Ray &ray, HitInfo &hit)const
    {
        float length = ray.getDirection().length()*hit.normal.length();
        float costheta = fabs(ray.getDirection().dot(hit.normal))/length;
        return m_colour*m_power*costheta;
    }
    private:
    float3 m_colour;
    float m_power, m_size;
    float3 m_direction;
};

class Point : public Light
{
    public:
    Point(float3 p, float3 colour, float power, float size):pos(p),m_colour(colour),m_power(power),m_size(size){}
    
    Ray get_light_ray(float3 hitpos, float3 normal)const
    {
        float3 sample = float3(drand48(), drand48(), drand48());
        return Ray(hitpos + normal*(1e-5), unit(pos- hitpos + sample*m_size));
    }
    
    float3 get_contribution(Ray &ray, HitInfo &hit)const
    {
        float3 hit_loc = ray.getHit(hit.t);
        float dist2 = (pos - hit_loc).sqrd_length();
        float length = ray.getDirection().length()*hit.normal.length();
        float costheta = fabs(ray.getDirection().dot(hit.normal));
        float invr2 = 1.0/(dist2);
        
        return unit(m_colour*invr2)*costheta*m_power;
    }
    void update(float3 p)
    {
        pos = p;
    }
    float3 pos;
    private:
    float3 m_colour;
    float m_power;
    float m_size;
};