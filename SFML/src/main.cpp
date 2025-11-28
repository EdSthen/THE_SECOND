#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

class Button : public sf::Drawable
{
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Font m_font;
    
    sf::Color m_defaultColor{sf::Color::Blue};
    sf::Color m_hoverColor{sf::Color::Cyan};
    sf::Color m_pressColor{sf::Color::Green};
    sf::Color m_textColor{sf::Color::White};
    
    bool m_isHovered{false};
    bool m_isPressed{false};

public:
    Button(const std::string& text, const sf::Vector2f& size, const sf::Vector2f& position)
        : m_text(m_font, text, 24)
    {
        if (!m_font.openFromFile("fonts/arial.ttf"))
        {
            std::cerr << "Failed to load font!" << std::endl;
        }
        
        m_shape.setSize(size);
        m_shape.setPosition(position);
        m_shape.setFillColor(m_defaultColor);
        m_shape.setOutlineColor(sf::Color::White);
        m_shape.setOutlineThickness(2.f);
        
        m_text.setFillColor(m_textColor);
        
        sf::FloatRect textBounds = m_text.getLocalBounds();
        m_text.setOrigin(textBounds.position + textBounds.size / 2.f);
        m_text.setPosition(position + size / 2.f);
    }
    
    void update(const sf::RenderWindow& window)
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        
        m_isHovered = m_shape.getGlobalBounds().contains(mousePos);
        
        if (m_isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (!m_isPressed)
            {
                m_isPressed = true;
                std::cout << "Button pressed!" << std::endl;
            }
        }
        else
        {
            m_isPressed = false;
        }
        
        if (m_isPressed)
        {
            m_shape.setFillColor(m_pressColor);
        }
        else if (m_isHovered)
        {
            m_shape.setFillColor(m_hoverColor);
        }
        else
        {
            m_shape.setFillColor(m_defaultColor);
        }
    }
    
    void setPosition(const sf::Vector2f& position)
    {
        sf::Vector2f size = m_shape.getSize();
        m_shape.setPosition(position);
        m_text.setPosition(position + size / 2.f);
    }
    
    sf::Vector2f getSize() const { return m_shape.getSize(); }
    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    
    bool isPressed() const { return m_isPressed; }
    
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(m_shape, states);
        target.draw(m_text, states);
    }
};

class Layout : public sf::Drawable
{
protected:
    std::vector<std::unique_ptr<Button>> m_buttons;
    sf::Vector2f m_position;
    float m_spacing{10.f};

public:
    Layout(const sf::Vector2f& position = {0.f, 0.f}) : m_position(position) {}
    
    void addButton(std::unique_ptr<Button> button)
    {
        m_buttons.push_back(std::move(button));
        updatePositions();
    }
    
    void setPosition(const sf::Vector2f& position)
    {
        m_position = position;
        updatePositions();
    }
    
    void setSpacing(float spacing)
    {
        m_spacing = spacing;
        updatePositions();
    }
    
    void update(const sf::RenderWindow& window)
    {
        for (auto& button : m_buttons)
        {
            button->update(window);
        }
    }
    
protected:
    virtual void updatePositions() = 0;
    
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (const auto& button : m_buttons)
        {
            target.draw(*button, states);
        }
    }
};

class HLayout : public Layout
{
public:
    HLayout(const sf::Vector2f& position = {0.f, 0.f}) : Layout(position) {}
    
protected:
    void updatePositions() override
    {
        float currentX = m_position.x;
        for (auto& button : m_buttons)
        {
            button->setPosition({currentX, m_position.y});
            currentX += button->getSize().x + m_spacing;
        }
    }
};

class VLayout : public Layout
{
public:
    VLayout(const sf::Vector2f& position = {0.f, 0.f}) : Layout(position) {}
    
protected:
    void updatePositions() override
    {
        float currentY = m_position.y;
        for (auto& button : m_buttons)
        {
            button->setPosition({m_position.x, currentY});
            currentY += button->getSize().y + m_spacing;
        }
    }
};

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "SFML Layout Example");
    window.setFramerateLimit(75);
    
    auto hLayout = std::make_unique<HLayout>(sf::Vector2f(100.f, 100.f));
    hLayout->addButton(std::make_unique<Button>("Button 1", sf::Vector2f(150.f, 60.f), sf::Vector2f(0, 0)));
    hLayout->addButton(std::make_unique<Button>("Button 2", sf::Vector2f(150.f, 60.f), sf::Vector2f(0, 0)));
    hLayout->addButton(std::make_unique<Button>("Button 3", sf::Vector2f(150.f, 60.f), sf::Vector2f(0, 0)));
    
    auto vLayout = std::make_unique<VLayout>(sf::Vector2f(500.f, 100.f));
    vLayout->addButton(std::make_unique<Button>("Button A", sf::Vector2f(150.f, 60.f), sf::Vector2f(0, 0)));
    vLayout->addButton(std::make_unique<Button>("Button B", sf::Vector2f(150.f, 60.f), sf::Vector2f(0, 0)));
    vLayout->addButton(std::make_unique<Button>("Button C", sf::Vector2f(150.f, 60.f), sf::Vector2f(0, 0)));
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        hLayout->update(window);
        vLayout->update(window);
        
        window.clear(sf::Color::Black);
        window.draw(*hLayout);
        window.draw(*vLayout);
        window.display();
    }
    
    return 0;
}