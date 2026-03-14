#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

class Pokemon {//Class for Pokemon

	private:
		string name;//Pokemon name
		string nameattack;//Attack name
		int hp = 0;//HP during the game
		int temp_hp = 0;//Original HP
		int level = 0;//Pokemon level
		int attack = 0;//Attack during the game
		int temp_attack = 0;//Original attack

	public:
		Pokemon(string n, int h, int l, int a) :name(n), hp(h), level(l), attack(a) {}//Constructor for entering data

		void ShowStats() {//Function to display your Pokemon's stats
			temp_hp = hp;
			temp_attack = attack;
			cout << name << ":\n----------------\n Hp: " << hp << "\n Level: " << level << endl;
			cout << "===========================================" << endl;
		}

		string GetName() {//Function to get the name
			return name;
		}

		int GetHp() {//Function to get HP
			return hp;
		}

		int GetLevel() {//Function to get the level
			return level;
		}

		string GetNameAttack() {//Function to get the attack name
			return nameattack;
		}

		int GetAttack() {//Function to get the attack value
			return attack;
		}

		void LevelUp() {//Function to level up your Pokemon
			hp = temp_hp + 10;
			level += 1;
			attack = temp_attack + 2;
		}

		void Reset() {//Function to reset stats after a defeat
			hp = temp_hp;
			attack = temp_attack;
		}

		void ShowAttack() {//Function to display your Pokemon's attacks
			cout << "ATTACK:\n----------------\n[1-Quick Attack]  [2-Super Attack]  [3-Heal]";
			cout << "\nInput number: ";
			int move = 0;
			cin >> move;

			cout << "===========================================" << endl;
			if (move == 1) //Normal attack
				nameattack = "Quick Attack";

			else if (move == 2) {//Attack increases attack by 1 but reduces HP by 5
				nameattack = "Super Attack";
				hp -= 5;
				attack += 1;
			}

			else if (move == 3) {//Heal restores 20 HP but reduces attack by 3
				nameattack = "Heal";
				hp += 20;
				if (hp > temp_hp)//System so the Pokemon cannot heal above max HP
					hp = temp_hp;
				attack -= 3;
				if (attack <= 0)//System so attack cannot go negative
					attack = 0;
			}
		}

		void EnemyAttack() {//AI enemy attacks
			int enemymove = rand() % (5 - 1 + 1) + 1;

			if (enemymove == 1 || enemymove == 2)//Normal attack
				nameattack = "Quick Attack";

			else if (enemymove == 3 || enemymove == 4) {//Attack increases attack by 1 but reduces HP by 5
				nameattack = "Super Attack";
				hp -= 5;
				attack += 1;
			}
			else if (enemymove == 5) {//Heal restores 20 HP but reduces attack by 3
				nameattack = "Heal";
				hp += 20;

				if (name == "Chaterpi" && hp > 10)//Max HP of Chaterpi
					hp = 10;

				else if (name == "Onix" && hp > 60)//Max HP of Onix
					hp = 60;

				else if (name == "Charizard" && hp > 120)//Max HP of Charizard
					hp = 120;

				attack -= 3;
				if (attack <= 0)//System so attack cannot go negative
					attack = 0;
			}
		}

		bool TakeDamage(int demage) {//Function for taking damage
			hp -= demage;
			if (hp <= 0)
				return false;
			else
				return true;
		}

};

class Battle {//Class for battle

	public:
		Battle(Pokemon& pikachu, Pokemon& enemy) {//Function to display Pokemon levels and HP
			cout << "BATTLE:\n----------------\n" << pikachu.GetLevel() << " lvl : " << enemy.GetLevel() << " lvl" << endl;
			cout << pikachu.GetName() << " " << pikachu.GetHp() << "hp VS ";
			cout << enemy.GetName() << " " << enemy.GetHp() << "hp" << endl;
			cout << "===========================================" << endl;
		}

		void FightPokemon(Pokemon& pikachu, Pokemon& enemy) {//Function for Pokemon battle
			while (true) {

				pikachu.ShowAttack();//Display our Pokemon's attack choice
				enemy.EnemyAttack();//AI opponent attack
				cout << pikachu.GetName() << " uses " << pikachu.GetNameAttack() << ", -" << pikachu.GetAttack() << endl;
				cout << enemy.GetName() << " uses " << enemy.GetNameAttack() << ", -" << enemy.GetAttack() << endl;
				cout << "===========================================" << endl;
				//Display which move each Pokemon uses and how much damage it deals

				if (enemy.TakeDamage(pikachu.GetAttack()) == false) {//If we win the battle
					cout << "You won!" << endl;
					break;
				}

				if (pikachu.TakeDamage(enemy.GetAttack()) == false) {//If we lose the battle
					cout << "You lost!" << endl;
					break;
				}

				cout << pikachu.GetName() << " " << pikachu.GetHp() << "hp\t" << enemy.GetName() << " " << enemy.GetHp() << "hp" << endl;
				//Display Pokemon HP during the battle
				cout << "===========================================" << endl;
			}
		}
};

int main() {
	srand(time(NULL));
	Pokemon pikachu("Pikachu", 20, 5, 7);//Enter data for our Pokemon

	while (true) {//While loop for battles

		pikachu.ShowStats();//Display stats of our Pokemon
		cout << "Choose enemy:\n----------------\n [1]-Chaterpi\n [2]-Onix\n [3]-Charizard\n [4]-Exit\nInput number: ";
		int choice = 0;
		cin >> choice;
		//Choose opponent

		cout << "===========================================" << endl;
		Pokemon enemy("", 0, 0, 0);//Create object before the if statement

		if (choice == 1)//Choice 1
			enemy = Pokemon("Chaterpi", 10, 3, 4);

		else if (choice == 2)//Choice 2
			enemy = Pokemon("Onix", 60, 12, 13);

		else if (choice == 3)//Choice 3
			enemy = Pokemon("Charizard", 120, 18, 28);

		else if (choice == 4)//Exit
			break;

		else//If we enter an invalid input we get an impossible opponent
			enemy = Pokemon("Mewtwo", 9999, 999, 999);

		Battle fight(pikachu, enemy);
		fight.FightPokemon(pikachu, enemy);

		cout << "===========================================" << endl;

		if (pikachu.GetHp() > 0)//Level up if we win
			pikachu.LevelUp();

		else//If we lose reset to normal
			pikachu.Reset();
	}
}