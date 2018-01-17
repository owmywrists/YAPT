#include "engine.h"

Engine::~Engine() {

}
void Engine::loadObjAsScene(std::string filename)
{
    Obj m(filename);
    auto temp = m.getScene();
    m_data = temp;

	auto m1 = std::make_shared<Lambertian>(float3(0.0, 1.0, 0.0));
	auto m2 = std::make_shared<Mirror>(float3(1.0, 1.0, 1.0), 0.0);

	m_data.push_back(new Sphere(float3(-2.0, 0.0, -1.0), 0.7f, std::make_shared<Mix>(m1, m2, 1.9f)));
    node = KDNode().build(m_data, 0);

	m_screen->debug_text.setString(sf::String("triangles: " + std::to_string(m_data.size())));
	m_screen->debug_text.setFont(m_screen->Font);
	m_screen->debug_text.setColor(sf::Color::White);
}

void Engine::restart()
{
	//m_cam.move(float3(sin(10), 0, cos(10) + 3.0));
    float *temp_col = m_screen->getColour();
    float3 rand_num = float3(temp_col[0], temp_col[1], temp_col[2]);
    std::cout << rand_num << std::endl;
	std::vector<std::shared_ptr<Material>> mats;
	mats.push_back(std::make_shared<Lambertian>(rand_num));
	mats.push_back(std::make_shared<Lambertian>(float3(1.0, 0.0, 0.0)));

    for (int face = 0; face < m_data.size(); face++)
        m_data[face]->setMaterial(mats[0]);
    m_screen->reset();
}

void Engine::loadBuffer(std::vector<float3> image)
{
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
	sf::Time start = clock.getElapsedTime();

	Ray persp, ortho;
	float3 colour = float3();
	float u, v;
#pragma omp parallel for schedule(dynamic, 1) private(hit, persp, ortho, colour, u, v)
    for (int x = 0; x < m_screen->getWidth(); x++)
    {
        for (int y = 0; y < m_screen->getHeight(); y++)
        {
            ortho = Ray(float3(x, y, 0), float3(0, 0, -1));
            colour = float3(0.0, 0.0, 0.0);
            u = float(x + drand48())/m_screen->getWidth();
            v = float(y + drand48())/m_screen->getHeight();
            persp = m_cam.getRay(u, v);
            colour = colour + trace(persp, hit, 0);
            temp_img[x + y * m_screen->getWidth()] = colour;
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
    if (node->intersect(node, ray, hit))
    {
        Ray new_ray;
        float3 col(1.0, 1.0, 1.0);
        float3 light = hit.mat->emitted();
        if (depth < 10 && hit.mat->scatter(ray, hit, col, new_ray))
        {
            return light + col * trace(new_ray, hit, depth + 1);
        }
        else
        {
            return light;
        }
    }
    else
    {
        float3 ud = unit(ray.getDirection());
        float t = 0.5 * (ud.y + 1.0);
		float u_ = 0.5 + atan2(ud.z, ud.x) / (2 * M_PI);
		float v_ = 0.5 - asin(ud.y) / M_PI;
		float3 sb = sample_skybox(hdri, u_, v_)/255.0;

		return sb;
    }
}
