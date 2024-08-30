#include<iostream>
#include<ctime>

namespace constants {
	constexpr std::size_t dyceSides { 6 };
	constexpr std::size_t totalDyceThrowsPerRound { 5 };
}

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

[[nodiscard]] int throwDyce() noexcept {
	return getRandomValueInRange(1, constants::dyceSides);
}

void printArray(const int* const arr, const std::size_t size) noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << ' ';
	}
}

void printDycesThrown(
	const int(&dycesThrown)[constants::totalDyceThrowsPerRound], 
	const std::size_t round
) noexcept {
	std::cout << "Bacanje " << round << ": ";
	printArray(dycesThrown, std::size(dycesThrown));
	std::cout << '\n';
}

void throwDycesAndUpdatedCounter(
	int(&dycesThrown)[constants::totalDyceThrowsPerRound], 
	int(&dycesCounter)[constants::dyceSides]
) noexcept {
	for (int& dyceThrown : dycesThrown) {
		dyceThrown = throwDyce();
		++dycesCounter[dyceThrown - 1];
	}
}

void setDycesCounterToAll0s(int(&dycesCounter)[constants::dyceSides]) noexcept {
	for (int& dyceCounter : dycesCounter) {
		dyceCounter = 0;
	}
}

[[nodiscard]] bool hasRoundEndingConditioBeenAchieved(
	const int(&dycesCounter)[constants::dyceSides]
) noexcept {
	int counter { 0 };

	for (const int dyceCounter : dycesCounter) {
		if (dyceCounter == 2) {
			++counter;
		}
	}

	return counter == 2;
}

int main() {
	std::srand(std::time(nullptr));

	int dycesThrown[constants::totalDyceThrowsPerRound]{};
	int dycesCounter[constants::dyceSides]{};
	std::size_t round { 0 };

	do {
		++round;
		setDycesCounterToAll0s(dycesCounter);

		throwDycesAndUpdatedCounter(dycesThrown, dycesCounter);
		printDycesThrown(dycesThrown, round);
	} while (!hasRoundEndingConditioBeenAchieved(dycesCounter));

	std::cout << "Ukupan broj bacanja: " << round << '\n';
	std::cout << "Posljednje izvucene vrijednosti: ";
	printArray(dycesThrown, std::size(dycesThrown));
	std::cout << '\n';

	return 0;
}
