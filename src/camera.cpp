#include "camera.h"

float3 random_in_unit_disk() {
    float3 p;
    do {
        p = float3(drand48(), drand48(), 0)*2.0 - float3(1, 1, 0);
    } while (p.dot(p) >= 1.0);
    return p;
}

Ray Camera::getRay(float x, float y)
{
    float3 rd = random_in_unit_disk()*m_aperture;
    float3 offset = u * rd.x + v * rd.y;
    return Ray(origin + offset, l_l_c + horizontal*x + vertical*y - origin - offset);
}
