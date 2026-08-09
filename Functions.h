#pragma once
#include "GameLogic.h"

void Clear()
{
	system("CLS");
}

void Pause()
{
	this_thread::sleep_for(chrono::seconds(2));
	Clear();
}

void GetKey()
{
	cout << "Press Any Key To Return" << endl;
	cin.ignore();
	getchar();
	Clear();
}

bool Input()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "[!] Invalid Option" << endl;
		Pause();
		return true;
	}
	return false;
}

void ShutDown()
{
	int result = MessageBoxA(NULL, "Are You Sure?", "Warning!", MB_YESNO | MB_ICONWARNING);

	if (result == IDYES)
	{
		Clear();
		cout << "Shutting Down";
		this_thread::sleep_for(chrono::seconds(1));
		cout << ".";
		this_thread::sleep_for(chrono::seconds(1));
		cout << ".";
		this_thread::sleep_for(chrono::seconds(1));
		cout << ".";
		exit(0);
	}

	else if (result == IDNO)
	{
		cout << endl;
		cout << "Returning";
		Clear();
		return;
	}

}

void SeedRandom()
{
	srand(time(0));
}

int GetRandomNumber()
{
	return rand() % 22 + 10;
}

int GetBossOption()
{
	return rand() % 2 + 1;
}

void Invalid()
{
	cout << "[!] Invalid Index" << endl;
	Pause();
}

void Space()
{
	cout << endl;
}


void BattlePause()
{
	Space();
	this_thread::sleep_for(chrono::seconds(1));
}