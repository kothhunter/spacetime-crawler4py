#include "coins.hpp"
#include <iostream>
using namespace std;

Coins::Coins(int q, int d, int n, int p)
    : quarters{q}, dimes{d}, nickels{n}, pennies{p} {}

void Coins::deposit_coins(Coins& coins){
    this->quarters += coins.quarters;
    this->dimes += coins.dimes;
    this->nickels += coins.nickels;
    this->pennies += coins.pennies;
    coins.quarters = 0;
    coins.dimes = 0;
    coins.nickels = 0;
    coins.pennies = 0;
}

bool Coins::has_exact_change_for_coins(const Coins& coins) const {
    return quarters >= coins.quarters && dimes >= coins.dimes &&
           nickels >= coins.nickels && pennies >= coins.pennies;
}

Coins Coins::extract_exact_change(const Coins& coins){
    if(has_exact_change_for_coins(coins)){
        quarters -= coins.quarters;
        dimes -= coins.dimes;
        nickels -= coins.nickels;
        pennies -= coins.pennies;
        return coins;
    }
    return Coins(0,0,0,0);
}

int Coins::total_value_in_cents() const {
    return (quarters * CENTS_PER_QUARTER) + (dimes * CENTS_PER_DIME) +
           (nickels * CENTS_PER_NICKEL) + pennies;
}

void Coins::print(ostream& out) const {
    out << quarters << " quarters, "
        << dimes << " dimes, "
        << nickels << " nickels, "
        << pennies << " pennies";
}

ostream& operator<<(ostream& out, const Coins& coins) {
    coins.print(out);
    return out;
}

Coins coins_required_for_cents(int amount_in_cents) {
    int q = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;
    int d = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;
    int n = amount_in_cents / CENTS_PER_NICKEL;
    amount_in_cents %= CENTS_PER_NICKEL;
    int p = amount_in_cents;
    return Coins(q, d, n, p);
}

void print_cents(int cents, ostream& out) {
    out << "$" << (cents / 100) << "." << (cents % 100);
}

Coins ask_for_coins(istream& in, ostream& out) {
    int q, d, n, p;
    out << "Enter the number of quarters: ";
    in >> q;
    out << "Enter the number of dimes: ";
    in >> d;
    out << "Enter the number of nickels: ";
    in >> n;
    out << "Enter the number of pennies: ";
    in >> p;
    return Coins(q, d, n, p);
}

void coins_menu(istream& in, ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    int choice;
    do {
        out << "\nMenu:\n"
            << "1. Deposit change\n"
            << "2. Extract change\n"
            << "3. Print total balance\n"
            << "4. Exit\n"
            << "Enter your choice: ";
        in >> choice;
        switch (choice) {
            case 1: {
                Coins deposit = ask_for_coins(in, out);
                myCoins.deposit_coins(deposit);
                out << "Deposited: " << deposit << "\n";
                break;
            }
            case 2: {
                Coins withdrawal = ask_for_coins(in, out);
                try {
                    myCoins.extract_exact_change(withdrawal);
                    out << "Extracted: " << withdrawal << "\n";
                } catch (const invalid_argument& e) {
                    out << e.what() << "\n";
                }
                break;
            }
            case 3: {
                out << "Total balance: ";
                print_cents(myCoins.total_value_in_cents(), out);
                out << "\n";
                break;
            }
            case 4:
                out << "Exiting...\n";
                break;
            default:
                out << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 4);
}
