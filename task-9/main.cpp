#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<ctime>

namespace constants {
	constexpr std::size_t kolonijaMravaSize { 4 };
	constexpr const char* const moguciTipMrava[] { "Crveni", "Radnici", "Faraonski", "Vojnik", "Medar"};
	constexpr const char* const moguciGradovi[] { 
		"Bihac", 
		"Bosanska Otoka", 
		"Cazin", 
		"Velika Kladusa", 
		"Bosanska Krupa",
		"Bosanski Petrovac",
	};
}

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

[[nodiscard]] char* GetNizKaraktera(const char* str) {
    if (!str) {
        return nullptr;
    }

    const std::size_t newSize { strlen(str) + 1 };
    char* const newStr { new char[newSize] {} };
    strcpy(newStr, str);

    return newStr;
}

struct Mrav {
    const char* tipMrava = nullptr;			// Crveni, Radnici, Faraonski, Vojnik, Medar
    int* kolicinaHranePrenesene = nullptr;  // Jedan broj, u intervalu 1 - 100

    void unos(const char* TipMrava) {
		tipMrava = GetNizKaraktera(TipMrava);
		kolicinaHranePrenesene = new int{ getRandomValueInRange(1, 100) };
	}

    void dealociraj() {
		delete[] tipMrava; 
		tipMrava = nullptr;

		delete kolicinaHranePrenesene; 
		kolicinaHranePrenesene = nullptr;
    }
};

struct KolonijaMrava {
	const char* grad = nullptr; // Bihac, Bosanska Otoka, Cazin, Velika Kladusa, Bosanska Krupa, Bosanski Petrovac,
	Mrav mravi[5];

	void unos(const char* Grad) {
		grad = GetNizKaraktera(Grad);		

		std::size_t tipMravaIndex = getRandomValueInRange(0, std::size(constants::moguciTipMrava) - 1);
		for (std::size_t i = 0; i < std::size(mravi); ++i) {
			(mravi + i)->unos(*(constants::moguciTipMrava + tipMravaIndex));
		}
	}

	void ispis() {
		std::cout << "Grad -> " << grad << '\n';
		std::cout << "Tip mrava kolonije -> " << mravi->tipMrava << '\n';
		for (std::size_t i = 0; i < std::size(mravi); ++i) {
			std::cout << "Kolocina hrane prenesena od mrava " << i + 1 << " -> ";
			std::cout << *(mravi + i)->kolicinaHranePrenesene << '\n';
		}
		std::cout << "Prosjecno prenesene hrane -> " << getProsjekPreneseneHrane() << '\n';
	}

	float getProsjekPreneseneHrane() {
		float sum { 0.0f };

		for (std::size_t i = 0; i < std::size(mravi); ++i) {
			sum += *(mravi + i)->kolicinaHranePrenesene;
		}

		return sum / std::size(mravi);
	}

	void dealociraj() {
		delete[] grad;
		grad = nullptr;

		for (std::size_t i = 0; i < std::size(mravi); ++i) {
			(mravi + i)->dealociraj();
		}
	}
};

void initializeKolonijeMrava(KolonijaMrava* const kolonijeMrava) {
	bool daLiJeGradIskoristen[std::size(constants::moguciGradovi)] { false };

	for (std::size_t i = 0; i < constants::kolonijaMravaSize; ++i) {
		std::size_t gradIndex{};	

		do {
			gradIndex = getRandomValueInRange(0, std::size(constants::moguciGradovi) - 1);
		} while(*(daLiJeGradIskoristen + gradIndex));

		(kolonijeMrava + i)->unos(*(constants::moguciGradovi + gradIndex));

		daLiJeGradIskoristen[gradIndex] = true;
	}
}

void ispisKolonijaMrava(KolonijaMrava* const kolonijeMrava) noexcept {
	for (std::size_t i = 0; i < constants::kolonijaMravaSize; ++i) {
		(kolonijeMrava + i)->ispis();

		if (i + 1 != constants::kolonijaMravaSize) {
			std::cout << '\n';
		}
	}
}

void deallocate(KolonijaMrava*& kolonijeMrava) {
	for (std::size_t i = 0; i < constants::kolonijaMravaSize; ++i) {
		(kolonijeMrava + i)->dealociraj();
	}

	delete[] kolonijeMrava;
	kolonijeMrava = nullptr;
}

[[nodiscard]] KolonijaMrava* getKolonijaSaNajboljimProsjekomPreneseneHrane(
	KolonijaMrava* const kolonijeMrava
) noexcept {
	std::size_t najboljiIndex { 0 };

	for (std::size_t i = 1; i < constants::kolonijaMravaSize; ++i) {
		if ((kolonijeMrava + najboljiIndex)->getProsjekPreneseneHrane() < (kolonijeMrava + i)->getProsjekPreneseneHrane()) {
			najboljiIndex = i;
		}
	}

	return kolonijeMrava + najboljiIndex;
}

[[nodiscard]] KolonijaMrava* getKolonijaSaNajgorimProsjekomPreneseneHrane(
	KolonijaMrava* const kolonijeMrava
) noexcept {
	std::size_t najgoriIndex { 0 };

	for (std::size_t i = 1; i < constants::kolonijaMravaSize; ++i) {
		if ((kolonijeMrava + najgoriIndex)->getProsjekPreneseneHrane() > (kolonijeMrava + i)->getProsjekPreneseneHrane()) {
			najgoriIndex = i;
		}
	}

	return kolonijeMrava + najgoriIndex;
}

int main() {
    srand(time(nullptr));

	KolonijaMrava* kolonijeMrava { new KolonijaMrava[constants::kolonijaMravaSize] };

	initializeKolonijeMrava(kolonijeMrava);
	ispisKolonijaMrava(kolonijeMrava);

	KolonijaMrava* najboljaKolonija { getKolonijaSaNajboljimProsjekomPreneseneHrane(kolonijeMrava) };
	KolonijaMrava* najgoraKolonija { getKolonijaSaNajgorimProsjekomPreneseneHrane(kolonijeMrava) };

	std::cout << '\n';
	std::cout << "Grad sa najboljom kolonijom -> " << najboljaKolonija->grad << '\n';
	std::cout << "Grad sa najgorom kolonijom -> " << najgoraKolonija->grad << '\n';

	deallocate(kolonijeMrava);
	
    return 0;
}
