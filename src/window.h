struct windowProperties
{
    int width;
    int height;
    std::string title;
};

class Window
{
    public:
    Window(std::string title, int width, int height) : m_prop{width, height, title}
    {
        init();
    };
    ~Window();
    void update();
    void poll_events();
    sf::RenderWindow *sf_win;
    Screen *screen;
    private:
    windowProperties m_prop;
    sf::Sprite m_drawable_view;
    sf::Clock m_delta_clock;
    private:
    void init();
};
