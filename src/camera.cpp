#include "camera.h"

float3 random_in_unit_disk() {
    float3 p;
    do {
        p = float3(drand48(), drand48(), 0)*2.0 - float3(1, 1, 0);
    } while (p.dot(p) >= 1.0);
    return p;
}

Ray Camera::primary_ray(float x, float y)
{
    
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
    
    float3 rd = random_in_unit_disk()*m_aperture;
    float3 offset = u * rd.x + v * rd.y;
    return Ray(origin, bl + horizontal*x + vertical*y - origin);
}
