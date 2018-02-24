#include "camera.h"

v3f random_in_unit_disk() {
    v3f p;
    do {
        p = v3f(drand48(), drand48(), 0)*2.0 - v3f(1, 1, 0);
    } while (p.dot(p) >= 1.0);
    return p;
}

Ray Camera::primary_ray(float x, float y)
{
    
    v3f rd = random_in_unit_disk()*m_aperture;
    v3f offset = u * rd.x + v * rd.y;
    return Ray(origin, bl + horizontal*x + vertical*y - origin);
}
