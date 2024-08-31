#include<iostream>
#include<limits>
#include<ctime>

[[nodiscard]] int getRandomValueInRange(const int from, const int to) noexcept {
	return std::rand() % (to - from + 1) + from;
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

void fillMatrixWithRandomValues(
	int* const* const matrix,
	const std::size_t rows,
	const std::size_t cols
) noexcept {
	for (std::size_t i = 0; i < rows; ++i) {
		for (std::size_t ii = 0; ii < cols; ++ii) {
			matrix[i][ii] = getRandomValueInRange(0, 9);
		}
	}
}

[[nodiscard]] std::size_t getIndexFromArrayMaxValue(
	const int* const arr, 
	const std::size_t size
) noexcept {
	std::size_t maxValIndex { 0 };

	for (std::size_t i = 1; i < size; ++i) {
		if (arr[maxValIndex] < arr[i]) {
			maxValIndex = i;
		}
	}

	return maxValIndex;
}

void fillMatrixRowsWithMaxValueFromOtherMatrixRows(
	int* const* const matrixDest,
	const int* const* const matrixSrc,
	const std::size_t rows,
	const std::size_t cols
) noexcept {
	for (std::size_t i = 0; i < rows; ++i) {
		const std::size_t maxValCol { getIndexFromArrayMaxValue(matrixSrc[i], cols) };
		
		for (std::size_t ii = 0; ii < cols; ++ii) {
			matrixDest[i][ii] = matrixSrc[i][maxValCol];
		}
	}
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

int main() {
	const std::size_t rows { getSizeInput("Unesite broj redova: ") };
	const std::size_t cols { getSizeInput("Unesite broj kolona: ") };

	int** randomValuesMatrix{ createMatrix(rows, cols) };
	int** maxRowValuesMatrix{ createMatrix(rows, cols) };

	fillMatrixWithRandomValues(randomValuesMatrix, rows, cols);
	fillMatrixRowsWithMaxValueFromOtherMatrixRows(maxRowValuesMatrix, randomValuesMatrix, rows, cols);

	std::cout << "Prva matrica:\n";
	printMatrix(randomValuesMatrix, rows, cols);

	std::cout << "Druga matrica (popunjena maksimalnim vrijednostima iz redova prve matrice):\n";
	printMatrix(maxRowValuesMatrix, rows, cols);

	deallocateMatrix(randomValuesMatrix, rows);
	deallocateMatrix(maxRowValuesMatrix, rows);

	return 0;
}
