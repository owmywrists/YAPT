
class Ray
{
    public:
    Ray(float3 origin, float3 direction) : m_origin(origin), m_direction(direction){
        tmin = 0;
        tmax = FLT_MAX;
    };
    Ray(){};
    float3 getHit(float t) { return m_origin + m_direction * t; }
    float3 getOrigin() { return m_origin; }
    float3 getDirection() { return m_direction; }
    
    mutable float tmin, tmax; //if i pass const to function, i can still edit these values
    private:
    float3 m_origin, m_direction;
};
//could probably just make this a struct