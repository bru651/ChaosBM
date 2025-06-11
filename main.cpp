#include <SFML/Graphics.hpp>
#include <cmath>

// Sta³e fizyczne
const float PI = 3.14159265f;
const float g = 9.81f;
const float dt = 0.03f; // krok czasu

// Parametry wahad³a
float l1 = 150.0f; // d³ugoœæ 1
float l2 = 150.0f; // d³ugoœæ 2
float m1 = 10.0f;  // masa 1
float m2 = 10.0f;  // masa 2

// K¹ty i prêdkoœci k¹towe
float a1 = PI / 2;
float a2 = PI / 2;
float a1_v = 0.0f;
float a2_v = 0.0f;

int main() {
    int displaySize = 800;
    bool pause = true;

    sf::RenderWindow window(sf::VideoMode(displaySize, displaySize), "Wahadlo");
    window.setFramerateLimit(60);

    sf::Vector2f origin(displaySize/2, displaySize/2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased) {    // Keyboard input
                if (event.key.code == sf::Keyboard::Space) {    // Pause button (Space)
                    pause = !pause;
                }
                if (event.key.code == sf::Keyboard::Escape) {    // Close program
                    window.close();
                }

            }
        }
        if (!pause) {
            // Obliczenia fizyczne 
            float num1 = -g * (2 * m1 + m2) * sin(a1);
            float num2 = -m2 * g * sin(a1 - 2 * a2);
            float num3 = -2 * sin(a1 - a2) * m2;
            float num4 = a2_v * a2_v * l2 + a1_v * a1_v * l1 * cos(a1 - a2);
            float den = l1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
            float a1_a = (num1 + num2 + num3 * num4) / den;

            num1 = 2 * sin(a1 - a2);
            num2 = a1_v * a1_v * l1 * (m1 + m2);
            num3 = g * (m1 + m2) * cos(a1);
            num4 = a2_v * a2_v * l2 * m2 * cos(a1 - a2);
            den = l2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
            float a2_a = (num1 * (num2 + num3 + num4)) / den;

            // Aktualizacja prêdkoœci i k¹tów
            a1_v += a1_a * dt;
            a2_v += a2_a * dt;
            a1 += a1_v * dt;
            a2 += a2_v * dt;


            // Pozycje
            float x1 = origin.x + l1 * sin(a1);
            float y1 = origin.y + l1 * cos(a1);
            float x2 = x1 + l2 * sin(a2);
            float y2 = y1 + l2 * cos(a2);

            // Rysowanie
            window.clear(sf::Color::Black);

            // Ramiona
            sf::Vertex line1[] = {
                sf::Vertex(origin, sf::Color::White),
                sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red)
            };
            sf::Vertex line2[] = {
                sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red),
                sf::Vertex(sf::Vector2f(x2, y2), sf::Color::White)
            };

            window.draw(line1, 2, sf::Lines);
            window.draw(line2, 2, sf::Lines);


            window.display();
        }
    }

    return 0;
}
