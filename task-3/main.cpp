#include<iostream>
#include<cassert>
#include<ctime>

namespace constants {
	constexpr std::size_t maxValCard { 14 };
	constexpr std::size_t totalCardsToDrawPerRound { 4 };
}

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

[[nodiscard]] int drawCard() noexcept {
	return getRandomValueInRange(1, constants::maxValCard);
}

void printArray(const int* const arr, const std::size_t size) noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << ' ';
	}
}

void printCardsDrawn(
	const int(&deckOfCards1)[constants::totalCardsToDrawPerRound], 
	const int(&deckOfCards2)[constants::totalCardsToDrawPerRound], 
	const std::size_t round
) noexcept {
	std::cout << "Izvlacenje " << round << ". put\n";

	std::cout << "Karte 1: ";	
	printArray(deckOfCards1, std::size(deckOfCards1));
	std::cout << '\n';

	std::cout << "Karte 2: ";	
	printArray(deckOfCards2, std::size(deckOfCards2));
	std::cout << '\n';
}

void drawCards(int(&deckOfCards)[constants::totalCardsToDrawPerRound]) noexcept {
	for (int& card : deckOfCards) {
		card = drawCard();
	}
}

[[nodiscard]] bool doAllPairsOfCardsHaveSameSum(
	const int(&deckOfCards1)[constants::totalCardsToDrawPerRound], 
	const int(&deckOfCards2)[constants::totalCardsToDrawPerRound]
) noexcept {
	assert(std::size(deckOfCards1) == std::size(deckOfCards2) && "Both decks gotta be the same size");

	for (std::size_t i = 1; i < std::size(deckOfCards1); ++i) {
		if (deckOfCards1[0] + deckOfCards2[0] != deckOfCards1[i] + deckOfCards2[i]) {
			return false;
		}
	}
	
	return true;
}

int main() {
	std::srand(std::time(nullptr));

	int deckOfCards1[constants::totalCardsToDrawPerRound]{};	
	int deckOfCards2[constants::totalCardsToDrawPerRound]{};	
	std::size_t round { 0 };

	do {
		++round;
		drawCards(deckOfCards1);
		drawCards(deckOfCards2);
		printCardsDrawn(deckOfCards1, deckOfCards2, round);
		std::cout << '\n';
	} while(!doAllPairsOfCardsHaveSameSum(deckOfCards1, deckOfCards2));

	std::cout << "Ukupan broj izlacenja: " << round << '\n';
	std::cout << "Posljednje izvucene vrijednosti\n";

	std::cout << "Karte 1: ";	
	printArray(deckOfCards1, std::size(deckOfCards1));
	std::cout << '\n';

	std::cout << "Karte 2: ";	
	printArray(deckOfCards2, std::size(deckOfCards2));
	std::cout << '\n';

	return 0;
}
