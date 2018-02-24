#include "engine.h"

#define RAY_PROB 0.5
#define NUM_BOUNCES 50

Engine::~Engine() {
    delete temp_img;
    delete m_screen;
}


void Engine::restart()
{
    m_screen->reset();
}

void Engine::render()
{
    HitInfo hit;
    sf::Time start(clock.getElapsedTime());
    
    Ray persp, ortho;
    v3f colour = v3f();
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
                    ortho = Ray(v3f(x, y, 0), v3f(0, 0, -1));
                    colour = v3f(0.0, 0.0, 0.0);
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
    m_screen->sample++;
    if (m_screen->should_save) m_screen->save_frame(temp_img, scene->info.filename);
    if (m_screen->should_reset) restart();
}

v3f Engine::hdri_sky(Ray &ray)
{
    v3f ud = unit(ray.direction);
    float t = 0.5 * (ud.y + 1.0);
    float u_ = 0.5 + atan2(ud.z, ud.x) / (2 * M_PI);
    float v_ = 0.5 - asin(ud.y) / M_PI;
    
    return(sample_texture(scene->hdri, u_, v_));
    
}

v3f Engine::trace(Ray &ray, HitInfo &hit, int depth)
{
    ray.tmin = 1e5;
    ray_type next_type = SCATTER;
    HitInfo previous_hit = hit;
    int l = rand() % scene->lights.size();
    Ray next_light_ray;
    if (scene->mesh.intersect(ray, hit))
    {
        Ray new_ray;
        v3f light_emitted(hit.mat->colour());
        v3f colour(0.0f);
        if (depth < NUM_BOUNCES && hit.mat->BRDF(ray, hit, colour, new_ray))
        {
            next_light_ray = scene->lights[l]->get_light_ray(ray.get_hit(hit.t), hit.normal);
            
            if (drand48() < RAY_PROB)
            {
                next_type = SHADOW;
                if(unit(next_light_ray.direction).dot(hit.normal)<0.0)return previous_hit.colour;
                new_ray = next_light_ray;
            }
            if (ray.type == SHADOW) colour = previous_hit.colour;
            new_ray.type = next_type;
            if (depth < 1) 
                return light_emitted + colour*trace(new_ray, hit, depth + 1)*hit.costheta*2.0;
            else //clamps indirect (any ray that bounces)
                return light_emitted + colour*minf3(trace(new_ray, hit, depth + 1)*hit.costheta*2.0, 1.1);
        }
        else
            return light_emitted;
    }
    else
    {
        if(ray.type == SHADOW)
            return scene->lights[l]->get_contribution(ray, previous_hit);
        else
            return v3f();
    }
    
}