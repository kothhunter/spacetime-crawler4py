#include "coins.hpp"
#include <iostream>
using namespace std;

Coins::Coins(int num_q, int num_d, int num_n, int num_p)
    : quarters{num_q}, dimes{num_d}, nickels{num_n}, pennies{num_p} {}


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
    Coins extracted(0, 0, 0, 0);
    int current_coins[] = {quarters, dimes, nickels, pennies};
    int required_coins[] = {coins.quarters, coins.dimes, coins.nickels, coins.pennies};
    
    bool can_extract = true;
    
    for (int i = 0; i < 4; i++) {
        if (current_coins[i] < required_coins[i]) {
            can_extract = false;
            break;
        }
    }
    
    if (can_extract) {
        for (int i = 0; i < 4; i++) {
            current_coins[i] -= required_coins[i];
            extracted.quarters = coins.quarters;
            extracted.dimes = coins.dimes;
            extracted.nickels = coins.nickels;
            extracted.pennies = coins.pennies;
        }
    }
    
    quarters = current_coins[0];
    dimes = current_coins[1];
    nickels = current_coins[2];
    pennies = current_coins[3];

    return can_extract ? extracted : Coins(0, 0, 0, 0);
}

int Coins::total_value_in_cents() const {
    return (quarters * CENTS_PER_QUARTER) + (dimes * CENTS_PER_DIME) + (nickels * CENTS_PER_NICKEL) + pennies;
}

void Coins::print(ostream& out) const {
    out << quarters << " quarters, " << dimes << " dimes, "
        << nickels << " nickels, " << pennies << " pennies";
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

void print_cents(int cents, std::ostream& out){
    if ((cents%100) < 10)
        out << "$" << (cents/100) << ".0" << (cents%100);
    else
    out << "$" << (cents/100) << '.' << (cents%100);
}

Coins ask_for_coins(std::istream& in, std::ostream& out){
    int quarters;
    int dimes;
    int nickels;
    int pennies;
    out << "Quarters? ";
    in >> quarters;
    out << "Dimes? ";
    in >> dimes;
    out << "Nickels? ";
    in >>nickels;
    out << "Pennies? ";
    in>>pennies;
    return Coins(quarters, dimes, nickels, pennies);
    
}

void coins_menu(std::istream& in, std::ostream& out){
    Coins coins(0,0,0,0);

    while (true){
        out<< "Coins Menu\n";
        out<< "1. Deposit Change" << endl << "2. Extract Change" << 
        endl << "3. Print Balance" << endl << "4. Exit" << endl<< endl << "User Input: ";
    int choice;
    in >> choice;
    Coins move(0,0,0,0);
    out << endl;

    switch(choice){
        case 1:
            move = ask_for_coins(in, out);
            out <<endl<< "Thank you!" << endl << endl;
            coins.deposit_coins(move);
            break;
        case 2:
            move = ask_for_coins(in, out);
            out << "Thank you!"<<endl<<endl;
            if (!coins.has_exact_change_for_coins(move)){
                out<< "Error: Insufficient Funds" << endl << endl;
            } 
            else {
                coins.extract_exact_change(move);
            }
            break;
        case 3:
            print_cents(coins.total_value_in_cents(),out);
            out<<endl<<endl << "Thank you!" << endl << endl;
            break;
        case 4:
            goto exit_loop;
        default:
            out << "Error: Invalid Command";
    }
    }
    exit_loop:;

}