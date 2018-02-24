class Surface
{
    public:
    virtual bool intersection(Ray &ray, HitInfo &hit) = 0;
    virtual std::shared_ptr<Material> getMatPtr() = 0;
    virtual void set_material(std::shared_ptr<Material> mat_type) = 0;
    virtual AABB get_bounding_box() const = 0;
    virtual v3f get_midpoint() const = 0;
};

class Sphere : public Surface
{
    public:
    Sphere(){};
    Sphere(v3f location, float radius, std::shared_ptr<Material> mat_type) : m_location(location),
    m_radius(radius),
    m_mat(mat_type) {}
    
    bool intersection(Ray &ray, HitInfo &hit);
    
    void set_material(std::shared_ptr<Material> mat_type)
    {
        m_mat = mat_type;
    }
    AABB get_bounding_box()const
    {
        return AABB(m_location - m_radius, m_location +m_radius);
    }
    std::shared_ptr<Material> getMatPtr() { return m_mat; }
    v3f get_midpoint()const
    {
        return m_location;
    }
    
    private:
    v3f m_location;
    float m_radius;
    std::shared_ptr<Material> m_mat;
};

class Triangle : public Surface
{
    public:
    Triangle(v3f *pa, v3f *pb, v3f *pc,
             v3f *na, v3f *nb, v3f *nc,
             v2f *uva, v2f *uvb, v2f *uvc,
             std::shared_ptr<Material> mat_type): m_mat(mat_type),
    p0(pa), p1(pb), p2(pc), n0(na), n1(nb), n2(nc), uv0(uva), uv1(uvb), uv2(uvc){}
    
    ~Triangle();
    bool intersection(Ray &ray, HitInfo &hit);
    
    std::shared_ptr<Material> getMatPtr() { 
        return m_mat;
    }
    void set_material(std::shared_ptr<Material> mat_type)
    {
        m_mat = mat_type;
    }
    AABB get_bounding_box()const
    {
        return AABB(v3f(
            std::min(std::min(p0->x, p1->x), p2->x ),
            std::min(std::min(p0->y, p1->y), p2->y ),
            std::min(std::min(p0->z, p1->z), p2->z )),
                    v3f(
            std::max(std::max(p0->x, p1->x), p2->x ),
            std::max(std::max(p0->y, p1->y), p2->y ),
            std::max(std::max(p0->z, p1->z), p2->z )));
    }
    v3f get_midpoint()const
    {
        return (*p0 + *p1 + *p2) /3.0;
    }
    
    v3f get_normal()
    {
        return unit((*p1 - *p0).cross(*p2 - *p0));
    }
    private:
    v3f *p0, *p1, *p2;
    v3f *n0, *n1, *n2;
    v2f *uv0, *uv1, *uv2;
    std::shared_ptr<Material> m_mat;
};
