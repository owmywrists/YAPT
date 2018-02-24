#include "kd_tree.h"

KDNode *KDNode::build(std::vector<Surface *> &surfaces, int depth)
{
    KDNode *node = new KDNode();
    node->leaf = false;
    node->surface = std::vector<Surface *>();
    node->left = NULL;
    node->right = NULL;
    node->aabb = AABB();
    
    if (surfaces.size() == 0)
        return node;
    
    if (depth > 25 || surfaces.size() <= 10)
    {
        node->surface = surfaces;
        node->leaf = true;
        node->aabb = surfaces[0]->get_bounding_box();
        
        for (int i = 1; i < surfaces.size(); i++){
            node->aabb.expand(surfaces[i]->get_bounding_box());
        }
        node->left = new KDNode();
        node->right = new KDNode();
        node->left->surface = std::vector<Surface *>();
        node->right->surface = std::vector<Surface *>();
        return node;
    }
    node->aabb = surfaces[0]->get_bounding_box();
    v3f midpoint = v3f();
    float s_rec = 1.0/float(surfaces.size());
    for (int i =1;  i < surfaces.size(); i++)
    {
        node->aabb.expand(surfaces[i]->get_bounding_box());
        midpoint = midpoint + (surfaces[i]->get_midpoint() * s_rec);
    }
    
    std::vector<Surface *> left_surfaces;
    std::vector<Surface *> right_surfaces;
    int axis = node->aabb.get_longest_axis();
    for (int i = 0; i < surfaces.size(); i++)
    {
        switch (axis)
        {
            case 0:
            midpoint.x >= surfaces[i]->get_midpoint().x ? right_surfaces.push_back(surfaces[i]) : left_surfaces.push_back(surfaces[i]);
            break;
            case 1:
            midpoint.y >= surfaces[i]->get_midpoint().y ? right_surfaces.push_back(surfaces[i]) : left_surfaces.push_back(surfaces[i]);
            break;
            case 2:
            midpoint.z >= surfaces[i]->get_midpoint().z ? right_surfaces.push_back(surfaces[i]) : left_surfaces.push_back(surfaces[i]);
            break;
        }
    }
    
    if (surfaces.size() == left_surfaces.size() || surfaces.size() == right_surfaces.size())
    {
        node->surface = surfaces;
        node->leaf = true;
        node->aabb = surfaces[0]->get_bounding_box();
        
        for (int i = 1; i < surfaces.size(); i++)
        {
            node->aabb.expand(surfaces[i]->get_bounding_box());
        }
        
        node->left = new KDNode();
        node->right = new KDNode();
        node->left->surface = std::vector<Surface *>();
        node->right->surface = std::vector<Surface *>();
        
        return node;
    }
    
    node->left = build(left_surfaces, depth + 1);
    node->right = build(right_surfaces, depth + 1);
    
    return node;
}

bool KDNode::closestIntersection(Ray &ray, HitInfo &hit, std::vector<Surface *> surfaces)
{
    float min_hit = 1e5;
    for (auto &s : surfaces)
    {
        if (s->intersection(ray, hit))
        {
            hit.mat = s->getMatPtr();
            ray.tmin = hit.t;
        }
    }
    
    if (ray.tmin < 1e5 && ray.tmin > 1e-5)
    {
        hit.t = ray.tmin;
        return true;
    }
    return false;
}

bool KDNode::intersect(KDNode *node, Ray &ray, HitInfo &hit)
{
    float dist;
    if (node->aabb.hit(ray, dist))
    {
        if (dist > ray.tmin) return false;
        
        if (!node->leaf)
        {
            bool hit_left = intersect(node->left, ray,hit);
            
            bool hit_right = intersect(node->right, ray, hit);
            return hit_left || hit_right;
        }
        else
        {
            if (closestIntersection(ray, hit,node->surface))
            {
                ray.tmin = hit.t;
                return true;
            }
            
        }
    }
    return false;
}
