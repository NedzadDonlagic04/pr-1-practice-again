#include<iostream>
#include<ctime>
#include<limits>

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

void moveIndexesToNextMatrixElement(
	std::size_t& currentRow, 
	std::size_t& currentCol,
	const std::size_t rows, 
	const std::size_t cols
) noexcept {
	++currentCol;
	if (currentCol == cols) {
		currentCol = 0;
		++currentRow;
	}
}

bool swapCurrentElementsIfNeccessary(
	int* const* const matrix, 
	const std::size_t rows, 
	const std::size_t cols,
	const std::size_t currentRow, 
	const std::size_t currentCol
) noexcept {
	std::size_t nextRow { currentRow };
	std::size_t nextCol { currentCol };
	moveIndexesToNextMatrixElement(nextRow, nextCol, rows, cols);

	if (matrix[currentRow][currentCol] > matrix[nextRow][nextCol]) {
		std::swap(matrix[currentRow][currentCol], matrix[nextRow][nextCol]);
		return true;
	}

	return false;
}

void sortMatrixAscendingOrder(
	int* const* const matrix, 
	const std::size_t rows, 
	const std::size_t cols
) noexcept {
    bool didElementsSwap{};
	
    std::size_t currentRow { 0 };
    std::size_t currentCol { 0 };
    do {
        didElementsSwap = false;

        for (std::size_t i = 0; i < rows - currentRow; ++i) {
            for (std::size_t ii = 0; ii < cols; ++ii) {
                if (i == rows - currentRow - 1 && ii == cols - currentCol - 1) {
                    break;
                }

                if (swapCurrentElementsIfNeccessary(matrix, rows, cols, i, ii)) {
					didElementsSwap = true;
				}
            }
        }

        moveIndexesToNextMatrixElement(currentRow, currentCol, rows, cols);

        if (currentRow == rows) {
            didElementsSwap = false;
        }
    } while (didElementsSwap);
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
	// std::srand(std::time(nullptr));

	const std::size_t rows { getSizeInput("Unesite broj redova: ") };
	const std::size_t cols { getSizeInput("Unesite broj kolona: ") };

	int** matrix { createMatrix(rows, cols) };
	fillMatrixWithRandomValues(matrix, rows, cols);

	std::cout << "Matrica:\n";
	printMatrix(matrix, rows, cols);

	sortMatrixAscendingOrder(matrix, rows, cols);

	std::cout << "Matrica poslije sortiranja (ascending order):\n";
	printMatrix(matrix, rows, cols);

	deallocateMatrix(matrix, rows);
    return 0;
}
