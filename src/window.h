struct windowProperties
{
    int width;
    int height;
    std::string title;
};

class Window
{
    public:
    Window(std::string title, int width, int height, std::shared_ptr<Gui> gui) : m_prop{width, height, title}
    {
        init();
    };
    ~Window();
    Screen *getScreenPtr() { return m_screen; }
    sf::RenderWindow *getWindowPtr() { return m_win; }
    void update();
    void pollEvents();
    
    private:
    windowProperties m_prop;
    sf::RenderWindow *m_win;
    Screen *m_screen;
    sf::Sprite m_drawableView;
    sf::Clock m_delta_clock;
    std::shared_ptr<Gui> gui;
    private:
    void init();
};
