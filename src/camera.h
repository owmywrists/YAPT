
float3 random_in_unit_disk();

class Camera
{
    public:
    Camera(uint16_t width, uint16_t height, float3 pos, float3 lookat, float3 up, float aperture, float focal_length, float fov) :m_aperture(aperture), m_width(width), m_height(height), m_fov(fov){
        m_aperture /= 2.0;
        float theta = fov * M_PI / 360;
        float half_height = tan(theta / 2.0);
        float aspect = float (width)/ float(height);
        float half_width = aspect * half_height;
        origin = pos;
        w = unit(pos - lookat);
        u = unit(up.cross(w));
        v = w.cross(u);
        l_l_c = origin - u*half_width * focal_length - v*half_height * focal_length - w*focal_length;
        horizontal = u*2 * half_width*focal_length;
        vertical = v*2 * half_height*focal_length;
        
    };
    
    Ray getRay(float x, float y);
    
    private:
    float3 l_l_c;
    float3 horizontal;
    float3 origin;
    float3 vertical;
    float3 u, v, w;
    float m_aperture;
    
    int m_width;
    int m_height;
    float m_fov;
};
