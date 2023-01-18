#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;
// ВИСЕЛИЦА created by ANTON 
class Gallows
{
	string encryptionENG = "qwertyuiop[]asdfghjkl;'zxcvbnm,.";
	string encryptionRUS = "йцукенгшщзхъфывапролджэячсмитьбю";
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
	}

	void reset()
	{
		int b = len - 1;
		current_word = 0 + rand() % (b - 0 + 1); // choose random word
		phase = 0;
	}

	void startGame()
	{
		reset();

		srand(time(0));
		string solve = words[current_word];

		int attempt = 7;
		int remaining_letters = words[current_word].size();
		vector<string> task(remaining_letters, "_");

		int numbers[20];
		int len_num = 0;

		string user;

		for (int i = 0; i < 2; i++)
		{
			while (true)
			{
				int l1 = 0 + rand() % (remaining_letters - 0 + 1);

				if (task.at(l1) == "_")
				{
					task.at(l1) = solve[l1];
					numbers[len_num++] = l1;
					remaining_letters--;
					break;
				}
			}
		}		

		while (true)
		{
			if (remaining_letters < 1)
			{
				cout << "\nВЫ ВЫИГРАЛИ!\n\n";
				break;
			}
			if (phase == 7)
			{
				cout << "\nВЫ ПРОИГРАЛИ!\n\n";
				cout << hangman_phase[phase] << endl;
				break;
			}

			cout << "Осталось букв: " << remaining_letters << endl;
			cout << "Осталось попыток: " << attempt-phase << endl;
			cout << hangman_phase[phase] << endl;

			for (int i = 0; i < words[current_word].size(); i++)
			{
				cout << task.at(i) << " ";
			} cout << "\n\n";

			cout << "Введите букву --> ";
			cin >> user;
			system("cls");

			bool lose = true;
			for (int i = 0; i < solve.size(); i++)
			{
				if (user[0] == solve[i])
				{				
					if (len_num > 0)
					{
						lose = false;
						bool repeat = false;
						for (int j = 0; j < len_num; j++)
						{
							if (i == numbers[j]) repeat = true;
						}

						if (repeat)
						{
							cout << "\nТакая буква уже есть!\n\n";
						}
						else
						{
							for (int k = 0; k < solve.size(); k++)
							{
								if (user[0] == solve[k])
								{
									task.at(k) = solve[k];
									numbers[len_num++] = k;
									remaining_letters--;
								}
							}

							cout << "\nВы нашли букву!\n\n";							
							break;
						}
					}
					else
					{
						lose = false;
						if (find(task.begin(), task.end(), user) == task.end())
						{
							cout << "\nВы нашли букву!\n\n";
							task.at(i) = solve[i];
							numbers[len_num++] = i;
							remaining_letters--;
							break;
						}
					}

					
				}
			}

			if (lose)
			{
				cout << "\nНе угадали!\n\n";
				phase++;
			}
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
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);

	string user;

	Gallows game;

	while (true)
	{
		cout << "\tВИСЕЛИЦА\n\n";
		cout << "Выберите цифру\n1. Играть\n2. Выйти\n--> ";
		cin >> user;
		system("cls");

		if (user == "1")
		{
			game.startGame();
		}
		else if (user == "2")
		{
			cout << "Спасибо за игру!\n";
			break;
		}
		else cout << "\nНеверный ввод!\n\n";
	}
}