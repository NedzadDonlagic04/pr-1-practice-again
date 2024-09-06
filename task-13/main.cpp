#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<cstring>
#include<iomanip>

namespace constants {
	constexpr const char* const moguceDrzave[] {
		"Japan", "Italija", "Kina", "Mongolija", "Rusija", "Peru", "Argetina", "Nigerija", "Alzir", "Svedska"
	};

	constexpr const char* const moguciGradovi[] {
		"Tokio", "Drvar", "Kijev", "Helsinki", "Nurnberg", "Sisak", "Nis", "Ibiza", "Stockholm", "Toronto"
	};

	constexpr const char* const moguceRijeke[] {
		"Una", "Nil", "Oranje", "Ural", "Volta", "Beni", "Oka", "Tajo", "Napo", "Drava"
	};

	constexpr const char* const mogucePlanine[] {
		"Alphubel", "Strahlhorn", "Eiger", "Taffel", "Maglic", "Dom", "Liskamm", "Llullaillaco", "Bonete", 
		"Makalu"
	};

	constexpr const char* const moguceZivotinje[] {
		"Slon", "Krava", "Koza", "Zmija",  "Majmun", "Lav", "Aligator", "Krokodil", "Hijena", "Srna"
	};
}

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

[[nodiscard]] char getRandomUppercaseLetter() noexcept {
	return getRandomValueInRange('A', 'Z');
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

[[nodiscard]] char* getRandomElementFromCStrings(
	const char* const * const cstrings, 
	const std::size_t size
) {
	const std::size_t index = getRandomValueInRange(0, size - 1);

	return GetNizKaraktera(*(cstrings + index));
}

struct DrzaveIGradovi {
	const char* drzava = nullptr;
	const char* grad = nullptr;
	const char* rijeka = nullptr;
	const char* planina = nullptr;
	const char* zivotinja = nullptr;

	void unos() {
		drzava = getRandomElementFromCStrings(constants::moguceDrzave, std::size(constants::moguceDrzave));
		grad = getRandomElementFromCStrings(constants::moguciGradovi, std::size(constants::moguciGradovi));
		rijeka = getRandomElementFromCStrings(constants::moguceRijeke, std::size(constants::moguceRijeke));
		planina = getRandomElementFromCStrings(constants::mogucePlanine, std::size(constants::mogucePlanine));
		zivotinja = getRandomElementFromCStrings(constants::moguceZivotinje, std::size(constants::moguceZivotinje));
	}

	void ispis() {
		std::cout << "Drzava    -> " << std::quoted(drzava) << '\n';
		std::cout << "Grad      -> " << std::quoted(grad) << '\n';
		std::cout << "Rijeka    -> " << std::quoted(rijeka) << '\n';
		std::cout << "Planina   -> " << std::quoted(planina) << '\n';
		std::cout << "Zivotinja -> " << std::quoted(zivotinja) << '\n';
	}

	void dealokacija() {
		delete[] drzava;
		drzava = nullptr;

		delete[] grad;
		grad = nullptr;

		delete[] rijeka;
		rijeka = nullptr;

		delete[] planina;
		planina = nullptr;

		delete[] zivotinja;
		zivotinja = nullptr;
	}

	int getBrojZapisanihStavki(const char firstLetter) {
		int counter { 0 };

		if (*drzava == firstLetter) {
			++counter;
		} else if (*grad == firstLetter) {
			++counter;
		} else if (*rijeka == firstLetter) {
			++counter;
		} else if (*planina == firstLetter) {
			++counter;
		} else if (*zivotinja == firstLetter) {
			++counter;
		}

		return counter;
	}
};

void dealocateDrzaveIGradovi(DrzaveIGradovi*& drzaveIGradovi) {
	drzaveIGradovi->dealokacija();
	delete drzaveIGradovi;

	drzaveIGradovi = nullptr;
}

int main() {
	std::srand(std::time(nullptr));
	
	DrzaveIGradovi* igrac1 { new DrzaveIGradovi {} };
	DrzaveIGradovi* igrac2 { new DrzaveIGradovi {} };

	int counter { 0 };
	char letter {};

	do {
		if (counter != 0) {
			igrac1->dealokacija();
			igrac2->dealokacija();
			std::cout << "Slovo \'" << letter << "\' nije imalo pobjednika\n";
		}
		letter = getRandomUppercaseLetter();

		igrac1->unos();
		igrac2->unos();
		++counter;
	} while(igrac1->getBrojZapisanihStavki(letter) == igrac2->getBrojZapisanihStavki(letter));

	std::cout << "Nakon " << counter << " ponavljanja igrac ";
	if (igrac1->getBrojZapisanihStavki(letter) > igrac2->getBrojZapisanihStavki(letter)) {
		std::cout << 1;
	} else {
		std::cout << 2;
	}
	std::cout << " je pobjedio sa slovom \'" << letter << "\'\n";

	std::cout << "\nIgrac 1 je u zadnjoj rundi zapisao:\n";
	igrac1->ispis();

	std::cout << "\nIgrac 2 je u zadnjoj rundi zapisao:\n";
	igrac2->ispis();

	dealocateDrzaveIGradovi(igrac1);
	dealocateDrzaveIGradovi(igrac2);

	return 0;
}
