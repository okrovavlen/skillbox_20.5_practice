#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string target_fish;
    string caught_fish;
    int fish_count = 0;

    cout << "Enter the type of fish you want to catch: ";
    cin >> target_fish;

    ifstream river_file("river.txt");
    ofstream basket_file("basket.txt", ios::app);

    if (!river_file.is_open() || !basket_file.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }


    while (river_file >> caught_fish) {
        if (caught_fish == target_fish) {
            basket_file << caught_fish << endl;
            fish_count++;
        }
    }

    river_file.close();
    basket_file.close();

    cout << "You caught " << fish_count << " " << target_fish << (fish_count == 1 ? "" : "s") << "." << endl;

    return 0;
}