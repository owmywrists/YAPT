class Screen
{
    public:
    Screen(int width, int height) : m_width(width), m_height(height),
    sample(1)
    {
        m_pixelBuffer.resize(width * height);
        m_img.create(width, height, sf::Color::Black);
        m_tex.loadFromImage(m_img);
        should_reset = false;
        
    };
    ~Screen();
    void setPixel(int x, int y, float3 colour);
    unsigned int getWidth() { return m_width; }
    unsigned int getHeight() { return m_height; }
    bool getState() { return should_reset; }
    sf::Sprite getDrawableView();
    void loadImage(std::vector<float3> img);
    void reset();
    int sample;
    
    private:
    bool should_reset;
    float3 avg(float3 current_avg, float3 new_colour);
    sf::Color transform(float3 pixel);
    sf::Clock clock;
    std::vector<float3> m_pixelBuffer;
    sf::Image m_img;
    sf::Texture m_tex;
    int m_width;
    int m_height;
};
