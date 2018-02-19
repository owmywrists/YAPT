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
    Screen *getScreenPtr() { return m_screen; }
    void update();
    void pollEvents();
    sf::RenderWindow *sf_win;
    
    private:
    windowProperties m_prop;
    Screen *m_screen;
    sf::Sprite m_drawableView;
    sf::Clock m_delta_clock;
    private:
    void init();
};
