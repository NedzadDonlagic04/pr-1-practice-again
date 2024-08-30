#include<iostream>
#include<algorithm>
#include<filesystem>
#include<fstream>
#include<string>
#include<string_view>
#include<regex>
#include<vector>
#include<charconv>

namespace fs = std::filesystem;

namespace constants {
	constexpr std::string_view rootDirPath { "./" };

	constexpr std::string_view taskDirName { "task-" }; 
	constexpr std::string_view taskDirMainFileName { "main.cpp" }; 
	constexpr std::string_view taskDirMainFileContent {
		"#include<iostream>\n\n"
		"int main() {\n\n"
		"\treturn 0;\n"
		"}\n"
	}; 

	constexpr int initialTaskNum { 0 }; 
}

[[nodiscard]] bool validateTaskDirName(
	const std::string& dirName 
) {
	std::regex validationRegex { std::string(constants::taskDirName) + "\\d+" };
	
	return std::regex_match(dirName, validationRegex);	
}

[[nodiscard]] int getTaskDirNum(const std::string_view taskDirName) {
	std::size_t delimiterPos { taskDirName.find(constants::taskDirName) };

	if (delimiterPos == std::string_view::npos) {
		return -1;
	} 

	delimiterPos += constants::taskDirName.size();

	if (delimiterPos == taskDirName.size()) {
		return -1;
	}	

	const auto numPartOfName { taskDirName.substr(delimiterPos) };

	int result{};
	auto [ptr, ec] = std::from_chars(
		numPartOfName.data(), 
		numPartOfName.data() + numPartOfName.size(),
		result
	);

	return (ec == std::errc())? result : -1;	
}

[[nodiscard]] bool taskDirNamesCompare(
	const std::string_view taskDirName1, 
	const std::string_view taskDirName2
) {
	const int taskDirName1Num { getTaskDirNum(taskDirName1) };
	const int taskDirName2Num { getTaskDirNum(taskDirName2) };

	return taskDirName1Num < taskDirName2Num;
}

[[nodiscard]] std::vector<std::string> getTaskDirNames() {
	const fs::path rootDir{ constants::rootDirPath };
	
	std::vector<std::string> taskDirNames{};
	
	for (const auto& dirEntry : fs::directory_iterator{ rootDir }) {
		if (!dirEntry.is_directory()) {
			continue;
		}
		
		std::string dirName { dirEntry.path().filename() };

		if (!validateTaskDirName(dirName)) {
			continue;
		}

		taskDirNames.push_back(std::move(dirName));
	}

	std::sort(std::begin(taskDirNames), std::end(taskDirNames), taskDirNamesCompare);

	return taskDirNames;
}

[[nodiscard]] std::string getNextTaskDirName() {
	std::vector<std::string> taskDirNames { getTaskDirNames() };

	std::string nextTaskDirName { constants::taskDirName };
	int nextTaskDirNum { constants::initialTaskNum };

	if (taskDirNames.size()) {
		nextTaskDirNum = getTaskDirNum(taskDirNames.back()) + 1;
	}

	return nextTaskDirName + std::to_string(nextTaskDirNum);
}

void createMainFileForNextTaskDir(const std::string_view nextTaskDirName) {
	std::string mainFilePath { nextTaskDirName };
	mainFilePath += '/';
	mainFilePath += constants::taskDirMainFileName;

	std::ofstream mainFile{ mainFilePath };

	mainFile << constants::taskDirMainFileContent;
}

int main() {
	std::string nextTaskDirName { getNextTaskDirName() };
	
	fs::create_directory(nextTaskDirName);
	createMainFileForNextTaskDir(nextTaskDirName);

	return 0;
}
