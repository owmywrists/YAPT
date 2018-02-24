enum ray_type
{
    SCATTER,
    SHADOW
};

struct Ray
{
    Ray(v3f origin, v3f direction) : origin(origin), direction(direction){
        tmin = 0;
        tmax = FLT_MAX;
        type = SCATTER;
    };
    Ray(){};
    v3f get_hit(float t) { return origin + direction * t; }
    
    mutable float tmin, tmax; //if i pass const to function, i can still edit these values
    ray_type type;
    v3f origin, direction;
    
};