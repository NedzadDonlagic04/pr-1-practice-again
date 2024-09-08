#include<iostream>
#include<limits>
#include<cmath>

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

void fillMatrixWithPyramidPatternFromTargetPos(
	int* const * const matrix,
	const std::ptrdiff_t rows,
	const std::ptrdiff_t cols,
	const std::ptrdiff_t targetRow,
	const std::ptrdiff_t targetCol,
	const int target
) noexcept {
	for (std::ptrdiff_t i = 0; i < rows; ++i) {
		for (std::ptrdiff_t ii = 0; ii < cols; ++ii) {
			const std::ptrdiff_t distance = std::abs(i - targetRow) + std::abs(ii - targetCol);	
			matrix[i][ii] = std::max<std::ptrdiff_t>(target - distance, 0);
		}
	}
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

[[nodiscard]] std::size_t getMatrixPositionInput(
	const char* const outputText,
	const std::size_t maxVal
) {
	std::size_t input {};
	bool repeatLoop {};

	do {
		repeatLoop = false;

		std::cout << outputText;
		std::cin >> input;

		if (std::cin.fail()) {
			clearInputBuffer();
			repeatLoop = true;	
		} else if (input >= maxVal) {
			repeatLoop = true;	
		}

	} while(repeatLoop);

	clearInputBuffer();

	return input;
}

[[nodiscard]] int getTargetInput(const char* const outputText) {
	int input {};
	bool repeatLoop {};

	do {
		repeatLoop = false;

		std::cout << outputText;
		std::cin >> input;

		if (std::cin.fail()) {
			clearInputBuffer();
			repeatLoop = true;	
		} else if (input <= 0) {
			repeatLoop = true;	
		}

	} while(repeatLoop);

	clearInputBuffer();

	return input;
}

int main() {
	const std::size_t rows { getSizeInput("Unesite broj redova: ") };
	const std::size_t cols { getSizeInput("Unesite broj kolona: ") };

	const std::size_t targetRow { getMatrixPositionInput("Unesite red ciljanog mjesta: ", rows) };
	const std::size_t targetCol { getMatrixPositionInput("Unesite kolonu ciljanog mjesta: ", cols) };

	int target { getTargetInput("Unesite vrijednost target (veca od 0): ") };

	int** matrix { createMatrix(rows, cols) };

	fillMatrixWithPyramidPatternFromTargetPos(matrix, rows, cols, targetRow, targetCol, target);

	std::cout << "Formirana matrica:\n";
	printMatrix(matrix, rows, cols);

	deallocateMatrix(matrix, rows);

	return 0;
}
