#include <iostream>
#include "coins.hpp"

using namespace std;

constexpr int CENTS_FOR_CHIPS = 149;
constexpr int CENTS_TRANSFERRED = 405; 

int main() {
    Coins piggyBank(50, 50, 50, 50);
    Coins pocket(8, 3, 6, 8);

    cout << "Initial state:" << endl;
    cout << "Piggy bank: " << piggyBank << endl;
    cout << "Pocket: " << pocket << endl;

    Coins pay_for_chips = pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CHIPS));
    cout << "\nBought chips for $1.49 using: " << pay_for_chips << endl;
    cout << "Pocket now has: " << pocket << endl;

    Coins transfer = piggyBank.extract_exact_change(coins_required_for_cents(CENTS_TRANSFERRED));
    pocket.deposit_coins(transfer);
    cout << "\nTransferred $4.05 from piggyBank to pocket." << endl;
    cout << "Piggy bank now has: " << piggyBank << endl;
    cout << "Pocket now has: " << pocket << endl;

    Coins sofa(10, 10, 10, 10);
    piggyBank.deposit_coins(sofa);
    cout << "\nFound the following in the sofa: " << sofa << endl;
    cout << "Piggy bank now has: " << piggyBank << endl;

    int total_cents = piggyBank.total_value_in_cents();
    cout << "\nPiggy bank total: ";
    print_cents(total_cents, cout);
    cout << endl;

    return 0;
}
