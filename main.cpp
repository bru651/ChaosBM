#include <vector>
#include <string>
#include <iostream>
#include <fstream>

int main()
{
    double sx = 0.50005;
    std::vector<double> sums;
    std::ofstream file("data2.csv");

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    // Nag³ówki pliku CSV
    file << "r,x\n";

    // Iteracja przez wartoœci r
    for (double r = 0.005; r < 4.0; r += 0.005) {
        double x = sx;

        for (int i = 0; i < 1000; i++) {
            x = x * r * (1 - x);
            // Zapisz wartoœæ x do pliku
            file << r << "," << x << "\n";
        }
    }

    file.close();
    std::cout << "Data saved to data.csv" << std::endl;

    return 0;
}
