#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <ctime>
#include <cstdlib>


using namespace std;
bool inBattle = true;
bool isDev = false;

struct Weapon
{

	string name;
	int damage;
	int gold;
	bool isOwned = false;
	bool isEquipped = false;

	void List()
	{
		cout << "Name: " << name << endl;
		cout << "Gold: " << gold << endl;

		if (isOwned)
			cout << "Owned: True" << endl;

		else if (!isOwned)
			cout << "Owned: False" << endl;
	}

	void ListInventory()
	{
		cout << "Name: " << name << endl;
		if (isEquipped)
			cout << "Equippded: True" << endl;

		else if (!isEquipped)
			cout << "Equippded: False" << endl;
	}

};

//Weapon weapon;

struct Player
{
	string name;
	int health;
	int level;
	int healamount;
	Weapon weapon;
	int flask;
	int gold;
	bool isAlive = true;

	void Display()
	{
		cout << name << "'s Stats" << endl;
		cout << "--------" << endl;
		cout << "Health: " << health << endl;
		cout << "Level: " << level << endl;
		cout << "Gold: " << gold << endl;
		cout << "Flask: " << flask << endl;
		cout << endl;

		cout << "Weapon Stats" << endl;
		cout << "--------" << endl;

		if (weapon.isEquipped == true)
		{
			cout << "Weapon: " << weapon.name << endl;
			cout << "Attack Power: " << weapon.damage << endl;
			cout << "Value: " << weapon.gold << endl;
		}

		else if (weapon.isEquipped == false)
		{
			cout << "Equip a Weapon To See The Stats" << endl;
		}
	}

};

enum MainMenu
{

	BATTLE = 1,
	SHOP,
	EQUIP,
	STATS,
	EXIT,

};

enum PlayerOption
{
	ATTACK = 1,
	HEAL,
	RUN,
};
