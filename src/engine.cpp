#include "engine.h"

Engine::~Engine() {
    
}


void Engine::restart()
{
    m_screen->reset();
}

void Engine::loadBuffer(std::vector<float3> image)
{
#pragma omp parallel for
    for (int x = 0; x < m_screen->width; x++)
    {
        for (int y = 0; y < m_screen->height; y++)
        {
            float3 col = image[x + m_screen->width * y];
            m_screen->setPixel(x, (m_screen->height - y), col);
        }
    }
}
void Engine::render()
{
    HitInfo hit;
    float3* temp_img = new float3[m_screen->width*m_screen->height];
    sf::Time start(clock.getElapsedTime());
    
    Ray persp, ortho;
    float3 colour = float3();
    float u, v;
#pragma omp parallel for schedule(dynamic, 1) private(hit, persp, ortho, colour, u, v) collapse(2)
    
    for (int ty = m_screen->height/tile_size-1; ty >= 0; ty--)
    {
        for (int tx = 0; tx < m_screen->width / tile_size; tx++) 
        {
            
            m_screen->begin_tile(tx*tile_size, ty*tile_size, tile_size);
            for (int x = 0; x < tile_size; x++)
            {
                for (int y = 0; y < tile_size; y++)
                {
                    ortho = Ray(float3(x, y, 0), float3(0, 0, -1));
                    colour = float3(0.0, 0.0, 0.0);
                    u = float(x + tx*tile_size + drand48()) / m_screen->width;
                    v = float(y + ty*tile_size + drand48()) / m_screen->height;
                    persp = m_cam->primary_ray(u, v);
                    colour = trace(persp, hit, 0);
                    temp_img[x + tx*tile_size + (ty*tile_size + y) * m_screen->width] = colour;
                }
            }
            m_screen->set_tile(tx*tile_size, ty*tile_size,tile_size, temp_img);
        }
    }
    sf::Time end = clock.getElapsedTime();
    std::cout << "sample " << m_screen->sample << " took: " << (end - start).asSeconds() << " seconds" << std::endl;
    delete temp_img;
    m_screen->sample++;
    if (m_screen->should_reset) restart();
}

float3 Engine::hdri_sky(Ray &ray)
{
    float3 ud = unit(ray.getDirection());
    float t = 0.5 * (ud.y + 1.0);
    float u_ = 0.5 + atan2(ud.z, ud.x) / (2 * M_PI);
    float v_ = 0.5 - asin(ud.y) / M_PI;
    
    return(sample_texture(scene->hdri, u_, v_));
    
}

float3 Engine::trace(Ray &ray, HitInfo &hit, int depth)
{
    ray.tmin = 1e5;
    ray_type next_type = SCATTER;
    HitInfo previous_hit = hit;
    int l = rand() % scene->lights.size();
    Ray next_light_ray;
    if (scene->mesh.intersect(ray, hit))
    {
        Ray new_ray;
        float3 light_emitted(hit.mat->colour());
        float3 colour(0.0f);
        if (depth < 50 && hit.mat->BSDF(ray, hit, colour, new_ray))
        {
            if (drand48() < 0.5) //magic number is probability of ray type 
            {
                next_type = SHADOW;
                next_light_ray = scene->lights[l]->get_light_ray(ray.getHit(hit.t), hit.normal);
                if (unit(next_light_ray.getDirection()).dot(hit.normal)<0.0) return light_emitted;
                new_ray = next_light_ray;
            }
            if (ray.type == SHADOW) colour = previous_hit.colour;
            new_ray.type = next_type;
            return light_emitted + colour*trace(new_ray, hit, depth + 1);
        }
        else
            return light_emitted; 
        
    }
    else
    {
        if(ray.type == SHADOW) return scene->lights[l]->get_contribution(ray, previous_hit);
        else
            return float3();
    }
    
}