#include "surface.h"
#include <vector>
#include "ray.h"
#include "material.h"
#include "aabb.h"

class KDNode{
public:
    AABB aabb;
    KDNode* left;
    KDNode* right;
    std::vector<Surface*> surface;
    bool leaf;


    KDNode(){};
    KDNode *build(std::vector<Surface*> &surfaces, int depth);
    bool intersect(KDNode* node, Ray &ray,HitInfo &hit);
private:
    bool closestIntersection(Ray &ray, HitInfo &hit, std::vector<Surface*> s);
};