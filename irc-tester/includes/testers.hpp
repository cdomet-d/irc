//HEADER

#ifndef TESTERS_HPP
#define TESTERS_HPP
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

int testRegistration(void);
void compare(std::ifstream &output, std::ifstream &expectedOutput);
int launchScript(const char *file);
int openFile(std::ifstream &expectedOutput, const char *file);

#endif