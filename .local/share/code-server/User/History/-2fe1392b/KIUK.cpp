#include <iostream>
#include "coins.hpp"

using namespace std;

constexpr int CENTS_FOR_CANDYBAR = 482;

int main() {
    // Step 1: Create a Coins object `pocket` with an initial number of coins
    Coins pocket(100, 10, 10, 100);

    // Step 2: Print the initial coins in the pocket
    cout << "I started with " << pocket << " in my pocket." << endl;

    // Step 3: Extract the exact change needed for the candy bar
    Coins pay_for_candy = pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CANDYBAR));

    // Step 4: Print the transaction details
    cout << "I bought a candy bar for " << CENTS_FOR_CANDYBAR 
         << " cents using " << pay_for_candy << "." << endl;

    // Step 5: Print the remaining coins in the pocket
    cout << "I have " << pocket << " left in my pocket." << endl;

    return 0;
}
