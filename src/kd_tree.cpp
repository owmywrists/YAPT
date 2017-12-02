#include "kd_tree.h"

KDNode *KDNode::build(std::vector<Surface *> &surfaces, int depth) const
{
    KDNode *node = new KDNode();
    node->leaf = false;
    node->surface = std::vector<Surface *>();
    node->left = NULL;
    node->right = NULL;
    node->aabb = AABB();

    if (surfaces.size() == 0)
        return node;

    if (depth > 25 || surfaces.size() <= 6)
    {
        node->surface = surfaces;
        node->leaf = true;
        node->aabb = surfaces[0]->getBoundingBox();

        for (int i = 1; i < surfaces.size(); i++){
            node->aabb.expand(surfaces[i]->getBoundingBox());
        }

        node->left = new KDNode();
        node->right = new KDNode();
        node->left->surface = std::vector<Surface *>();
        node->right->surface = std::vector<Surface *>();
        return node;
    }

    node->aabb = surfaces[0]->getBoundingBox();
    float3 midpoint = float3();
    for (int i = 1; i < surfaces.size(); i++)
    {
        node->aabb.expand(surfaces[i]->getBoundingBox());
        midpoint = midpoint + (surfaces[i]->getMidpoint() * (1.0 / surfaces.size()));
    }

    std::vector<Surface *> left_surfaces;
    std::vector<Surface *> right_surfaces;
    int axis = node->aabb.getLongestAxis();
    for (int i = 0; i < surfaces.size(); i++)
    {
        switch (axis)
        {
        case 0:
            midpoint.x() >= surfaces[i]->getMidpoint().x() ? right_surfaces.push_back(surfaces[i]) : left_surfaces.push_back(surfaces[i]);
            break;
        case 1:
            midpoint.y() >= surfaces[i]->getMidpoint().y() ? right_surfaces.push_back(surfaces[i]) : left_surfaces.push_back(surfaces[i]);
            break;
        case 2:
            midpoint.z() >= surfaces[i]->getMidpoint().z() ? right_surfaces.push_back(surfaces[i]) : left_surfaces.push_back(surfaces[i]);
            break;
        }
    }

    if (surfaces.size() == left_surfaces.size() || surfaces.size() == right_surfaces.size())
    {
        node->surface = surfaces;
        node->leaf = true;
        node->aabb = surfaces[0]->getBoundingBox();

        for (int i = 1; i < surfaces.size(); i++)
        {
            node->aabb.expand(surfaces[i]->getBoundingBox());
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

bool KDNode::closestIntersection(Ray &ray, HitInfo &hit, std::vector<Surface *> surfaces) const
{
    float min_hit = 1e5;
    for (auto &s : surfaces)
    {
        if (s->intersection(ray, hit))
        {
            if (hit.t < min_hit)
            {
                hit.normal = s->getNormal(ray.getHit(hit.t));
                hit.mat = s->getMatPtr();
                min_hit = hit.t;
            }
        }
    }
    if (min_hit < 1e5 && min_hit > 1e-5)
    {
        hit.t = min_hit;
        return true;
    }
    return false;
}

bool KDNode::intersect(KDNode *node, Ray &ray, HitInfo &hit) const
{
    float dist;
    if (node->aabb.hit(ray, dist))
    {
        

        if (!node->leaf)
        {
            bool hit_left = intersect(node->left, ray, hit);

            bool hit_right = intersect(node->right, ray, hit);
            return hit_left || hit_right;
        }
        else
        {
            if (closestIntersection(ray, hit, node->surface))
            {
                return true;
            }
        }
    }
    return false;
}