#define _CTR_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<ctime>

namespace constants {
	constexpr const char* const moguciTipoviZmija[] {
		"Poskok", 
		"Piton", 
		"Anakonda", 
		"Smuk", 
		"Bjelica", 
		"Bjelouska"
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

[[nodiscard]] char* getRandomTipZmije() noexcept {
	const std::size_t index = getRandomValueInRange(0, std::size(constants::moguciTipoviZmija) - 1);

	return GetNizKaraktera(*(constants::moguciTipoviZmija + index));
}

struct Zmija {
	const char* tipZmije = nullptr;		// Poskok, Piton, Anakonda, Smuk, Bjelica, Bjelouska
	int* brojJabukaPojedenih = nullptr;	// Svaka jabuka pojedene predstavlja 1m duzine
										// Zmija je na pocetku duzine 1m

	void unos() {
		tipZmije = getRandomTipZmije();
		brojJabukaPojedenih = new int{ 1 };
	}

	void ispis() {
		std::cout << "Tip zmije -> " << tipZmije << '\n';
		std::cout << "Duzina -> " << *brojJabukaPojedenih << "m\n";
	}

	void dealokacija() {
		delete[] tipZmije;
		tipZmije = nullptr;
		delete brojJabukaPojedenih;
		brojJabukaPojedenih = nullptr;
	}

	void pojediSveJabukeUPolju(bool** polje, const std::size_t rows, const std::size_t cols) {
		for (std::size_t i = 0; i < rows; ++i) {
			for(std::size_t ii = 0; ii < cols; ++ii) {
				if (*(*(polje + i) + ii)) {
					++(*brojJabukaPojedenih);	
				}
			}
		}
	}
};

bool** generisiPolje(const std::size_t rows, const std::size_t cols) {
	bool** const polje { new bool*[rows] {} };

	for (std::size_t i = 0; i < rows; ++i) {
		*(polje + i) = new bool[cols] {};

		for (std::size_t ii = 0; ii < cols; ++ii) {
			*(*(polje + i) + ii) = getRandomValueInRange(0, 1);
		}
	}

	return polje;
}

void dealocirajPolje(bool**& polje, const std::size_t rows) {
	for (std::size_t i = 0; i < rows; ++i) {
		delete[] *(polje + i);
	}
	delete[] polje;
	polje = nullptr;
}

void ispisiPolje(bool** polje, const std::size_t rows, const std::size_t cols) noexcept {
	for (std::size_t i = 0; i < rows; ++i) {
		for (std::size_t ii = 0; ii < cols; ++ii) {
			if (*(*(polje + i) + ii)) {
				std::cout << "Jabuka ";
				continue;
			} 
			std::cout << "Trava  ";
		}
		std::cout << '\n';
	}
}

void kreirajPoljeINahraniZmijuNjime(Zmija* const zmija, const char* const text) {
	const std::size_t poljeRows = getRandomValueInRange(1, 5);
	const std::size_t poljeCols = getRandomValueInRange(1, 5);
	bool** polje { generisiPolje(poljeRows, poljeCols) };

	std::cout << text;
	ispisiPolje(polje, poljeRows, poljeCols);

	zmija->pojediSveJabukeUPolju(polje, poljeRows, poljeCols);

	dealocirajPolje(polje, poljeRows);
}

int main() {
	std::srand(std::time(nullptr));
	Zmija* zmija { new Zmija {} };

	zmija->unos();

	std::cout << "Zmija prije nego sto pojede polja:\n";
	zmija->ispis();
	std::cout << '\n';

	kreirajPoljeINahraniZmijuNjime(zmija, "Ispis prvog polja:\n");
	std::cout << '\n';
	kreirajPoljeINahraniZmijuNjime(zmija, "Ispis drugog polja:\n");
	std::cout << '\n';

	std::cout << "Zmija nakon sto pojede polja:\n";
	zmija->ispis();

	zmija->dealokacija();
	delete zmija;

	return 0;
}
