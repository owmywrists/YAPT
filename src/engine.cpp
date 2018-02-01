#include "engine.h"

Engine::~Engine() {
    
}


void Engine::restart()
{
    float *temp_col = m_screen->getColour();
    float3 rand_num = float3(temp_col[0], temp_col[1], temp_col[2]);
    std::cout << rand_num << std::endl;
    std::vector<std::shared_ptr<Material>> mats;
    //mats.push_back(std::make_shared<Lambertian>(rand_num));
    //mats.push_back(std::make_shared<Lambertian>(float3(1.0, 0.0, 0.0)));
    
    //for (int face = 0; face < mesh.size(); face++)
    //m_data[face]->setMaterial(mats[0]);
    m_screen->reset();
    std::string obj_loc = "../../res/objs/";
    std::string hdri_loc = "../../res/hdris/";
    std::string obj_open = m_screen->obj_to_open;
    std::string hdri_load = m_screen->hdri_to_load;
    mesh.load(obj_loc + obj_open);
    hdri.loadFromFile(hdri_loc + hdri_load);
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
                    colour = colour + trace(persp, hit, 0);
                    
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
float3 Engine::trace(Ray &ray, HitInfo &hit, int depth)
{
    ray.tmin = 1e5;
    if (mesh.intersect(ray, hit))
    {
        Ray new_ray;
        float3 contribution(1.0, 1.0, 1.0);
        float3 light_emitted(hit.mat->colour());
        if (depth < 10 && hit.mat->scatter(ray, hit, contribution, new_ray))
        {
            return light_emitted + contribution * trace(new_ray, hit, depth + 1);
        }
        else
        {
            return light_emitted; 
        }
    }
    else //must be sky
    {
        float3 ud = unit(ray.getDirection());
        float t = 0.5 * (ud.y + 1.0);
        float u_ = 0.5 + atan2(ud.z, ud.x) / (2 * M_PI);
        float v_ = 0.5 - asin(ud.y) / M_PI;
        float3 sb = sample_texture(hdri, u_, v_)/255.0;
        
        return sb;
    }
}
