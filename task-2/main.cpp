#include<iostream>
#include<ctime>

namespace constants {
	constexpr std::size_t maxValCard { 14 };
	constexpr std::size_t totalCardsToDrawPerRound { 10 };
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
	const int(&deckOfCards)[constants::totalCardsToDrawPerRound], 
	const std::size_t round
) noexcept {
	std::cout << "Izvlacenje " << round << ": ";
	printArray(deckOfCards, std::size(deckOfCards));
	std::cout << '\n';
}

[[nodiscard]] bool drawCardsAndReturnAreAllEvenDrawsEvenNumbers(
	int(&deckOfCards)[constants::totalCardsToDrawPerRound]
) noexcept {
	bool allCardsEven { true };

	for (std::size_t i = 0; i < std::size(deckOfCards); ++i) {
		deckOfCards[i] = drawCard();
		
		if (i % 2 != 0 && deckOfCards[i] % 2 != 0) {
			allCardsEven = false;
		}
	}

	return allCardsEven;
}

int main() {
	std::srand(std::time(nullptr));

	int deckOfCards[constants::totalCardsToDrawPerRound]{};	
	std::size_t round { 0 };
	bool areAllEvenDrawsEvenNumbers {};

	do {
		++round;
		areAllEvenDrawsEvenNumbers = drawCardsAndReturnAreAllEvenDrawsEvenNumbers(deckOfCards);
		printCardsDrawn(deckOfCards, round);
	} while(!areAllEvenDrawsEvenNumbers);
	
	std::cout << "Ukupan broj izlacenja: " << round << '\n';
	std::cout << "Posljednje izvucene vrijednosti: ";
	printArray(deckOfCards, std::size(deckOfCards));
	std::cout << '\n';

	return 0;
}
