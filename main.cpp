#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <fstream>

const float PI = 3.14159265f;
const float g = 9.81f;
const float dt = 0.05f;



struct DoublePendulum {
    float l1 = 150.0f;
    float l2 = 150.0f;
    float m1 = 10.0f;
    float m2 = 10.0f;

    float a1;
    float a2;
    float a1_v = 0.0f;
    float a2_v = 0.0f;

    sf::Color color;

    std::vector<std::pair<float, float>> trajectory; // do zapisu a2 vs a2_v


    DoublePendulum(float a1_init, float a2_init, sf::Color col)
        : a1(a1_init), a2(a2_init), color(col) {
    }

    void record() {
        trajectory.emplace_back(a2, a2_v);
    }

    void update() {
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

        a1_v += a1_a * dt;
        a2_v += a2_a * dt;
        a1 += a1_v * dt;
        a2 += a2_v * dt;
    }

    void draw(sf::RenderWindow& window, sf::Vector2f origin) {
        float x1 = origin.x + l1 * sin(a1);
        float y1 = origin.y + l1 * cos(a1);
        float x2 = x1 + l2 * sin(a2);
        float y2 = y1 + l2 * cos(a2);

        sf::Vertex line1[] = {
            sf::Vertex(origin, sf::Color::White),
            sf::Vertex(sf::Vector2f(x1, y1), color)
        };
        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(x1, y1), color),
            sf::Vertex(sf::Vector2f(x2, y2), sf::Color::White)
        };

        window.draw(line1, 2, sf::Lines);
        window.draw(line2, 2, sf::Lines);
    }
};

int main() {
    const int displaySize = 800;
    bool pause = true;
    sf::RenderWindow window(sf::VideoMode(displaySize, displaySize), "Wahadla Podwójne");
    window.setFramerateLimit(60);
    sf::Vector2f origin(displaySize / 2, displaySize / 2);

    // Tworzymy wahadla
    std::vector<DoublePendulum> pendulums;
    const int numPendulums = 200;
    float baseAngle = PI / 2;
    for (int i = 0; i < numPendulums; ++i) {
        float offset = i * 0.0001f;
        sf::Color color = sf::Color(50 + i, 100, 255 - i);
        pendulums.emplace_back(baseAngle + offset, baseAngle, color);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space)
                    pause = !pause;
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        if (!pause) {
            for (auto& p : pendulums)
                p.update();
            pendulums[0].record();
            pendulums[1].record();
        }

        window.clear(sf::Color::Black);
        for (auto& p : pendulums)
            p.draw(window, origin);
        window.display();
    }

    std::ofstream file("trajectory.csv");
    file << "a2_1,a2v_1,a2_2,a2v_2\n";
    size_t size = std::min(pendulums[0].trajectory.size(), pendulums[1].trajectory.size());
    for (size_t i = 0; i < size; ++i) {
        std::pair<float,float> p1 = pendulums[0].trajectory[i];
        std::pair<float, float> p2 = pendulums[1].trajectory[i];
        file << p1.first << "," << p1.second << "," << p2.first << "," << p2.second << "\n";
    }
    file.close();

    return 0;
}
