#ifndef COINS_HPP
#define COINS_HPP
#include <iosfwd>

constexpr int CENTS_PER_QUARTER = 25;
constexpr int CENTS_PER_DIME = 10;
constexpr int CENTS_PER_NICKEL = 5;

class Coins {
    public:
    Coins(int q, int d, int n, int p);

    void deposit_coins(Coins& coins);

    bool has_exact_change_for_coins(const Coins& coins) const;

    Coins extract_exact_change(const Coins& coins);
}