//HEADER
#include "testers.hpp"

int launchScript(const char* file) {
    int status = system(file);

	if (status == -1) {
		perror("Erreur lors de l'exécution du script");
		return (1);
	}
    return (0);
}

int openFile(std::ifstream& expectedOutput, const char* file) {
	expectedOutput.open(file);
	if (!expectedOutput.is_open()) {
		std::cout << "Error: could not open " << file << std::endl;
		return (1);
	}
    return (0);
}

std::string trim_crlf(std::string &line) {
	if (!line.empty() && line[line.size() - 1] == '\n')
		line.erase(line.size() - 1, line.size());
	if (!line.empty() && line[line.size() - 1] == '\r')
		line.erase(line.size() - 1, line.size());
	return line;
}

void compare(std::ifstream& output, std::ifstream& expectedOutput) {
    size_t i = 1;
    std::string expectedOutputContent;
	std::string outputContent;

	std::cout << std::endl;
	while (getline(expectedOutput, expectedOutputContent, '\n') &&
		   getline(output, outputContent, '\n')) {
		outputContent = trim_crlf(outputContent);
		expectedOutputContent = trim_crlf(expectedOutputContent);

		if (expectedOutputContent != outputContent) {
			std::cerr << "\033[31mTest " << i << ":\033[0m\n"
					  << "\033[31mExpected:\033[0m " << expectedOutputContent
					  << std::endl
					  << "\033[31mGot:\033[0m " << outputContent << std::endl;
		} else
			std::cout << "\033[32mTest " << i << ":\nSuccess\033[0m\n";
		std::cout << std::endl;
		i++;
	}
}

int main() {
    std::ifstream output;
	std::ifstream expectedOutput;
	
	output.open("output.txt");
    if (!output.is_open()) {
		std::cout << "Error: could not open file 'output.txt'" << std::endl;
		return (1);
	}

	//registration
    if (launchScript("tester-scripts/test-registration.sh"))
        return (1);
    if (openFile(expectedOutput, "expected-outputs/registration_output.tx"))
        return (1);
    std::cout << "Registration:";
    compare(output, expectedOutput);

	output.close();
	expectedOutput.close();
	return (0);
}
