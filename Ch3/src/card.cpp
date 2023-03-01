#include "card.h"
#include <string>

using namespace std;

cardT newCard(rankT rank, suitT suit)
{
    return cardT{rank, suit};
}

rankT rank(cardT card)
{
    return card.rank;
}

suitT suit(cardT card)
{
    return card.suit;
}

string cardName(cardT card)
{
    string name = "";
    int rank = card.rank;
    int suit = card.suit;
    if (two <= rank && rank <= ten) {
        name += to_string(rank + 1);
    } else {
        switch (rank) {
        case 0:
            name += 'A';
            break;
        case 10:
            name += 'J';
            break;
        case 11:
            name += 'Q';
            break;
        case 12:
            name += 'K';
            break;
        }
    }

    switch (suit) {
    case 0:
        name += 'C';
        break;
    case 1:
        name += 'D';
        break;
    case 2:
        name += 'H';
        break;
    case 3:
        name += 'S';
        break;
    }
    return name;
}
