#include <iostream>
#include "coins.hpp"

using namespace std;

class Coins {
private:
    int quarters, dimes, nickels, pennies;

public:
    // Constructor
    Coins(int q = 0, int d = 0, int n = 0, int p = 0)
        : quarters(q), dimes(d), nickels(n), pennies(p) {}

    // Overloaded inserter for printing
    friend ostream& operator<<(ostream& os, const Coins& coins) {
        os << coins.quarters << " quarters, "
           << coins.dimes << " dimes, "
           << coins.nickels << " nickels, and "
           << coins.pennies << " pennies";
        return os;
    }

    // Method to extract exact change
    Coins extract_exact_change(const Coins& required) {
        if (required.quarters > quarters || required.dimes > dimes ||
            required.nickels > nickels || required.pennies > pennies) {
            throw runtime_error("Not enough coins for exact change.");
        }
        
        quarters -= required.quarters;
        dimes -= required.dimes;
        nickels -= required.nickels;
        pennies -= required.pennies;

        return required;
    }
};

// Function to compute coins required for a given amount in cents
Coins coins_required_for_cents(int cents) {
    int quarters = cents / 25;
    cents %= 25;

    int dimes = cents / 10;
    cents %= 10;

    int nickels = cents / 5;
    cents %= 5;

    int pennies = cents;

    return Coins(quarters, dimes, nickels, pennies);
}

constexpr int CENTS_FOR_CANDYBAR = 482;

int main() {
    // Step 1: Define and initialize pocket
    Coins pocket(100, 10, 10, 100);
    cout << "I started with " << pocket << " in my pocket." << endl;

    // Step 2: Extract exact change for candy bar
    Coins pay_for_candy = pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CANDYBAR));
    cout << "I bought a candy bar for " << CENTS_FOR_CANDYBAR << " cents using " << pay_for_candy << "." << endl;

    // Step 3: Print remaining coins
    cout << "I have " << pocket << " left in my pocket." << endl;

    return 0;
}

#include <iostream>
#include "coins.hpp"

using namespace std;

constexpr int CENTS_FOR_CANDYBAR = 482;

int main() {
    Coins pocket(100, 10, 10, 100);
    
    cout << "I started with " << pocket << " in my pocket." << endl;
    Coins pay_for_candy = pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CANDYBAR));
    cout << "I bought a candy bar for " << CENTS_FOR_CANDYBAR << " cents using " << pay_for_candy << "." << endl;
    cout << "I have " << pocket << " left in my pocket." << endl;
}
