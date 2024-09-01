#include<iostream>
#include<limits>

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

void decrementTopFromMatrixPos(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	const std::size_t targetRow,
	const std::size_t targetCol
) noexcept {
	for (std::ptrdiff_t i = targetRow - 1; i >= 0; --i) {
		matrix[i][targetCol] = std::max(matrix[i + 1][targetCol] - 1, 0);
	}
}

void decrementBottomFromMatrixPos(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	const std::size_t targetRow,
	const std::size_t targetCol
) noexcept {
	for (std::size_t i = targetRow + 1; i < rows; ++i) {
		matrix[i][targetCol] = std::max(matrix[i - 1][targetCol] - 1, 0);
	}
}

void decrementLeftFromMatrixPos(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	const std::size_t targetRow,
	const std::size_t targetCol
) noexcept {
	for (std::ptrdiff_t i = targetCol - 1; i >= 0; --i) {
		matrix[targetRow][i] = std::max(matrix[targetRow][i + 1] - 1, 0);
	}
}

void decrementRightFromMatrixPos(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	const std::size_t targetRow,
	const std::size_t targetCol
) noexcept {
	for (std::size_t i = targetCol + 1; i < cols; ++i) {
		matrix[targetRow][i] = std::max(matrix[targetRow][i - 1] - 1, 0);
	}
}

void fillTopRightCorner(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	std::ptrdiff_t targetRow,
	std::size_t targetCol
) noexcept {
	--targetRow;
	++targetCol;
	while (targetRow >= 0 && targetCol < cols) {
		matrix[targetRow][targetCol] = std::max(matrix[targetRow + 1][targetCol - 1] - 1, 0);

		decrementRightFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
		decrementTopFromMatrixPos(matrix, rows, cols, targetRow, targetCol);

		--targetRow;
		++targetCol;
	}	
}

void fillTopLeftCorner(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	std::ptrdiff_t targetRow,
	std::ptrdiff_t targetCol
) noexcept {
	--targetRow;
	--targetCol;
	while (targetRow >= 0 && targetCol >= 0) {
		matrix[targetRow][targetCol] = std::max(matrix[targetRow + 1][targetCol + 1] - 1, 0);

		decrementLeftFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
		decrementTopFromMatrixPos(matrix, rows, cols, targetRow, targetCol);

		--targetRow;
		--targetCol;
	}	
}

void fillBottomRightCorner(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	std::ptrdiff_t targetRow,
	std::size_t targetCol
) noexcept {
	++targetRow;
	++targetCol;
	while (targetRow < rows && targetCol < cols) {
		matrix[targetRow][targetCol] = std::max(matrix[targetRow - 1][targetCol - 1] - 1, 0);

		decrementRightFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
		decrementBottomFromMatrixPos(matrix, rows, cols, targetRow, targetCol);

		++targetRow;
		++targetCol;
	}	
}

void fillBottomLeftCorner(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	std::ptrdiff_t targetRow,
	std::ptrdiff_t targetCol
) noexcept {
	++targetRow;
	--targetCol;
	while (targetRow < rows && targetCol >= 0) {
		matrix[targetRow][targetCol] = std::max(matrix[targetRow - 1][targetCol + 1] - 1, 0);

		decrementLeftFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
		decrementBottomFromMatrixPos(matrix, rows, cols, targetRow, targetCol);

		++targetRow;
		--targetCol;
	}	
}

void fillMatrixWithSquarePatternFromTargetPos(
	int* const * const matrix,
	const std::size_t rows,
	const std::size_t cols,
	const std::size_t targetRow,
	const std::size_t targetCol,
	const int target
) noexcept {
	matrix[targetRow][targetCol] = target;

	// Creates a + shape with decreasing values from target
	// and it's position
	decrementLeftFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
	decrementRightFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
	decrementTopFromMatrixPos(matrix, rows, cols, targetRow, targetCol);
	decrementBottomFromMatrixPos(matrix, rows, cols, targetRow, targetCol);

	// Now from that target position we fill up each corner one by one 
	fillTopRightCorner(matrix, rows, cols, targetRow, targetCol);
	fillTopLeftCorner(matrix, rows, cols, targetRow, targetCol);
	fillBottomRightCorner(matrix, rows, cols, targetRow, targetCol);
	fillBottomLeftCorner(matrix, rows, cols, targetRow, targetCol);
}

int main() {
	const std::size_t rows { getSizeInput("Unesite broj redova: ") };
	const std::size_t cols { getSizeInput("Unesite broj kolona: ") };

	const std::size_t targetRow { getMatrixPositionInput("Unesite red ciljanog mjesta: ", rows) };
	const std::size_t targetCol { getMatrixPositionInput("Unesite kolonu ciljanog mjesta: ", cols) };

	int target { getTargetInput("Unesite vrijednost target (veca od 0): ") };

	int** matrix { createMatrix(rows, cols) };

	fillMatrixWithSquarePatternFromTargetPos(matrix, rows, cols, targetRow, targetCol, target);

	std::cout << "Formirana matrica:\n";
	printMatrix(matrix, rows, cols);

	deallocateMatrix(matrix, rows);

	return 0;
}
