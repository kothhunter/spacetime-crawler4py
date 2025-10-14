#include <iostream>
#include <string>
using namespace std;

template<typename TheType> class Pair {
    public:
        void Input();
        void Output();
        char CompareWith(Pair<TheType>* otherPair);
        void ShowComparison(Pair<TheType>* otherPair);

    private:
        TheType firstVal;
        TheType secondVal;
};

template<typename TheType>
char Pair<TheType>::CompareWith(Pair<TheType>* otherPair) {
    if (firstVal < otherPair->firstVal)
        return '<';
    else if (firstVal > otherPair->firstVal)
        return '>';
    else if (secondVal < otherPair->secondVal)
        return '<';
    else if (secondVal > otherPair->secondVal)
        return '>';
    else
        return '=';
}

template<typename TheType>
void Pair<TheType>::Input() {
    cin >> firstVal >> secondVal;
}

template<typename TheType>
void Pair<TheType>::Output() {
    cout << "[" << firstVal << ", " << secondVal << "]";
}

template<typename TheType>
void Pair<TheType>::ShowComparison(Pair<TheType>* otherPair) {
    char symb = CompareWith(otherPair);
    Output();
    cout << " " << symb << " ";
    otherPair->Output();
    cout << endl;
}

// int main() {
//     Pair<int> intPair, intOtherPair;
//     intPair.Input();
//     intOtherPair.Input();
//     intPair.ShowComparison(&intOtherPair);

//     Pair<double> doublePair, doubleOtherPair;
//     doublePair.Input();
//     doubleOtherPair.Input();
//     doublePair.ShowComparison(&doubleOtherPair);

//     Pair<string> wordPair, wordOtherPair;
//     wordPair.Input();
//     wordOtherPair.Input();
//     wordPair.ShowComparison(&wordOtherPair);

//     return 0;
// }

int main() {
    Pair<int> intPair;
    Pair<int> intOtherPair;
    intPair.Input();
    intOtherPair.Input();
    intPair.ShowComparison(&intOtherPair);

    Pair<double> doublePair;
    Pair<double> doubleOtherPair;
    doublePair.Input();
    doubleOtherPair.Input();
    doublePair.ShowComparison(&doubleOtherPair);

    Pair<string> wordPair;
    Pair<string> wordOtherPair;
    wordPair.Input();
    wordOtherPair.Input();
    wordPair.ShowComparison(&wordOtherPair);
    return 0;
}