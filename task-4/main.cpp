#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<ctime>

namespace constants {
	constexpr std::size_t cardsSize { 52 };
	constexpr const char* const moguciZnakovi[] = {
		"tref",
		"karo",
		"srce",
		"pik"
	};
	constexpr const char* const moguceVrijednosti[] = { 
		"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "0", "K", "A" 
	};
}

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

[[nodiscard]] char* getNizKaraktera(const char* const str) noexcept {
	if (!str) {
		return nullptr;
	}

	const std::size_t size { std::strlen(str) + 1 };
	char* const newStr { new char[size] {} };
	strcpy(newStr, str);

	return newStr;
}

[[nodiscard]] char* getRandomKartaVrijednost() noexcept {
	std::size_t index = getRandomValueInRange(0, std::size(constants::moguceVrijednosti) - 1);

	return getNizKaraktera(*(constants::moguceVrijednosti + index));
}

[[nodiscard]] char* getRandomKartaZnak() noexcept {
	std::size_t index = getRandomValueInRange(0, std::size(constants::moguciZnakovi) - 1);

	return getNizKaraktera(*(constants::moguciZnakovi + index));
}

struct Karta {
	char* vrijednost = nullptr; // 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A
	char* znak = nullptr; // tref, karo, srce, pik
	void unos();
	void ispis();
	void dealociraj();
};

void Karta::unos() {
	if (!vrijednost || !znak) {
		dealociraj();
	}

	vrijednost = getRandomKartaVrijednost();
	znak = getRandomKartaZnak();
}

void Karta::ispis() {
	if (!vrijednost || !znak) {
		return;
	}

	std::cout << vrijednost << ' ' << znak << '\n';
}

void Karta::dealociraj() {
	delete[] vrijednost;
	vrijednost = nullptr;
	delete[] znak;
	znak = nullptr;
}

void setCardInfo(Karta& card, const char* const znak, const char* const vrijednost) noexcept {
	card.znak = getNizKaraktera(znak);
	card.vrijednost = getNizKaraktera(vrijednost);
}

void initializeCards(Karta(&cards)[constants::cardsSize]) noexcept {
	std::size_t cardsIndex { 0 };

	for (auto znak: constants::moguciZnakovi) {
		for (auto vrijednost: constants::moguceVrijednosti) {
			setCardInfo(*(cards + cardsIndex), znak, vrijednost);		
			++cardsIndex;
		}
	}	
}

void deallocateAllCardsData(Karta(&cards)[constants::cardsSize]) noexcept {
	for (auto& card : cards) {
		card.dealociraj();	
	}
}

void draw5Cards(
	Karta(&cards)[constants::cardsSize],
	bool (&hasCardBeenDrawn)[constants::cardsSize]
) {
	std::size_t index {};

	for (int i = 0; i < 5; ++i) {
		do {
			index = getRandomValueInRange(0, std::size(cards) - 1);
		} while(*(hasCardBeenDrawn + index));

		*(hasCardBeenDrawn + index) = true;
		(cards + index)->ispis();

		// Debugging
		// std::cout << "Index -> " << index << '\n';
	}	
}

int main() {
	std::srand(std::time(nullptr));

	Karta cards[constants::cardsSize]{};
	bool hasCardBeenDrawn[constants::cardsSize]{ false };

	initializeCards(cards);	

	for (int i = 1; i <= 5; ++i) {
		std::cout << "Izvlacenje " << i << ":\n";
		draw5Cards(cards, hasCardBeenDrawn);

		if (i != 5) {
			std::cout << '\n';
		}
	}

	deallocateAllCardsData(cards);

	return 0;
}
