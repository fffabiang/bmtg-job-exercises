// Poker 

// Exercise4.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define CARDS_PER_PLAYER 5

#define HIGH_CARD 1
#define ONE_PAIR 2
#define TWO_PAIRS 3
#define THREE_OF_A_KIND 4
#define STRAIGHT 5
#define FLUSH 6
#define FULL_HOUSE 7
#define FOUR_OF_A_KIND 8
#define STRAIGHT_FLUSH 9
#define ROYAL_FLUSH 10

//Card type in word form
std::string GetCardTypeName(char letter) {

	switch (letter)
	{

	case 'C':
		return "treboles";
	case 'S':
		return "espadas";
	case 'H':
		return "corazones";
	case 'D':
		return "diamantes";
	default:
		return "";
	}

}

//Card value in word form
std::string GetCardValueName(char letter, bool plural = false) {

	switch (letter) {
		case '2':
			return "dos";

		case '3':
			return "tres";
		
		case'4':
			return "cuatro";

		case '5':
			return "cinco";

		case '6':
			return "seis";

		case '7':
			return plural? "sietes" : "siete";

		case '8':
			return plural ? "ochos" : "ocho";

		case '9':
			return plural ? "nueves" : "nueve";

		case 'T':
			return "diez";

		case 'J':
			return plural ? "jacks" : "jack";
		
		case 'Q':
			return plural ? "reinas" : "reina";

		case 'K':
			return plural ? "reyes" : "rey";

		case 'A':
			return plural ? "Ace" : "Aces";

		default:
			break;

	}

	return "";

}

//For each letter of the card read, we return the proper value in integer type
int GetCardValue(std::string card) {

	if (card[0] <= '9' && card[0] >= '2') {

		return (card[0] - '0');

	}
	else if (card[0] == 'T') {
		return 10;
	}
	else if (card[0] == 'J') {
		return 11;
	}
	else if (card[0] == 'Q') {
		return 12;
	}
	else if (card[0] == 'K') {
		return 13;
	}
	else if (card[0] == 'A') {
		return 14;
	}
	else {
		return 0;
	}
	

}

//Checks for the hand's highest card
bool CheckClass_HighCard(std::string hand[], int& handValue, std::string& className) {

	int maxValue = 0;
	int maxIndex = 0;

	for (int i = 0;i < CARDS_PER_PLAYER;i++) {

		int value = GetCardValue(hand[i]);
		if (value > maxValue) {
			maxValue = value;
			maxIndex = i;
		}

	}

	handValue = maxValue;
	className = "HIGH CARD " + GetCardValueName(hand[maxIndex][0]);

	return true;

}

//Checks if hand is ONE PAIR or TWO PAIR
bool CheckClass_Pairs(std::string hand[], int& handValue, std::string& className, int expectedPairs) {

	int numPairs = 0;
	int pairs[2] = {0,0};
	int indexPair = 0;

	for (int i = 0;i < CARDS_PER_PLAYER;i++) {

		for (int j = 0; j < CARDS_PER_PLAYER; j++) {

			if (i != j) {

				if (GetCardValue(hand[i]) == GetCardValue(hand[j]) && GetCardValue(hand[i]) != pairs[0] && GetCardValue(hand[i]) != pairs[1])
				{
					pairs[numPairs] = GetCardValue(hand[i]);
					indexPair = i;
					numPairs++;			
				}
			}
		}
	}

	if (numPairs != expectedPairs) {

		return false;

	}
	else {

		if (numPairs == 1) {
			className = "PAIR " + GetCardValueName(hand[indexPair][0], true);
			handValue = pairs[0]; //ONE PAIR value equals the card that has a pair
		}
		else if (numPairs == 2) {
			className = "TWO PAIR"; 
			handValue = 0; //This class doesn't have card-related value according to example
		}

		return true;

	}

}


//Checks if class is either THREE OF A KIND or FOUR OF A KIND
bool CheckClass_RepeatedCards(std::string hand[], int& handValue, std::string& className, int expectedRepetitionTimes) {

	int timesRepeated = 0;

	for (int i = 0;i < CARDS_PER_PLAYER;i++) {

		timesRepeated = 1;

		for (int j = 0; j < CARDS_PER_PLAYER; j++) {

			if (i != j) {

				if (GetCardValue(hand[i]) == GetCardValue(hand[j])) {
					timesRepeated++;
				}
			}
		}

		if (timesRepeated == expectedRepetitionTimes && timesRepeated >= 3 && timesRepeated <= 4) {

			handValue = GetCardValue(hand[i]); //THREE/FOUR of a kind have a card-related value according to the card repeated
			switch (timesRepeated) {
				case 3:
					className = "THREE OF " + GetCardValueName(hand[i][0]);
					break;

				case 4:
					className = "FOUR OF " + GetCardValueName(hand[i][0]);
					break;

				default:
					break;

			}
					
			return true;

		}
 

	}

	return false;



}




bool CheckClass_Flush(std::string hand[], int& handValue, std::string& className) {

	for (int i = 1;i < CARDS_PER_PLAYER;i++) {
		if (hand[i][1] != hand[i - 1][1]) {
			return false;
		}
	}


	handValue = 0; //This class doesn't have card-related value according to example
	className = "FLUSH de " + GetCardTypeName(hand[0][1]);
	return true;

}

//Is three of a kind and contains a different pair
bool CheckClass_FullHouse(std::string hand[], int& handValue, std::string& className) {

	int auxVal;
	std::string auxStr;
	int auxVal2;
	std::string auxStr2;

	if (CheckClass_Pairs(hand, auxVal, auxStr, 2) && CheckClass_RepeatedCards(hand, auxVal2, auxStr2, 3) ) {
		handValue = auxVal2; //This class has a card-related value that equals the three of a kind card found (according to example)
		className = "FULL HOUSE de " + std::to_string(auxVal2);
		return true;
	}
	else {
		return false;
	}

}


//Process a hand and sets its values in a sorted array
void GetHandSortedValues(std::string hand[], int sortedArray[]) {

	//Array of card values
	int handValues[CARDS_PER_PLAYER] = {};
	for (int i = 0;i < CARDS_PER_PLAYER;i++) {
		handValues[i] = GetCardValue(hand[i]);
	}

	//Sorting the values
	std::sort(std::begin(handValues), std::end(handValues), [](auto &left, auto &right) {
		return left < right;
	});

	//Copy result
	for (int i = 0;i < CARDS_PER_PLAYER;i++) {
		sortedArray[i] = handValues[i];
	}

}

//All cards have consecutive values
bool CheckClass_Straight(std::string hand[], int& handValue, std::string& className) {

	//Array of card values
	int handValues[CARDS_PER_PLAYER] = {};

	GetHandSortedValues(hand, handValues);

	for (int i = 1; i < CARDS_PER_PLAYER; i++) {
		if (handValues[i] != (handValues[i - 1] + 1)) {
			return false;
		}
	}

	handValue = 0; //This class doesn't have card-related value according to example
	className = "STRAIGHT";

	return true;


}

//Hand is both STRAIGHT and FLUSH
bool CheckClass_StraightFlush(std::string hand[], int& handValue, std::string& className) {

	int auxVal;
	std::string auxStr;
	int auxVal2;
	std::string auxStr2;

	if (CheckClass_Flush(hand,auxVal,auxStr) && CheckClass_Straight(hand,auxVal2,auxStr2)){

		handValue = 0; //This class doesn't have card-related value according to example
		className = "STRAIGHT FLUSH";

		return true;

	}


	return false;

}

//Hand contains 10, JACK, QUEEN, KING, ACE of same type
bool CheckClass_RoyalFlush(std::string hand[], int& handValue, std::string& className) {

	int auxVal;
	std::string auxStr;

	//All cards are of same type
	if (CheckClass_StraightFlush(hand, auxVal, auxStr))
	{
		
		//Array of card values
		int handValues[CARDS_PER_PLAYER] = {};
		GetHandSortedValues(hand, handValues);


		//Sorted array starts at 10 (and it goes up to ACE)
		if (handValues[0] == 10) {
			handValue = 0; //This class doesn't have card-related value according to example
			className = "ROYAL FLUSH";
			return true;
		}
		else {

			return false;
		}

	}
	else 
	{

		return false;
	}



}

//Check if a hand belongs to a possibleClass (Macro defined values), if true it assigns the handValue and the classes' name (for output)
bool isHandOfClass(std::string hand[], int possibleClass, int& handValue, std::string& className) {

	switch (possibleClass) {

	case HIGH_CARD:
		return CheckClass_HighCard(hand, handValue, className);

	case ONE_PAIR:
		return CheckClass_Pairs(hand, handValue, className, 1);
		
	case TWO_PAIRS:
		return CheckClass_Pairs(hand, handValue, className, 2);

	case THREE_OF_A_KIND:
		return CheckClass_RepeatedCards(hand, handValue, className, 3);

	case STRAIGHT:
		return CheckClass_Straight(hand, handValue, className);

	case FLUSH:
		return CheckClass_Flush(hand, handValue, className);

	case FULL_HOUSE:
		return CheckClass_FullHouse(hand, handValue, className);

	case FOUR_OF_A_KIND:
		return CheckClass_RepeatedCards(hand, handValue, className, 4);

	case STRAIGHT_FLUSH:
		return CheckClass_StraightFlush(hand, handValue, className);

	case ROYAL_FLUSH:
		return CheckClass_RoyalFlush(hand, handValue, className);

	default:
		break;
	}

	return false;

}

//Analyze which kind of class the hand is, starting from the most valuable type
int GetHandClass(std::string playerHand[], int& handValue, std::string& className) {

	std::string tmpClassName;
	int tmpHandValue;

	for (int i = ROYAL_FLUSH; i >= HIGH_CARD; i--) {

		//If true, we set the class name to be printed and the hand's value (related to a card)
		if (isHandOfClass(playerHand, i, tmpHandValue, tmpClassName)) {
			className = tmpClassName;
			handValue = tmpHandValue;
			return i; //Hand class is returned.
		}

	}

	return 0; //should not reach here, hand must be of one class

}



//Calculates winner of current hand (returns number of winning player)
int GetWinner(std::string player1Hand[], std::string player2Hand[], std::string& hand1ClassName, std::string& hand2ClassName, int& highestCard1, int& highestCard2) {

	int hand1Value, hand2Value;

	int hand1Class = GetHandClass(player1Hand, hand1Value, hand1ClassName);
	int hand2Class = GetHandClass(player2Hand, hand2Value, hand2ClassName);

	//First the hand classes are compared
	if (hand1Class > hand2Class) {
		return 1;
	}
	else if (hand1Class < hand2Class) {
		return 2;
	}
	else {

		//Next, hand values are compared
		if (hand1Value > hand2Value) {
			return 1;
		}
		else if (hand1Value < hand2Value) {
			return 2;
		}
		else {
			//Analyze when hand classes and values are equal
			
			//Array of card values
			int hand1[CARDS_PER_PLAYER] = {};
			GetHandSortedValues(player1Hand, hand1);

			int hand2[CARDS_PER_PLAYER] = {};
			GetHandSortedValues(player2Hand, hand2);

			for (int i = CARDS_PER_PLAYER - 1; i >= 0; i--) {

				highestCard1 = hand1[i];
				highestCard2 = hand2[i];

				if (highestCard1 > highestCard2) {
					return 1;
				}
				else if (highestCard1 < highestCard2) {
					return 2;
				}

			}

			return 3;//Should not reach here. Result must be PLAYER 1 OR 2

		}
	}
}


 
int main()
{
    char filename[] = "poker.txt";
	std::ifstream file;
	std::string card;
	int numCard = 0;
	int numGames = 0;
	std::string player1Hand[5] = {};
	std::string player2Hand[5] = {};

	file.open(filename);

	std::cout << "Mano\tJugador 1\t\tJugador 2\t\tGanador" << std::endl; //Output header

	while (file >> card)
	{
		
		numCard++;

		//Assigning card read to hand array of player 1 or player 2
		if (numCard <= CARDS_PER_PLAYER) {
			player1Hand[numCard - 1] = card;
		}
		else {
			player2Hand[numCard - 1 - CARDS_PER_PLAYER] = card;
		}

		//Output
		if (numCard == 1) {
			std::cout << std::endl << numGames + 1 << "\t";
		}
		
		std::cout << card << " " ;

		if (numCard == CARDS_PER_PLAYER) {
			std::cout << "\t\t";
		}

		//If we read both hands, a winner is calculated and printed
		if (numCard == (CARDS_PER_PLAYER * 2) ) {

			int highestCard1 = 0, highestCard2 = 0;

			std::string player1HandClass, player2HandClass;

			std::cout << "\t\tJugador " << GetWinner(player1Hand, player2Hand, player1HandClass, player2HandClass, highestCard1, highestCard2) << std::endl;

			std::cout << "\t" << player1HandClass << "\t\t" << player2HandClass << std::endl;

			if (highestCard1 != 0 && highestCard2 != 0) {
				std::cout << "\tMaxima carta " << highestCard1 << "\t\tMaxima carta " << highestCard2 << std::endl;
			}

			numCard = 0;
			numGames++;
		}

	}


}