#include<iostream>
#include<limits>
#include<ctime>

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
}

void clearInputBuffer() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

[[nodiscard]] std::size_t getSizeInput(const char* const outputText) {
	std::size_t input {};
	bool repeatLoop {};

	do {
		repeatLoop = false;

		std::cout << outputText;
		std::cin >> input;

		if (std::cin.fail()) {
			clearInputBuffer();
			repeatLoop = true;	
		} else if (input == 0) {
			repeatLoop = true;	
		}

	} while(repeatLoop);

	clearInputBuffer();

	return input;
}

[[nodiscard]] int* getArrayFilledWithRandomValues(const std::size_t size) {
	int* const arr { new int[size] {} };

	for (std::size_t i = 0; i < size; ++i) {
		arr[i] = getRandomValueInRange(0, 9);
	}

	return arr;
}

[[nodiscard]] int** createMatrix(const std::size_t rows, const std::size_t cols) {
	int** const matrix { new int*[rows] {} };

	for (std::size_t i = 0; i < rows; ++i) {
		matrix[i] = new int[cols] {};
	}

	return matrix;
}

void deallocateMatrix(int**& matrix, const std::size_t rows) {
	for (std::size_t i = 0; i < rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}

void printMatrix(
	const int* const* const matrix, 
	const std::size_t rows, 
	const std::size_t cols
) noexcept {
	for (std::size_t i = 0; i < rows; ++i) {
		for (std::size_t ii = 0; ii < cols; ++ii) {
			std::cout << matrix[i][ii] << ' ';
		}
		std::cout << '\n';
	}
}

void fillMatrixWithValuesFromArray(
	const int* const arr, 
	const std::size_t size, 
	int* const * const matrix
) noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		matrix[0][i] = arr[i];
	}

	for (std::size_t i = 1; i < size; ++i) {
		for (std::size_t ii = 0; ii < size; ++ii) {
			matrix[i][ii] = std::max(matrix[i - 1][ii] - 1, 0);
		}
	}
}

void printArray(const int* const arr, const std::size_t size) noexcept {
	for (std::size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << ' ';
	}
	std::cout << '\n';
}

int main() {
	std::srand(std::time(nullptr));

	const std::size_t size { getSizeInput("Unesite duzinu niza: ") };
	int* const arr { getArrayFilledWithRandomValues(size) };	
	int** matrix { createMatrix(size, size) };
	
	fillMatrixWithValuesFromArray(arr, size, matrix);

	std::cout << "Niz popunjen nasumicnim vrijednostima:\n";
	printArray(arr, size);

	std::cout << "Popunjena matrica:\n";
	printMatrix(matrix, size, size);

	deallocateMatrix(matrix, size);
	delete[] arr;

	return 0;
}
