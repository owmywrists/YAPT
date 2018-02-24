class Light
{
    public:
    virtual Ray get_light_ray(v3f hitpos, v3f normal)const = 0;
    virtual v3f get_contribution(Ray &ray, HitInfo &hit) = 0;
    virtual void update(v3f p){};
};

class Directional : public Light
{
    public:
    Directional(){};
    Directional(v3f direction, v3f colour, float power, float size): m_direction(direction),m_colour(colour), m_power(power), m_size(size){}
    
    Ray get_light_ray(v3f hitpos, v3f normal)const
    {
        v3f sample = v3f(drand48(), drand48(), drand48());
        return Ray(hitpos + normal*(1e-5), unit(m_direction + sample*m_size));
    }
    v3f get_contribution(Ray &ray, HitInfo &hit)
    {
        
        float length =  m_direction.length()*hit.normal.length();
        float costheta = fmax(m_direction.dot(hit.normal)/length, 0.1);
        return m_colour*m_power*costheta;
    }
    void update(v3f p){ m_direction = p;}
    private:
    v3f m_colour;
    float m_power, m_size;
    v3f m_direction;
};

class Point : public Light
{
    public:
    Point(v3f p, v3f colour, float power, float size):pos(p),m_colour(colour),m_power(power),m_size(size){}
    
    Ray get_light_ray(v3f hitpos, v3f normal)const
    {
        v3f sample = v3f(drand48(), drand48(), drand48());
        return Ray(hitpos + normal*(1e-5), unit(pos-hitpos + sample*m_size));
    }
    v3f get_contribution(Ray &ray, HitInfo &hit)
    {
        v3f hit_loc = ray.origin;
        float dist2 = (pos - hit_loc).sqrd_length();
        float illuminance = m_power/(dist2*4*M_PI);
        float length = (pos-hit_loc).length()*hit.normal.length();
        float costheta = (pos-hit_loc).dot(hit.normal)/length;
        costheta = fmax(costheta, 0.0);
        v3f col = m_colour*illuminance*costheta; 
        return v3f(fmax(col.x, 0.0), fmax(col.y,0.0), fmax(col.z, 0.0));
    }
    void update(v3f p)
    {
        pos = p;
    }
    v3f pos;
    private:
    v3f m_colour;
    float m_power;
    float m_size;
};