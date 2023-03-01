#ifndef CARD_H
#define CARD_H
#include <string>

enum rankT { ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };
enum suitT { clubs, diamonds, hearts, spades };
struct cardT
{
    rankT rank;
    suitT suit;
};

/**
 * @brief newCard creates a new card object
 * @param rank the rank to create it with
 * @param suit the suit to create it with
 * @return the card
 */
cardT newCard(rankT rank, suitT suit);

/**
 * @brief rank gets the rank of a card
 * @param card card to check
 * @return rank
 */
rankT rank(cardT card);

/**
 * @brief suit get suit from a card
 * @param card card to check
 * @return suit
 */
suitT suit(cardT card);

/**
 * @brief cardName returns a string representing the card name
 * @param card card to represent
 * @return string of cardname
 */
std::string cardName(cardT card);

#endif // CARD_H
