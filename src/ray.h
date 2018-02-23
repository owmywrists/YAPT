enum ray_type
{
    SCATTER,
    SHADOW
};

struct Ray
{
    Ray(float3 origin, float3 direction) : origin(origin), direction(direction){
        tmin = 0;
        tmax = FLT_MAX;
        type = SCATTER;
    };
    Ray(){};
    float3 get_hit(float t) { return origin + direction * t; }
    
    mutable float tmin, tmax; //if i pass const to function, i can still edit these values
    ray_type type;
    float3 origin, direction;
    
};