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
    bool closestIntersection(Ray &ray, HitInfo &hit, std::vector<Surface*> s);
};