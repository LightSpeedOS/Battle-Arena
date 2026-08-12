#include "GameLogic.h"
#include "Functions.h"

int main()
{

	SeedRandom();

	int random = GetRandomNumber();
	int option;
	vector<int> availableWeapons;
	vector<Player> Entities;

	Player player;
	player.name = "Tarnish";
	player.health = 100;
	player.level = 1;
	player.flask = 3;
	player.gold = 2000;
	player.elixir = 0;
	player.healamount = random;
	player.isAlive = true;
	Entities.push_back(player);

	Player boss;
	boss.name = "Margot";
	boss.health = 145;
	boss.weapon.name = "Cursed Sword";
	boss.weapon.damage = 27;
	boss.weapon.AntiHeal = false;
	boss.level = 3;
	boss.healamount = random;
	boss.isAlive = true;
	Entities.push_back(boss);

	vector<Weapon> weaponshop;

	Weapon baseweapon;
	baseweapon.name = "Long Sword";
	baseweapon.damage = 11;
	baseweapon.level = 1;
	baseweapon.gold = 5;
	baseweapon.AntiHeal = false;
	baseweapon.isOwned = true;
	weaponshop.push_back(baseweapon);

	Weapon weapon1;
	weapon1.name = "Coded Sword";
	weapon1.damage = 100;
	weapon1.level = 99;
	weapon1.gold = 900;
	weapon1.AntiHeal = true;
	weapon1.isOwned = false;
	weaponshop.push_back(weapon1);

	Weapon weapon2;
	weapon2.name = "Last Flame";
	weapon2.damage = 37;
	weapon2.level = 3;
	weapon2.gold = 115;
	weapon2.AntiHeal = false;
	weapon2.isOwned = false;
	weaponshop.push_back(weapon2);

	vector<Shop> potionshop;

	Shop potion1;
	potion1.name = "Elixir of Life";
	potion1.gold = 500;
	potion1.stock = 1;
	potion1.isOwned = false;
	potion1.isEquipped = false;
	potionshop.push_back(potion1);

	Shop potion2;
	potion2.name = "Double Power";
	potion2.gold = 250;
	potion2.stock = 2;
	potion2.Double = true;
	potion2.isOwned = false;
	potion2.isEquipped = false;
	potionshop.push_back(potion2);

	Shop potion3;
	potion3.name = "Over Heal";
	potion3.gold = 150;
	potion3.stock = 2;
	potion3.OverHealh = false;
	potion3.isOwned = false;
	potion3.isEquipped = false;
	potionshop.push_back(potion3);

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
				cout << "[3] -> Potions" << endl;
				cout << "[4] -> Run" << endl;
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

					if (potionshop[1].isEquipped == true)
					{
						player.weapon.damage = player.weapon.damage * 2;
						cout << "> " << player.weapon.name << " Striking With Double Damage -> " << boss.name << "!" << endl;

						potionshop[1].isOwned = false;
					}
					else
					{
						cout << "> " << player.weapon.name << " Striking -> " << boss.name << "!" << endl;
					}

						this_thread::sleep_for(chrono::seconds(1));

						// player attacking boss
						int before = boss.health;
						boss.health = boss.health - player.weapon.damage;
						cout << "> Boss Health: " << before << " -> " << boss.health << " (-" << player.weapon.damage << ")" << endl;
						BattlePause();


						// checking if boss hp is zero or below before we continue
						if (0 >= boss.health)
						{
							if (player.gold <= 0)
							{
								player.gold = 250;
							}

							int beforegold = player.gold;
							player.gold = player.gold * 2;
							cout << "You Win, Gold Doubled!" << endl;
							Space();
							cout << "Gold: " << beforegold << " -> " << player.gold << " (+" << beforegold << ")" << endl;
							inBattle = false;
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

							if (player.elixir > 0)
							{
								cout << "> Elixir of Life Restored You From Death!" << endl;
								Space();
								player.health = 100;
								player.elixir = player.elixir - 1;
								break;
							}

							int beforegold = player.gold;
							player.gold = player.gold - 250;

							if (player.gold <= 0)
							{
								player.gold = 0;
							}
							cout << "You Lose!" << endl;
							Space();
							cout << "250 Gold Lost" << endl;
							cout << "Gold: " << beforegold << " -> " << player.gold << " (-250)" << endl;
							GetKey();
							inBattle = false;
						}

						// if boss hp is 50 or below we generate a number between 1 and 2, 1 auto heal, 2 another attack 
						if (50 >= boss.health)
						{

							if (GetBossOption() == 1)
							{
								if (player.weapon.AntiHeal == true)
								{
									cout << "> " << boss.name << "'s Healing Was Blocked By Anti Heal!" << endl;
									BattlePause();
									break;
								}

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
				if (potionshop[1].isEquipped == true)
				{
					player.weapon.damage = player.weapon.damage / 2;
					potionshop[1].isEquipped = false;
				}
				break;


				case HEAL:
				{
					if (player.flask == 0)
					{
						Clear();
						cout << "[!] No More Flask" << endl;
						Pause();
						break;
					}

					if (potionshop[2].isEquipped == true)
					{
						player.health = 100;
						int overheal = player.health * 0.20 + player.health;
						cout << "Over Heal Applied | Player Healh: " << player.health << " -> " << overheal << " (+" << player.health * 0.20 << ")" << endl;
						potionshop[2].isOwned = false;
						potionshop[2].isEquipped = false;
						GetKey();
						break;
					}


					if (player.health <= 70)
					{
						SetConsoleTitleA("Battle Arena (Healing)");

						int healthbefore = player.health;
						player.health = player.health + player.healamount;
						player.flask = player.flask - 1;

						Space();
						cout << "Health: " << healthbefore << " -> " << player.health << " (+" << player.healamount << ")";

						if (player.flask == 2)
						{
							cout << " | " << player.flask << " Flask Remaining" << endl;
							Space();
						}

						if (player.flask == 1)
						{
							cout << " | " << player.flask << " Flask Remaining" << endl;
							Space();
						}

						if (player.flask == 0)
						{
							cout << " | " << player.flask << " Flask Remaining" << endl;
							Space();
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

				case POTION:
				{
					Clear();
					cout << "Equip a Potion" << endl;
					Space();
					int selected;

					for (int i = 0; i < potionshop.size(); i++)
					{
						if (potionshop[i].isOwned == true)
						{
							cout << "---------" << endl;
							cout << "Index: " << i << endl;
							potionshop[i].ListPotions();
						}
					}

					Space();
					cout << "Bounds [ 1 -> " << potionshop.size() - 1 << " ]" << endl;
					cout << "Select a Potion To Use" << endl;
					cout << "> ";
					cin >> selected;

					if (Input())
					{
						continue;
					}

					if (selected > potionshop.size() || selected < 0)
					{
						cout << "[!] Invalid Option" << endl;
						Pause();
						break;
					}

					if (potionshop[selected].isEquipped == true)
					{
						cout << potionshop[selected].name << " is Already Equip" << endl;
						GetKey();
						break;
					}

					if (potionshop[selected].isOwned == false)
					{
						cout << "[!] You Do Not Own " << potionshop[selected].name << endl;
						Pause();
						break;
					}

					Space();
					cout << "[+] " << potionshop[selected].name << " Ready To Use" << endl;
					potionshop[selected].isEquipped = true;
					GetKey();
					break;
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
					GetKey();
				}
			}
			break;
		}
		case SHOP:
		{
			SetConsoleTitleA("Battle Arena (Shop)");
			Clear();
			int subshop;
			Shop shop;
			cout << "Shop Selection" << endl;
			Space();

			cout << "[1] -> Weapons" << endl;
			cout << "[2] -> Potions" << endl;
			cout << "> ";
			cin >> subshop;

			if (Input())
			{
				continue;
			}

			switch (subshop)
			{

			case WEAPONS:
			{
				Clear();

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
					GetKey();
					break;
				}

				for (int i = 0; i < weaponshop.size(); i++)
				{
					if (weaponshop[i].isOwned == false)
					{
						availableWeapons.push_back(i);
					}
				}

				Space();
				cout << "Bounds [ 1 -> " << available << " ]" << endl;
				cout << "Select an Index: ";
				cin >> index;

				if (Input())
				{
					continue;
				}

				if (index < 0 || index >= weaponshop.size() || index == 0)
				{
					Invalid();
					break;
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


				if (player.level < weaponshop[index].level)
				{
					Clear();
					cout << "You Do Not Meet Level Requirements for " << weaponshop[index].name << endl;
					cout << "Your Level -> " << player.level << endl;
					cout << "Weapon Level -> " << weaponshop[index].level << endl;
					GetKey();
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
					GetKey();
				}

				else
				{
					cout << "[!] Not Enough Gold" << endl;
					Pause();
				}
				break;
			}

			case POTIONS:
			{
				int potionindex;
				Clear();

				cout << "Potion Shop | Player Gold: " << player.gold << endl;
				Space();

				for (int i = 0; i < potionshop.size(); i++)
				{
					cout << "----------" << endl;
					cout << "Index: " << i << endl;
					potionshop[i].Display();
				}
				Space();
				cout << "Bounds [ 0" << " -> " << potionshop.size() - 1 << " ]" << endl;
				cout << "Select an Index: ";
				cin >> potionindex;

				if (Input())
				{
					continue;
				}

				if (potionindex > potionshop.size() || potionindex < 0)
				{
					Invalid();
					break;
				}

				if (player.gold < potionshop[potionindex].gold)
				{
					cout << "[!] You Do Not Have Enough Gold" << endl;
					Pause();
					break;
				}

				if (potionshop[potionindex].isOwned == true)
				{
					Space();
					cout << "[!] You Already Own " << potionshop[potionindex].name << ". Use " << potionshop[potionindex].name << " Before Purchasing Another" << endl;

					GetKey();
					break;
				}

				int goldbefore = player.gold;
				potionshop[potionindex].isOwned = true;
				player.gold = player.gold - potionshop[potionindex].gold;

				Space();
				cout << "[+] " << potionshop[potionindex].name << " Successfully Purchased" << " | " << "Gold: " << goldbefore << " -> " << player.gold << " (-" << potionshop[potionindex].gold << ")" << endl;


				if (potionindex == 0)
				{
					player.elixir = player.elixir + 1;
					potionshop[potionindex].isOwned = false;
				}

				if (potionindex == 1)
				{
					potionshop[1].Double = true;
				}

				if (potionindex == 2)
				{
					potionshop[2].OverHealh = true;
				}

				GetKey();
				break;
			}
			
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
			GetKey();
			break;

		case STATS:
		{
			Clear();
			SetConsoleTitleA("Battle Arena (Stat's)");

			player.Display();
			
			if (player.gold < 400)
			{
				GetKey();
			}

			if (player.gold >= 400)
			{

				string answer;
				Space();
				cout << "Would You Like To Level Up?" << endl;
				cout << "Yes or No Y/N: " << endl;
				cin >> answer;

				transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

				if (answer == "yes" || answer == "y")
				{
					Clear();
					cout << "Enhance " << player.name << endl;
					Space();

					int levels;
					cout << "1 Level = 400 Gold | You Can Afford " << player.gold / 400 << " Levels" << endl;
					Space();

					cout << "How Many Levels Would You Like To Buy?" << endl;
					cout << "Amount: ";
					cin >> levels;

					if (levels < 0 || levels == 0)
					{
						cout << "[!] You Cant Purchase Zero or Negative Levels" << endl;
						Pause();
						break;
					}

					if ((levels * 400) <= player.gold)
					{
						player.gold = player.gold - (levels * 400);
						int healthbefore = player.health;
						int levelbefore = player.level;
						int flaskbefore = player.flask;
						player.health = player.health + ((100 * 0.12) * levels);
						player.level = player.level + levels;
						player.flask = player.flask + (levels * 1);

						if (player.flask > 11)
						{
							player.flask = 11;
						}

						Space();
						cout << "[+] Sucessfully Purchased " << levels << "!" << endl;
						cout << "Health: " << healthbefore << " -> " << player.health << " (+" << (100 * 0.12) * levels << ")" << endl;
						cout << "Level: " << levelbefore << " -> " << player.level << " (+" << levels << ")" << endl;
						cout << "Flask: " << flaskbefore << " -> " << player.flask << " (+" << (player.flask - flaskbefore) << ")" << endl; // fix flask display
						GetKey();
						break;
					}

					else
					{
						cout << "[!] Not Enough Gold" << endl;
						GetKey();
						break;
					}
				}

				if (answer == "no" || answer == "n")
				{
					cout << "[!] Returning" << endl;
					Pause();
					break;
				}

				else
				{
					cout << "[!] Invalid Option" << endl;
					Pause();
					break;
				}
			}

			break;
		}

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
