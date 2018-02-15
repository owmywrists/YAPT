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
    for (int x = 0; x < m_screen->getWidth(); x++)
    {
        for (int y = 0; y < m_screen->getHeight(); y++)
        {
            float3 col = image[x + m_screen->getWidth() * y];
            m_screen->setPixel(x, (m_screen->getHeight() - y), col);
        }
    }
}
void Engine::render()
{
    HitInfo hit;
    std::vector<float3> temp_img;
    temp_img.resize(m_screen->getWidth() * m_screen->getHeight());
    sf::Time start(clock.getElapsedTime());
    
    Ray persp, ortho;
    float3 colour = float3();
    float u, v;
    const int tile_size = 80;
#pragma omp parallel for schedule(dynamic, 1) private(hit, persp, ortho, colour, u, v) collapse(2)
    for (int tx = 0; tx < m_screen->getWidth() / tile_size; tx++) 
    {
        for (int ty = 0; ty < m_screen->getHeight() / tile_size; ty++)
        {
            for (int x = 0; x < tile_size; x++)
            {
                for (int y = 0; y < tile_size; y++)
                {
                    ortho = Ray(float3(x, y, 0), float3(0, 0, -1));
                    colour = float3(0.0, 0.0, 0.0);
                    u = float(x + tx*tile_size + drand48()) / m_screen->getWidth();
                    v = float(y + ty*tile_size + drand48()) / m_screen->getHeight();
                    persp = m_cam.getRay(u, v);
                    colour = trace(persp, hit, 0);
                    
                    temp_img[x + tx*tile_size + (ty*tile_size + y) * m_screen->getWidth()] = colour;
                }
            }
        }
    }
    sf::Time end = clock.getElapsedTime();
    std::cout << "sample " << m_screen->sample << " took: " << (end - start).asSeconds() << " seconds" << std::endl;
    m_screen->loadImage(temp_img);
    m_screen->sample++;
    if (m_screen->getState())
        restart();
}

float3 Engine::hdri_sky(Ray &ray)
{
    float3 ud = unit(ray.getDirection());
    float t = 0.5 * (ud.y + 1.0);
    float u_ = 0.5 + atan2(ud.z, ud.x) / (2 * M_PI);
    float v_ = 0.5 - asin(ud.y) / M_PI;
    
    return(sample_texture(scene->hdri, u_, v_));
    
}

float3 Engine::trace(Ray &ray, HitInfo &hit, int depth, ray_type type)
{
    ray.tmin = 1e5;
    ray_type next_type = SCATTER;
    HitInfo previous_hit = hit;
    int l = rand() % scene->lights.size();
    
    if (scene->mesh.intersect(ray, hit))
    {
        Ray new_ray;
        float3 light_emitted(hit.mat->colour());
        float3 contribution(0.0f);
        if (depth < 50 && hit.mat->scatter(ray, hit, contribution, new_ray))
        {
            if (drand48() < 0.5)
            {
                next_type = SHADOW;
                Ray next_light_ray = scene->lights[l]->get_light_ray(ray.getHit(hit.t), hit.normal);
                if (unit(next_light_ray.getDirection()).dot(hit.normal)<0.0) return light_emitted;
                new_ray = next_light_ray;
                
            }
            if(type == SHADOW)
                contribution = previous_hit.colour;
            
            return light_emitted + contribution * trace(new_ray, hit, depth + 1,next_type);
        }
        else
        {
            return light_emitted; 
        }
    }
    else
    {
        if (type == SCATTER){
            return hdri_sky(ray)*2.0;
            
        }
        else
        {
            Ray prev_light_ray = scene->lights[l]->get_light_ray(ray.getHit(previous_hit.t), previous_hit.normal);
            
            return scene->lights[l]->get_contribution(prev_light_ray, previous_hit)*scene->lights.size();
        }
        
    }
}