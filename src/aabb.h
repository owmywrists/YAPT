class AABB
{
    public:
    AABB(float3 min=float3(), float3 max=float3()) : min(min), max(max) {}
    
    bool hit(Ray &ray, float &t)
    {
        float3 inv_rd = ray.direction;
        
        float tx1 = (min.x - ray.origin.x) / inv_rd.x;
        float tx2 = (max.x - ray.origin.x) / inv_rd.x;
        
        float tmin = std::min(tx1, tx2);
        float tmax = std::max(tx1, tx2);
        
        float ty1 = (min.y - ray.origin.y) / inv_rd.y;
        float ty2 = (max.y - ray.origin.y) / inv_rd.y;
        
        tmin = std::max(tmin, std::min(ty1, ty2));
        tmax = std::min(tmax, std::max(ty1, ty2));
        
        float tz1 = (min.z - ray.origin.z) / inv_rd.z;
        float tz2 = (max.z - ray.origin.z) / inv_rd.z;
        
        tmin = std::max(tmin, std::min(tz1, tz2));
        tmax = std::min(tmax, std::max(tz1, tz2));
        
        t = tmin;
        
        return tmax >= tmin;
        
    }
    
    void expand(const AABB &a)
    {
        if (a.min.x < min.x)
            min.x = (a.min.x);
        
        if (a.min.y < min.y)
            min.y = (a.min.y);
        
        if (a.min.z < min.z)
            min.z = (a.min.z);
        
        if (a.max.x > max.x)
            max.x = (a.max.x);
        
        if (a.max.y > max.y)
            max.y = (a.max.y);
        
        if (a.max.z > max.z)
            max.z = (a.max.z);
    }
    
    int getLongestAxis()
    {
        float3 diff = max - min;
        if (diff.x > diff.y && diff.x > diff.z)
            return 0;
        if (diff.y > diff.x && diff.y > diff.z)
            return 1;
        return 2;
    }
    
    private:
    float3 max, min;
};