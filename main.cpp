//#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>



int main()
{
    double a = 0.50005;
    double b = 0.5000505;
    double lam = 1.29;
    for (int i = 0; i < 100; i++) {
        a *= lam;
        b *= lam;
        if (a > 1)a -= 1.0;
        if (b > 1)b -= 1.0;
        std::cout << "A: " << a << " B: " << b << std::endl;
    }
    
    return 0;
}