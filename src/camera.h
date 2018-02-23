
float3 random_in_unit_disk();

class Camera
{
    public:
    Camera(uint16_t width, uint16_t height, float3 pos, float3 look, float3 up, float aperture, float focal_length, float fov) :m_aperture(aperture), m_width(width), m_height(height), m_fov(fov), lookat(look)
    {
        
        m_aperture /= 2.0;
        origin = pos;
        float theta = m_fov * M_PI / 180;
        float half_height = tanf(theta / 2.0);
        float aspect = float (m_width)/ float(m_height);
        float half_width = aspect * half_height;
        eye= unit(origin - lookat);
        u = unit(float3(0,1,0).cross(eye));
        v = eye.cross(u);
        bl= origin - u*half_width - v*half_height- eye;
        horizontal = u*2 * half_width;
        vertical = v*2 * half_height;
        
        
    };
    
    Ray primary_ray(float x, float y);
    
    float3 bl;
    float3 horizontal;
    float3 origin;
    float3 vertical;
    float3 u, v, eye;
    float3 lookat;
    private:
    
    float m_aperture;
    
    int m_width;
    int m_height;
    float m_fov;
};
