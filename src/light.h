class Light
{
    public:
    virtual Ray get_light_ray(float3 hitpos, float3 normal)const = 0;
    virtual float3 get_contribution(Ray &ray, HitInfo &hit) = 0;
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
    float3 get_contribution(Ray &ray, HitInfo &hit)
    {
        
        float length =  m_direction.length()*hit.normal.length();
        float costheta = fmax(m_direction.dot(hit.normal)/length, 0.1);
        return m_colour*m_power*costheta;
    }
    void update(float3 p){ m_direction = p;}
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
        return Ray(hitpos + normal*(1e-5), unit(pos-hitpos + sample*m_size));
    }
    float3 get_contribution(Ray &ray, HitInfo &hit)
    {
        float3 hit_loc = ray.origin;
        float dist2 = (pos - hit_loc).sqrd_length();
        float illuminance = m_power/(dist2*4*M_PI);
        float length = (pos-hit_loc).length()*hit.normal.length();
        float costheta = (pos-hit_loc).dot(hit.normal)/length;
        costheta = fmax(costheta, 0.0);
        float3 col = m_colour*illuminance*costheta; 
        return float3(fmax(col.x, 0.0), fmax(col.y,0.0), fmax(col.z, 0.0));
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