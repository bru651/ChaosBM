#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


int main()
{

    double sa = 0.50005,a=sa;
    double sb = 0.5000505,b=sb;
    double d = 0.0000005;
    double lam = 1.99;
    double sum;
    std::vector<double> sums;
    for (int j = 0; j < 1000; j++) {
        sum = 0;
        a = sa; b = sb+j*d;
        //std::cout << "|A-B|: " << abs(a - b) << std::endl;
        for (int i = 0; i < 1000; i++) {
            a *= lam;
            b *= lam;
            if (a > 1)a -= 1.0;
            if (b > 1)b -= 1.0;
            sum += abs(a-b);
            //std::cout << "|A-B|: " << abs(a-b) << std::endl;
        }
        sums.push_back(sum);
        //std::cout << "SUM: " << sum << std::endl;
    }
    std::ofstream file("data1.csv");
    if (file.is_open()) {
        for (const auto& value : sums) {
            file << value << "\n";
        }
        file.close();
        std::cout << "Data saved to data.csv" << std::endl;
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
    return 0;
}