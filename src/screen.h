class Screen
{
    public:
    Screen(int w, int h) : width(w), height(h),
    sample(1)
    {
        m_pixelBuffer  = new float3[width*height];
        m_img.create(width, height, sf::Color::Black);
        m_tex.loadFromImage(m_img);
        should_reset = false;
        
    };
    ~Screen(){delete m_pixelBuffer;};
    void setPixel(int x, int y, float3 colour);
    void set_tile(int start_x, int start_y, int tile_size, float3* pixels);
    void begin_tile(int start_x, int start_y, int tile_size);
    sf::Sprite get_drawable_view();
    void loadImage(float3* img);
    void reset();
    void save_frame(float3* img, std::string filename);
    int sample;
    bool should_reset;
    bool should_save;
    unsigned int width, height;
    private:
    float3 avg(float3 current_avg, float3 new_colour);
    sf::Color transform(float3 pixel);
    sf::Clock clock;
    float3* m_pixelBuffer;
    sf::Image m_img;
    sf::Texture m_tex;
};
