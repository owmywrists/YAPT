#include "camera.h"

Ray Camera::getRay(float x, float y)
{

    float u = x / float(m_width);
    float v = y / float(m_height);

    float theta = (float(m_fov) * M_PI) / float(180.0);
    float half_height = tan(theta / 2.0);
    float aspect = float(m_width) / float(m_height);
    float half_width = aspect * half_height;
    float3 l_l_c = float3(half_width * (-1.0), half_height * (-1.0), -1.0);
    float3 horizontal = float3(2.0 * half_width, 0.0, 0.0);

    float3 vertical = float3(0.0, float(2.0 * half_height), 0.0);
    float3 origin = float3(0.0, 0.0, 0.0);
    float3 direction = l_l_c + horizontal * u + vertical * v - origin;

    return Ray(origin, direction);
}
