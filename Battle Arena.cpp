#include "GameLogic.h"
#include "Functions.h"
#include<iostream>
#include<cstdlib>


int main()
{

	SeedRandom();

	int random = GetRandomNumber();
	int option;

	vector<Player> Entities;

	Player player;
	player.name = "Tarnish";
	player.health = 100;
	player.level = 1;
	player.flask = 3;
	player.gold = 2000;
	player.healamount = random;
	player.isAlive = true;
	Entities.push_back(player);

	Player boss;
	boss.name = "Margot";
	boss.health = 145;
	boss.weapon.name = "Cursed Sword";
	boss.weapon.damage = 27;
	boss.level = 3;
	boss.healamount = random;
	boss.isAlive = true;
	Entities.push_back(boss);

	vector<Weapon> weaponshop;

	Weapon baseweapon;
	baseweapon.name = "Long Sword";
	baseweapon.damage = 11;
	baseweapon.gold = 5;
	baseweapon.isOwned = true;
	weaponshop.push_back(baseweapon);

	Weapon weapon1;
	weapon1.name = "Coded Sword";
	weapon1.damage = 297;
	weapon1.gold = 900;
	weapon1.isOwned = false;
	weaponshop.push_back(weapon1);

	Weapon weapon2;
	weapon2.name = "Last Flame";
	weapon2.damage = 22;
	weapon2.gold = 115;
	weapon2.isOwned = false;
	weaponshop.push_back(weapon2);

	char username[256];
	DWORD size = sizeof(username);
	GetUserNameA(username, &size);

	while (true)
	{
		SetConsoleTitleA("Battle Arena");
		inBattle = true;

		cout << "[1] -> Battle" << endl;
		cout << "[2] -> Shop" << endl;
		cout << "[3] -> Equip Weapon" << endl;
		cout << "[4] -> Stats" << endl;
		cout << "[5] -> Exit" << endl;
		cout << "> ";
		cin >> option;

		if (Input())
		{
			continue;
		}

		switch (option)
		{

		case BATTLE:
		{
			Clear();

			if (player.weapon.isEquipped == false)
			{
				cout << "[!] Equip a Weapon Before Battle" << endl;
				Pause();
				continue;
			}

			while (inBattle)
			{
				SetConsoleTitleA("Battle Arena (Battle)");

				int sub;

				cout << "[1] -> Attack" << endl;
				cout << "[2] -> Heal" << endl;
				cout << "[3] -> Run" << endl;
				cout << "Option: ";
				cin >> sub;

				if (Input())
				{
					continue;
				}

				switch (sub)
				{

				case ATTACK:
				{
					Clear();
					SetConsoleTitleA("Battle Arena (In Battle)");

					cout << player.name << " vs " << boss.name << endl;
					Space();

					cout << "> " << player.weapon.name << " Striking -> " << boss.name << "!" << endl;
					this_thread::sleep_for(chrono::seconds(1));

					// player attacking boss
					int before = boss.health;
					boss.health = boss.health - player.weapon.damage;
					cout << "> Boss Health: " << before << " -> " << boss.health << " (-" << player.weapon.damage << ")" << endl;
					BattlePause();

					// checking if boss hp is zero or below before we continue
					if (0 >= boss.health)
					{
						int beforegold = player.gold;
						player.gold = player.gold * 2;
						cout << "You Win, Gold Doubled!" << endl;
						Space();
						cout << "Gold: " << beforegold << " -> " << player.gold << " (+" << beforegold << ")" << endl;
						inBattle = false;
						Space();
						GetKey();

					}
					if (boss.health > 50)
					{
						// boss forecfully to attack if health is over 50
						cout << "> " << boss.weapon.name << " Striking -> " << player.name << endl;
						this_thread::sleep_for(chrono::seconds(1));

						before = player.health;
						player.health = player.health - boss.weapon.damage;
						cout << "> Player Health: " << before << " -> " << player.health << " (-" << boss.weapon.damage << ")" << endl;
						BattlePause();
					}

					// checking if player hp is zero or below before we continue back to player hit
					if (player.health <= 0)
					{
						int beforegold = player.gold;
						player.gold = player.gold - 250;
						cout << "You Lose!" << endl;
						Space();
						cout << "250 Gold Lost" << endl;
						cout << "Gold: " << beforegold << " -> " << player.gold << " (-250)" << endl;
						Space();
						GetKey();
						inBattle = false;
					}

					// if boss hp is 50 or below we generate a number between 1 and 2, 1 auto heal, 2 another attack 
					if (50 >= boss.health)
					{

						if (GetBossOption() == 1)
						{
							int healthbefore = boss.health;
							boss.health = boss.health + boss.healamount;
							cout << "Boss Healing: " << healthbefore << " -> " << boss.health << "(+" << boss.healamount << ")" << endl;
							GetKey();
						}

						if (GetBossOption() == 2)
						{
							cout << boss.weapon.name << " Striking " << player.name << endl;
							before = player.health;
							player.health = player.health - boss.weapon.damage;
							cout << "Player Health: " << before << " -> " << player.health << "(-" << boss.weapon.damage << ")" << endl;
							GetKey();
						}

					}
				}
				break;


				case HEAL:
				{

					if (player.flask == 0)
					{
						cout << "No More Flask" << endl;
					}

					if (player.health <= 70)
					{
						SetConsoleTitleA("Battle Arena (Healing)");

						int healthbefore = player.health;
						player.health = player.health + player.healamount;
						cout << "Health: " << healthbefore << " -> " << player.health << " (+" << player.healamount << ")" << endl;
						player.flask = player.flask - 1;

						if (player.flask == 2)
						{
							cout << player.flask << " Flask Remaining" << endl;
						}

						if (player.flask == 1)
						{
							cout << player.flask << " Flask Remaining" << endl;
						}

						break;
					}

					else
					{
						Space();
						cout << "Health Has To Be Equal or less Than 70" << endl;
						Pause();
						break;
					}

				}

				case RUN:
					Clear();
					SetConsoleTitleA("Battle Arena (Running... Coward)");

					cout << "You Ran Away..." << endl;
					Space();
					int goldbefore = player.gold;
					player.gold = player.gold / 2;

					if (player.gold < 0)
					{
						player.gold = 0;
					}

					player.flask = player.flask - 1;

					if (player.flask < 0)
					{
						player.flask = 0;
					}

					cout << "[!] Gold Has Been Halfed & Flask has been Reduced by 1" << endl;
					cout << "Gold: " << goldbefore << " -> " << player.gold << " (-" << goldbefore / 2 << ")" << endl;
					cout << "Flask: " << player.flask << endl;

					inBattle = false;
					Space();
					GetKey();
				}
			}
			break;
		}
		case SHOP:
		{
			Clear();
			SetConsoleTitleA("Battle Arena (Shop)");

			int index;
			int purchase;
			int available = 0;
			cout << "-Shop-" << endl;
			cout << "Gold: " << player.gold << endl;
			Space();

			for (int i = 0; i < weaponshop.size(); i++)
			{
				if (weaponshop[i].isOwned == true || weaponshop[i].name == "LongSword")
				{
					continue;
				}

				if (weaponshop[i].isOwned == false)
				{
					available++;
				}

				cout << "------------" << endl;
				cout << "Index: " << i << endl;
				weaponshop[i].List();
			}

			if (available == 0)
			{
				cout << "Come Back Later, Shop is Closed" << endl;
				Space();
				GetKey();
				break;
			}

			Space();
			cout << "Bounds [ 1 -> " << weaponshop.size() - 1 << " ]" << endl;
			cout << "Select an Index: ";
			cin >> index;

			if (Input())
			{
				continue;
			}

			char username[256];
			DWORD size = sizeof(username);
			GetUserNameA(username, &size);

			string user = username;

			if (user == "Jamaal")
			{
				isDev = true;
			}

			if (index == 1)
			{
				if (isDev == true)
				{
					weaponshop[index].isOwned = true;
					player.gold = player.gold - weaponshop[index].gold;
					Space();
					cout << "[+] Dev Sword Acquired" << endl;
					Space();
					GetKey();
					break;
				}

				else if (isDev == false)
				{
					cout << "[-] Dev Sword" << endl;
					Pause();
					break;
				}
			}


			if (index < 0 || index >= weaponshop.size() || index == 0)
			{
				Invalid();
				break;
			}

			if (weaponshop[index].isOwned == true)
			{
				Space();
				cout << "You Already Own This Weapon" << endl;
				Pause();
				break;
			}

			if (player.gold >= weaponshop[index].gold)
			{
				weaponshop[index].isOwned = true;
				player.gold = player.gold - weaponshop[index].gold;
				Space();
				cout << "[+] Purchased" << endl;
				Space();
				GetKey();
			}

			else
			{
				cout << "[!] Not Enough Gold" << endl;
				Pause();
			}

			break;
		}

		case EQUIP:
			Clear();
			SetConsoleTitleA("Battle Arena (Weapon Inventory)");

			cout << "-Weapon Inventory-" << endl;
			Space();

			for (int i = 0; i < weaponshop.size(); i++)
			{
				if (weaponshop[i].isOwned == false)
				{
					continue;
				}

				cout << "------------" << endl;
				cout << "Index: " << i << endl;
				weaponshop[i].ListInventory();
			}

			int select;
			Space();
			cout << "Bounds [ 0 -> " << weaponshop.size() - 1 << " ]" << endl;
			cout << "Select an Index To Equip: ";
			cin >> select;

			if (Input())
			{
				continue;
			}

			if (select < 0 || select >= weaponshop.size())
			{
				Invalid();
				break;
			}

			if (weaponshop[select].isOwned == false)
			{
				cout << "[!] You Do Not Own This Weapon" << endl;
				Pause();
				break;
			}

			if (weaponshop[select].isEquipped == true)
			{
				cout << "[!] Weapon is Already Equipped" << endl;
				Pause();
				break;
			}

			for (int i = 0; i < weaponshop.size(); i++)
			{
				weaponshop[i].isEquipped = false;
			}

			weaponshop[select].isEquipped = true;

			player.weapon = weaponshop[select];
			Space();
			cout << "[+] Equipped " << player.weapon.name << "!" << endl;
			Space();
			GetKey();
			break;

		case STATS:

			Clear();
			SetConsoleTitleA("Battle Arena Stat's)");

			player.Display();

			Space();
			GetKey();

			break;

		case EXIT:
			ShutDown();
		break;

		default:
			cout << "[!] Invalid Option" << endl;
			Pause();
			break;


		}
	}
}