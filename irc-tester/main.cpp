//HEADER
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

std::string trim_crlf(std::string& line) {
    if (!line.empty() && line[line.size() - 1] == '\n') line.erase(line.size() - 1, line.size());
    if (!line.empty() && line[line.size() - 1] == '\r') line.erase(line.size() - 1, line.size());
    return line;
}

int main() {
    int status = system("./tester.sh");

    if (status == -1) {
        perror("Erreur lors de l'exécution du script");
        return (1);
    }

    std::ifstream output;
    std::ifstream expectedOutput;

    output.open("output.txt");
    expectedOutput.open("expected_output.tx");
    if (!expectedOutput.is_open() || !output.is_open())
	{
		std::cout << "Error: could not open file" << std::endl;
		return (1);
	}
    
    std::string expectedOutputContent;
    std::string outputContent;
    size_t      i = 1;
    std::cout << std::endl;
    while (getline(expectedOutput, expectedOutputContent, '\n') && getline(output, outputContent, '\n')) {
        outputContent = trim_crlf(outputContent);
        expectedOutputContent = trim_crlf(expectedOutputContent);

        if (expectedOutputContent != outputContent) {
             std::cerr << "\033[31mTest " << i << ":\033[0m\n"
                    << "\033[31mExpected:\033[0m " << expectedOutputContent << std::endl
                    << "\033[31mGot:\033[0m " << outputContent << std::endl;
        }
        else
            std::cout << "\033[32mTest " << i << ":\nSuccess\033[0m\n";
        std::cout << std::endl;
        i++;
    }
    expectedOutput.close();
    output.close();
    return (0);
}
