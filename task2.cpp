#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));
    std::ofstream file("pic.txt", std::ios::binary);
    int height, width;
    std::cout << "Input width (width = height): ";
    std::cin >> width;
    height = width;

    int painting[width][height];
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            file << std::rand() % 2;
        }
        file << '\n';
    }
    file.close();
}