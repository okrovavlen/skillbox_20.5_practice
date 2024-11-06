#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

using namespace std;

struct ATMState {
    vector<int> denominations = {100, 200, 500, 1000, 2000, 5000};
    vector<int> counts;

    ATMState() : counts(denominations.size(), 0) {}
};

void saveState(const ATMState& state, const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error saving state." << endl;
        return;
    }

    for (int count : state.counts) {
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    }
}

bool loadState(ATMState& state, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        return false;
    }

    for (int& count : state.counts) {
        if (!file.read(reinterpret_cast<char*>(&count), sizeof(count))) {
            cerr << "Error reading from file.  ATM data may be corrupted." << endl;
            state = ATMState();
            return true;
        }

    }
    return true;
}

void printState(const ATMState& state) {
    long long total = 0;
    for (size_t i = 0; i < state.denominations.size(); ++i) {
        cout << state.denominations[i] << " rub: " << state.counts[i] << " bills" << endl;
        total += (long long)state.denominations[i] * state.counts[i];
    }
    cout << "Total: " << total << " rub" << endl;
}

void fillATM(ATMState& state) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 1000 / state.denominations.size());

    int currentBills = accumulate(state.counts.begin(), state.counts.end(), 0);
    int billsToAdd = 1000 - currentBills;

    for (size_t i = 0; i < state.denominations.size(); ++i){
        int toAdd = min((int)distrib(gen), billsToAdd);
        state.counts[i] += toAdd;
        billsToAdd -= toAdd;
        if (billsToAdd <= 0) break;

    }
}

bool withdraw(ATMState& state, int amount) {
    if (amount % 100 != 0) {
        cout << "Invalid amount. Must be a multiple of 100." << endl;
        return false;
    }
    vector<int> dispensed_counts(state.denominations.size(), 0);

    for (int i = state.denominations.size() - 1; i >= 0; --i) {
        while (amount >= state.denominations[i] && state.counts[i] > 0) {
            amount -= state.denominations[i];
            state.counts[i]--;
            dispensed_counts[i]++;
        }
    }

    if (amount == 0) {
        return true;
    } else {
        for (size_t i = 0; i < state.denominations.size(); ++i) {
            state.counts[i] += dispensed_counts[i];
        }
        cout << "Insufficient funds or unable to dispense the requested amount." << endl;
        return false;
    }
}

int main() {
    ATMState atm;
    if (!loadState(atm, "atm_state.bin")) {
        cout << "New ATM initialized." << endl;
    } else {
        cout << "ATM state loaded." << endl;
    }

    char operation;
    while (true) {
        printState(atm);
        cout << "Enter operation (+ to fill, - to withdraw, q to quit): ";
        cin >> operation;

        if (operation == '+') {
            fillATM(atm);
        } else if (operation == '-') {
            int amount;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            withdraw(atm, amount);
        } else if (operation == 'q') {
            break;
        } else {
            cout << "Invalid operation." << endl;
        }
    }

    saveState(atm, "atm_state.bin");
    cout << "ATM state saved." << endl;

    return 0;
}