#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
// ¬»—≈Ћ»÷ј created by ANTON 
class Gallows
{
	string encryptionENG = "qwertyuiop[]asdfghjkl;'zxcvbnm,.";
	string encryptionRUS = "йцукенгшщзхъфывапролджэ€чсмитьбю";
	string* words;
	int len, current_word;

	string hangman_phase[8];
	int phase;

public:
	Gallows() : phase(0)
	{
		srand(time(0));
		readFile("words.txt", "for_words");
		readFile("0", "for_phases");
		current_word = 0 + rand() % (len - 0 + 1); // choose random word
	}

	void startGame()
	{
		int remaining_letters = words[current_word].size();
		vector<string> task(remaining_letters, "_");


		while (true)
		{
			cout << "ќсталось букв: " << remaining_letters << endl;
			cout << hangman_phase[phase] << endl;

			for (int i = 0; i < words[current_word].size(); i++)
			{
				cout << task.at(i) << " ";
			} cout << endl;


			break;
		}
	}

	void readFile(string path, string value)
	{
		if (value == "for_words")
		{
			string line;
			int iter = 0;

			fstream f(path);

			while (getline(f, line)) ++iter; // calculate size array

			words = new string[iter]; // create array 
			iter = 0;

			fstream f1(path);

			while (getline(f1, line)) words[iter++] = line; // fill array CODED words

			len = iter;
			f.close();
			f1.close();

			string word = "";
			for (int i = 0; i < len; i++) // decoding
			{
				for (int j = 0; j < words[i].size(); j++)
				{
					for (int k = 0; k < encryptionENG.size(); k++)
					{
						char letter = words[i][j];
						if (letter == encryptionENG[k])
						{
							word += encryptionRUS[k];
							break;
						}
					}
				}

				words[i] = word;
				word = "";
			}
		}
		else if (value == "for_phases")
		{
			string line, phase, path, text;
			for (int i = 0; i < 8; i++)
			{
				text = "";
				phase = "phases/phase";
				phase += to_string(i);
				phase += ".txt";
				fstream p(phase);

				while (getline(p, line))
				{
					text += line;
					text += "\n";
				}

				hangman_phase[i] = text;

				p.close();
			}
			
		}
	}
};

int main()
{
	system("chcp 1251");
	system("cls");

	Gallows game;
	game.startGame();
}