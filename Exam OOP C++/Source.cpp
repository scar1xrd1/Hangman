#include "Gallows.h"
// ВИСЕЛИЦА created by ANTON 

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