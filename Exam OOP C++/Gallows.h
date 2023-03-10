#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdio.h> 
#include <time.h> 
using namespace std;

class Gallows
{
	string encryptionENG = "qwertyuiop[]asdfghjkl;'zxcvbnm,.";
	string encryptionRUS = "йцукенгшщзхъфывапролджэячсмитьбю";
	string* words;
	int len, current_word;

	string hangman_phase[8];
	int phase;

public:
	Gallows();

	void reset();

	void startGame();

	void readFile(string, string);
};