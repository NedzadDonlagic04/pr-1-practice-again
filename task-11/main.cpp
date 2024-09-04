#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<cstring>

namespace constants {
	constexpr std::size_t brojStolova{ 3 };
	constexpr const char* const moguceNarudzbe[]{
		"Sok od jabuke",
		"Sok od breskve",
		"Sok od narandze",
		"Sok od jagode",
		"Zeleni caj",
		"Koka kola",
		"Pepsi",
		"Fanta",
		"Kafa",
		"Viski",
		"Konjak",
		"Veliko toceno pivo"
	};
}

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

[[nodiscard]] char* GetNizKaraktera(const char* str) {
	if (!str) {
		return nullptr;
	}

	const std::size_t newSize{ strlen(str) + 1 };
	char* const newStr{ new char[newSize] {} };
	strcpy(newStr, str);

	return newStr;
}

[[nodiscard]] char* getRandomNarudzba() {
	const std::size_t index = getRandomValueInRange(0, std::size(constants::moguceNarudzbe) - 1);

	return GetNizKaraktera(*(constants::moguceNarudzbe + index));
}

struct Sto {
	const char* narudzbe[5]{ nullptr };	// narudzbe nece nuzno uvijek trebati biti skroz popunjene

	void unos() {
		const std::size_t brojNarudzbi = getRandomValueInRange(1, std::size(narudzbe) - 1);

		for (std::size_t i = 0; i < brojNarudzbi; ++i) {
			*(narudzbe + i) = getRandomNarudzba();
		}
	}

	void ispis() {
		for (std::size_t i = 0; i < std::size(narudzbe) && *(narudzbe + i); ++i) {
			std::cout << " - " << *(narudzbe + i) << '\n';
		}
	}

	void dealociraj() {
		for (std::size_t i = 0; i < std::size(narudzbe); ++i) {
			delete[] *(narudzbe + i);
			*(narudzbe + i) = nullptr;
		}
	}

	std::size_t getBrojNarudzbi() {
		std::size_t index{ 0 };

		while (index != std::size(narudzbe) && *(narudzbe + index)) {
			++index;
		}

		return index;
	}
};

struct Konobar {
	const char* imePrezime = nullptr;		// U mainu dati ime bez korisnickog unosa, mozete staviti svoje
	const char* narudzbe[5]{ nullptr };	// narudzbe nece nuzno uvijek trebati biti skroz popunjene

	void unos(const char* ImePrezime) {
		imePrezime = GetNizKaraktera(ImePrezime);
	}

	void ispis() {
		std::cout << "Konobar -> " << imePrezime << '\n';
	}

	void dealociraj() {
		delete[] imePrezime;
		imePrezime = nullptr;

		dealocirajNarudzbe();
	}

	void dealocirajNarudzbe() {
		for (std::size_t i = 0; i < std::size(narudzbe); ++i) {
			delete[] *(narudzbe + i);
			*(narudzbe + i) = nullptr;
		}
	}

	std::size_t getBrojPrazniNarudzbi() {
		std::size_t index{ 0 };

		while (index != std::size(narudzbe) && *(narudzbe + index)) {
			++index;
		}

		return std::size(narudzbe) - index;
	}

	bool daLiJeMoguceUzetiNarudzbiZaSto(Sto sto) {
		return sto.getBrojNarudzbi() <= getBrojPrazniNarudzbi();
	}

	void uzmiNarudzbeZaSto(Sto sto) {
		const std::size_t startingIndex{ std::size(narudzbe) - getBrojPrazniNarudzbi() };
		for (std::size_t i = 0; i < sto.getBrojNarudzbi(); ++i) {
			*(narudzbe + startingIndex + i) = GetNizKaraktera(*(sto.narudzbe + i));
		}
	}

	void servirajNarudzbe() {
		std::cout << "Trenutno se serviraju narudzbe:\n";
		for (std::size_t i = 0; i < std::size(narudzbe) && *(narudzbe + i); ++i) {
			std::cout << " - " << *(narudzbe + i) << '\n';
		}

		dealocirajNarudzbe();
	}
};

[[nodiscard]] Sto* generisiStolove() {
	Sto* stolovi{ new Sto[constants::brojStolova] {} };

	for (std::size_t i = 0; i < constants::brojStolova; ++i) {
		(stolovi + i)->unos();
	}

	return stolovi;
}

void dealocirajStolove(Sto*& stolovi) {
	for (std::size_t i = 0; i < constants::brojStolova; ++i) {
		(stolovi + i)->dealociraj();
	}

	delete[] stolovi;
	stolovi = nullptr;
}

void ispisiNarudzbeZaStolove(Sto* const stolovi) noexcept {
	for (std::size_t i = 0; i < constants::brojStolova; ++i) {
		std::cout << "Narudzbe za sto " << i + 1 << " ispod:\n";
		(stolovi + i)->ispis();

		if (i + 1 != constants::brojStolova) {
			std::cout << '\n';
		}
	}
}

void servirajSveNarudzbeZaStolove(
	Konobar* const konobar,
	Sto* const stolovi
) {
	for (std::size_t i = 0; i < constants::brojStolova; ++i) {
		if (!konobar->daLiJeMoguceUzetiNarudzbiZaSto(*(stolovi + i))) {
			konobar->servirajNarudzbe();
			std::cout << '\n';
		}
		konobar->uzmiNarudzbeZaSto(*(stolovi + i));
	}
	konobar->servirajNarudzbe();
}

int main() {
	std::srand(std::time(nullptr));

	Konobar* konobar{ new Konobar {} };
	konobar->unos("Nedzad Donlagic");

	Sto* stolovi{ generisiStolove() };

	ispisiNarudzbeZaStolove(stolovi);
	std::cout << '\n';
	servirajSveNarudzbeZaStolove(konobar, stolovi);

	dealocirajStolove(stolovi);
	konobar->dealociraj();
	delete konobar;

	return 0;
}
