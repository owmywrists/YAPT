class Screen
{
    public:
    Screen(int w, int h) : width(w), height(h),
    sample(1)
    {
        m_pixelBuffer  = new v3f[width*height];
        m_img.create(width, height, sf::Color::Black);
        m_tex.loadFromImage(m_img);
        should_reset = false;
        
    };
    ~Screen(){delete m_pixelBuffer;};
    void setPixel(int x, int y, v3f colour);
    void set_tile(int start_x, int start_y, int tile_size, v3f* pixels);
    void begin_tile(int start_x, int start_y, int tile_size);
    sf::Sprite get_drawable_view();
    void loadImage(v3f* img);
    void reset();
    void save_frame(v3f* img, std::string filename);
    int sample;
    bool should_reset;
    bool should_save;
    unsigned int width, height;
    private:
    v3f avg(v3f current_avg, v3f new_colour);
    sf::Color transform(v3f pixel);
    sf::Clock clock;
    v3f* m_pixelBuffer;
    sf::Image m_img;
    sf::Texture m_tex;
};
