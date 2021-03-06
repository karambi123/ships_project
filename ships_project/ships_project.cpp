//Ship Wars Project
//Creators: Szymon Buksak, Mikołaj Herzberg

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <io.h>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <math.h>

#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

struct ship {
	short size;
	short amount;
	short setting_order = 0;  // used in Selecting_setup() function to determine the order of setting ships
	string name;
	string position; // vertical | horizontal | cross
};

struct match_config {
	string type = "standard"; // Standard | Custom
	string oponent; //Player | SI
	string player1; //Player1's name
	string player2; //Player2's name

	//default match rules
	bool ships_beside = false; //if false => there must be 1 empty space between each ship
	bool cross_setting = false; //if true => ships can be set in cross position "\"
	bool board_type_int = false; //if true => all coordinates of board will be presented as int value
	int computer_difficulty = 1;
	//default miss sound
	int miss_tone_1 = 350, miss_tone_2 = 225;
	int miss_duration_1 = 250, miss_duration_2 = 200;
	//default shot sound
	int shot_tone = 300;
	int shot_duration = 300;
	//default hit sound
	int hit_tone = 340;
	int hit_duration = 600;

	//default ship info 
	vector <ship> Battleship;
	short Battleship_amount = 1;
	short Battleship_size = 4;
	string Battleship_name = "Battleship";
	vector <ship> cruiser;
	short cruiser_amount = 2;
	short cruiser_size = 3;
	string cruiser_name = "Cruiser";
	vector <ship> destroyer;
	short destroyer_amount = 3;
	short destroyer_size = 2;
	string destroyer_name = "Destroyer";

	//custom ships
	vector <vector<ship>> custom_ship_main; //Player can create her own ships. It contains all custom ships
	vector <ship> custom_ship; //Single custom ship
	short custom_ships_amount = 0; //Amount of custom ships

	//default board dimensions
	int board_size_x = 10;
	int board_size_y = 10;

	//special helps
	int turn = 0; //Used to determine how much turns have been in the game
	string winner; //Who won the Battle?
};

//MAIN MENU FUNCTIONS
match_config Main_menu(match_config &);
match_config Main_menu_help(match_config &);
match_config Main_menu_settings(match_config &);
match_config Main_menu_settings_sound(int &, match_config &, int, string);
match_config Main_menu_play(match_config &);
match_config Main_menu_play_custom(match_config &);
match_config Main_menu_custom_ships(match_config &);
match_config Main_menu_custom_ship_creator(match_config &);
match_config Main_menu_custom_boards(match_config &);
match_config Main_menu_custom_basic_rules(match_config &);
void Main_menu_copyright(match_config &);
void Main_menu_exit(match_config &);
int Main_menu_choice(int &);

//GENERATING FUNCTIONS
vector <ship> Generating_ship(struct ship, vector <ship> &, match_config &, short, short, string);
vector <vector<short>> Generating_board(vector <vector<short>> &, match_config &);
vector <vector<ship>> Custom_ship_update(vector <vector<ship>> &, int);
vector <vector<short>> Computer_shooting(vector <vector<short>> &, vector <vector<short>> &, vector <vector<short>> &, match_config &);
vector <vector<short>> Computer_setup(match_config &, vector <vector<short>> &);

//DISPLAYING FUNCTIONS
string Displaying_picture_ascii(ifstream &);
void Game_intro();
void Displaying_ships(match_config &);
void Displaying_board(vector <vector<short>> &, match_config);

//PLAY FUNCTIONS
vector <ship> Setting_ship(vector<ship> &, match_config &, vector <vector<short>> &, short &, string);
vector <vector<short>> Selecting_setup(match_config &, vector <vector<short>> &, string);
vector <vector<short>> Player_shooting(vector <vector<short>> &, match_config &, vector <vector<short>> &, string);
vector <vector<short>> Board_set(vector <vector<short>> &, int, int, vector<ship>, short);
vector <vector <short>> Battle(vector<vector<short>> &, vector<vector<short>> &, match_config &, vector <vector<short>> &, vector <vector<short>> &);
bool Board_collision(vector<vector<short>> &, int, int, vector<ship>, short, match_config);
bool Board_is_empty(vector<vector<short>>);
void Game_results(match_config &);
int Setting_coordinates(int &, int &, match_config &);

//HELP FUNCTIONS
size_t Ship_counting(match_config &);


int main()
{
	//EARLY SETTINGS
	match_config match;

	//BOARDS
	vector< vector<short>> board_1, board_2;
	vector < vector<short>> board_1_mirror, board_2_mirror;
	Game_intro();
	cout << "If this is your first time using this app, we recommend to see help page. To select a help page input '4' on your keyboard and click 'Enter' button." << endl;

	Main_menu(match);
	//START FUNCTIONS
	Generating_board(board_1, match);
	Generating_board(board_2, match);
	Generating_board(board_1_mirror, match);
	Generating_board(board_2_mirror, match);
	Generating_ship(ship(), match.Battleship, match, match.Battleship_amount, match.Battleship_size, match.Battleship_name);
	Generating_ship(ship(), match.cruiser, match, match.cruiser_amount, match.cruiser_size, match.cruiser_name);
	Generating_ship(ship(), match.destroyer, match, match.destroyer_amount, match.destroyer_size, match.destroyer_name);
	match_config match2 = match;


	//GAME PLAYER VS PLAYER
	if (match.oponent == "player") {
		system("cls");
		cout << "\n\n";
		cout << "[SETTING FORMATION]\n" << endl;
		Displaying_board(board_1, match);
		Selecting_setup(match, board_1, match.player1);
		system("cls");
		cout << "[SETTING FORMATION]\n" << endl;
		Displaying_board(board_2, match2);
		Selecting_setup(match2, board_2, match2.player2);
		system("cls");
		cout << "LET THE Battle BEGIN! ~ Good luck & Have fun! ~" << endl;
		Battle(board_1_mirror, board_2_mirror, match, board_2, board_1);
	}
	//GAME PLAYER VS COMPUTER
	else {
		system("cls");
		cout << "\n\n";
		cout << "[SETTING FORMATION]\n" << endl;
		Displaying_board(board_1, match);
		Selecting_setup(match, board_1, match.player1);
		system("cls");
		Computer_setup(match2, board_2);
		system("cls");
		cout << "LET THE Battle BEGIN! ~ Good luck & Have fun! ~" << endl;
		Battle(board_1_mirror, board_2_mirror, match, board_2, board_1);
	}


	return 0;
}

//----[MAIN MENU FUNCTIONS]
match_config Main_menu(match_config &match) {
	//cout << "[1] PLAY\n[2] SETTINGS\n[3] COPYRIGHT\n[4] HELP\n[5] EXIT\n";
	ifstream Intro_image("menu_ascii.txt");
	string ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();

	int choice = 0;
	cin >> choice;
	switch (choice) {
	case 1: {
		system("cls");
		Main_menu_play(match);
	}break;
	case 2: {
		system("cls");
		Main_menu_settings(match);
	}break;
	case 3: {
		system("cls");
		Main_menu_copyright(match);
	}break;
	case 4: {
		system("cls");
		Main_menu_help(match);
	}break;
	case 5: {
		system("cls");
		Main_menu_exit(match);
	} break;
	default: {
		cout << "Unexpected choice!" << endl;
		Main_menu(match);
	}break;
	}
	return match;
}

match_config Main_menu_help(match_config &match) {
	cout << "      --HELP--\n" << endl;
	cout << "--- [BASIC INPUT] ---\n" << endl;
	cout << "[1],[2],[3],[n]  - Enter respectively 1,2,3 etc. value on your keyboard to choose that option " << endl;
	cout << "[ < ], [ > ] - Press [ < ]  LEFT ARROW or [ > ] RIGHT ARROW on keyboard to choose this option " << endl;
	cout << "\n\n\n\n [ < ] GO BACK     [ > ] GO NEXT\n";

	int choice_value = 0;
	Main_menu_choice(choice_value);
	do {
		switch (choice_value) {
		case -1: {
			system("cls");
			return Main_menu(match);
		}
		case 0: {
			system("cls");
			return Main_menu_help(match);
		}break;
		case 1: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [GENERAL RULES] --- " << endl;
			cout << "\n\n In first step You will have to set up Your formation of ships. After that the Battle begins. Your purpose is to destroy all enemy units." << endl;
			cout << "There is standard match and custom match. To learn more about it [ > ] GO NEXT ";
			cout << "\n\n [ < ] GO BACK     [ > ] GO NEXT\n";
			Main_menu_choice(choice_value);
			system("cls");
		}break;
		case 2: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [STANDARD MATCH RULES] ---" << endl;
			cout << "1. Players have 2 boards (10x10). Columns are marked by letters (from A to J) and digits (from 1 to 10). " << endl;
			cout << "2. On first board Player sets up his formation of ships. On the second board Game marks Player's shots." << endl;
			cout << "3. Ships can be set up as vertical or horizontal. " << endl;
			cout << "4. There must be at least one empty space betweeen each ship. " << endl;
			cout << "5. Each player has: 1 Large Ship, 2 Medium Ships and 3 Small Ships. " << endl;
			cout << "6. Shots are rendered by guessing enemy ship's position. (For example: C3 )" << endl;
			cout << "7. Each player has single shot" << endl;
			cout << "\n\n [ < ] GO BACK     [ > ] GO NEXT\n";
			Main_menu_choice(choice_value);
			system("cls");
		}break;
		case 3: {
			system("cls");
			cout << "      --HELP--\n" << endl;
			cout << "--- [CUSTOM MATCH RULES] ---" << endl;
			cout << "In custom match you are able to create new rules or edit the standard rules." << endl;
			cout << "For example You can choose that there won't be necessary empty space between ships (make point '4' from standard match useless) " << endl;
			cout << "You can even change the amount of ships, create new ships or change the boards' size " << endl;
			cout << "\n\n [ < ] GO BACK" << endl;
			Main_menu_choice(choice_value);
			system("cls");
		}break;
		case 4: {
			system("cls");
			return Main_menu_help(match);
		}break;
		}
	} while (choice_value != -1);
	return Main_menu(match);
}

match_config Main_menu_play(match_config &match) {
	//ASCII image
	ifstream Intro_image("match_choice_ascii.txt");
	string ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();
	//----
	int choice = 0;
	do {
		cin >> choice;
		if (choice == 1) {
			match.type = "standard";
		}
		else if (choice == 2) {
			match.type = "custom";
		}
		else {
			cout << "Unexpected choice! Please try again..." << endl;
		}
	} while (choice < 1 || choice > 2);
	//ASCII image
	system("cls");
	Intro_image.open("oponent_choice_ascii.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();
	//----
	choice = 0;
	do {
		cin >> choice;
		if (choice == 1) {
			match.oponent = "player";
			cout << "Please enter [Player 1] name: ";
			cin >> match.player1;
			cout << "\nPlease enter [Player 2] name: ";
			cin >> match.player2;
			cout << endl;
		}
		else if (choice == 2) {
			match.oponent = "computer";
			match.player2 = "Computer";
			cout << "Please enter [Player] name: ";
			cin >> match.player1;
			cout << "\nPlease select a difficulty: \n[1] Ultra Noob\n[2] Noob\n[3] Medium\n[4] Hard\n[5] Hardore\n[6] pow(Hardcore, lim_n where n -> infinity)\n";
			short difficulty;
			do {
				cin >> difficulty;
				if (difficulty < 1 || difficulty > 6)
					cout << "Please read again the difficulties..." << endl;
			} while (difficulty < 1 || difficulty > 6);
			switch (difficulty) {
				//setting computer's turn based on chosen difficulty
			case 1: match.computer_difficulty = 1; break;
			case 2: match.computer_difficulty = 2; break;
			case 3: match.computer_difficulty = 3; break;
			case 4: match.computer_difficulty = 5; break;
			case 5: match.computer_difficulty = 8; break;
			case 6: match.computer_difficulty = 9; break;
			}
		}
		else {
			cout << "Unexpected choice! Please try again..." << endl;
		}
	} while (choice < 1 || choice > 2);
	system("cls");
	if (match.type == "custom") {
		system("cls");
		Main_menu_play_custom(match);
	}
	//just removing one 'yeti' option with board formatting...
	if (match.board_size_x > 52)
		match.board_type_int = true;
	return match;
}

match_config Main_menu_settings(match_config &match) {
	cout << "   --SETTINGS-- \n" << endl;
	cout << "[1] Change shot sound\n[2] Change hit sound\n[3] Change miss sound\n\n\n[4] MAIN MENU" << endl;
	int choice = 0, sound_choice = 0;
	while (choice < 1 || choice > 4) {
		choice = 0;
		cin >> choice;
		switch (choice) {
		case 1: {
			system("cls");
			cout << "[1] - Default sound\n[2] - Sound #1\n[3] - Sound #2\n\n" << endl;
			sound_choice = 1;
			Main_menu_settings_sound(sound_choice, match, 300, "shot sound");
			Main_menu_settings(match);
		}break;
		case 2: {
			system("cls");
			cout << "[1] - Default sound\n[2] - Sound #1\n[3] - Sound #2\n\n" << endl;
			sound_choice = 2;
			Main_menu_settings_sound(sound_choice, match, 300, "hit sound");
			Main_menu_settings(match);

		}break;
		case 3: {
			system("cls");
			cout << "[1] - Default Sound\n[2] - Sound #1\n[3] - Sound #2\n\n" << endl;
			sound_choice = 3;
			Main_menu_settings_sound(sound_choice, match, 300, "miss sound");
			Main_menu_settings(match);
		}break;
		case 4: {
			system("cls");
			Main_menu(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	}
	return match;
}

match_config Main_menu_settings_sound(int &sound_choice, match_config &match, int value_1, string sound_name) {
	int duration_1 = 300, duration_2 = 400;
	int value_2 = 200;
	//Hit sound
	if (sound_choice == 2) {
		duration_1 = 600;
		value_1 += 40;
	}
	//Miss sound
	else if (sound_choice == 3) {
		duration_1 = 250;
		duration_2 = 200;
		value_1 += 50;
		value_2 += 25;
	}
	//Selecting a specific sound
	int second_sound_choice;
	do {
		cin >> second_sound_choice;
		if (second_sound_choice == 1) {
			system("cls");
			//Playing sound
			Beep(value_1, duration_1);
			if (sound_choice == 3) Beep(value_2, duration_2);
			cout << "//Default Sound has been set up as [" << sound_name << "] \n\n";
		}
		else if (second_sound_choice == 2) {
			system("cls");
			//Playing sound
			Beep(value_1 + 100, duration_1);
			if (sound_choice == 3) {
				Beep(value_2, duration_2);
				value_2 -= 40;
			}
			value_1 += 100;
			cout << "//Sound #1 has been set up as [" << sound_name << "] \n\n";
		}
		else if (second_sound_choice == 3) {
			system("cls");
			//Playing sound
			Beep(value_1 + 300, duration_1);
			if (sound_choice == 3) {
				Beep(value_2 + 150, duration_2);
				value_2 += 150;
			}
			value_1 += 300;
			cout << "//Sound #2 has been set up as [" << sound_name << "] \n\n";
		}
		else {
			cout << "Unexpected choice! Please try again..." << endl;
		}
	} while (sound_choice < 1 || sound_choice > 3);
	//Saving settings in match structure
	if (sound_name == "miss sound") {
		match.miss_tone_1 = value_1;
		match.miss_tone_2 = value_2;
		match.miss_duration_1 = duration_1;
		match.miss_duration_2 = duration_2;
	}
	else if (sound_name == "hit sound") {
		match.hit_tone = value_1;
		match.hit_duration = duration_1;
	}
	else if (sound_name == "shot sound") {
		match.shot_tone = value_1;
		match.shot_duration = duration_1;
	}
	return match;
}

match_config Main_menu_play_custom(match_config &match) {
	system("cls");
	cout << "You can change the game rules by selecting options below...\n\n[1] Ships section\n[2] Boards section\n[3] Ship Creator\n[4] Basic rules\n[5] APPLY CHANGES & EXIT\n" << endl;
	short choice;
	do {
		cin >> choice;
		switch (choice) {
		case 1: {
			system("cls");
			Main_menu_custom_ships(match);
		}break;
		case 2: {
			system("cls");
			Main_menu_custom_boards(match);
		}break;
		case 3: {
			system("cls");
			Main_menu_custom_ship_creator(match);
		}break;
		case 4: {
			system("cls");
			Main_menu_custom_basic_rules(match);
		}break;
		case 5: {
			return match;
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	} while (choice < 1 || choice > 5);
	return match;
}

match_config Main_menu_custom_ships(match_config &match) {
	short choice, second_choice;
	short max_choice = 4 + match.custom_ships_amount; //used to navigate to go back 
	do {
		system("cls");
		//ASCII image
		ifstream Intro_image("ships_section_ascii.txt");
		string ascii_picture = Displaying_picture_ascii(Intro_image);
		cout << ascii_picture << endl;
		Intro_image.close();
		//----
		cout << "\n\nSelect a specific ship to make some changes...\n\n";
		Displaying_ships(match);
		cin >> choice;
		if (choice > -1 && choice < 4) {
			switch (choice) {
			case 0: {
				cin >> choice;
			}break;
			case 1: {
				do {
					system("cls");
					cout << "[" << match.Battleship_name << "]\n";
					cout << "Ship size: " << match.Battleship_size << "\nAmount: " << match.Battleship_amount << endl;
					cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
					cin >> second_choice;
					switch (second_choice) {
					case 1: {
						cout << "Enter a value: ";
						cin >> match.Battleship_size;
						second_choice = 0;
					}break;
					case 2: {
						cout << "Enter a value: ";
						cin >> match.Battleship_amount;
						second_choice = 0;
					}break;
					case 3: {
						cout << "Enter a name: ";
						cin >> match.Battleship_name;
						second_choice = 0;
					}
					case 4: {
						choice = 0;
						break;
					}break;
					default: {
						cout << "Unexpected choice! Please try again..." << endl;
						Sleep(1000);
					}
					}
				} while (second_choice < 1 || second_choice > 4);
			}break;
			case 2: {
				do {
					system("cls");
					cout << "[" << match.cruiser_name << "]\n";
					cout << "Ship size: " << match.cruiser_size << "\nAmount: " << match.cruiser_amount << endl;
					cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
					cin >> second_choice;
					switch (second_choice) {
					case 1: {
						cout << "Enter a value: ";
						cin >> match.cruiser_size;
						second_choice = 0;
					}break;
					case 2: {
						cout << "Enter a value: ";
						cin >> match.cruiser_amount;
						second_choice = 0;
					}break;
					case 3: {
						cout << "Enter a name: ";
						cin >> match.cruiser_name;
						second_choice = 0;
					}
					case 4: {
						choice = 0;
						break;
					}break;
					default: {
						cout << "Unexpected choice! Please try again..." << endl;
						Sleep(1000);
					}
					}
				} while (second_choice < 1 || second_choice > 4);
			}break;
			case 3: {
				do {
					system("cls");
					cout << "[" << match.destroyer_name << "]\n";
					cout << "Ship size: " << match.destroyer_size << "\nAmount: " << match.destroyer_amount << endl;
					cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
					cin >> second_choice;
					switch (second_choice) {
					case 1: {
						cout << "Enter a value: ";
						cin >> match.destroyer_size;
						second_choice = 0;
					}break;
					case 2: {
						cout << "Enter a value: ";
						cin >> match.destroyer_amount;
						second_choice = 0;
					}break;
					case 3: {
						cout << "Enter a name: ";
						cin >> match.destroyer_name;
						second_choice = 0;
					}
					case 4: {
						choice = 0;
						break;
					}break;
					default: {
						cout << "Unexpected choice! Please try again..." << endl;
						Sleep(1000);
					}
					}
				} while (second_choice < 1 || second_choice > 4);
			}break;
			default: {
				cout << "Unexpected choice! Please try again..." << endl;
				Sleep(2000);
				system("cls");
			}break;
			}
		}
		else if (choice == max_choice)
			return Main_menu_play_custom(match);
		else if (choice > max_choice) {
			cout << "Unexpected choice! Please try again..." << endl;
			Sleep(1000);
			return Main_menu_custom_ships(match);
		}
		else {
			choice = choice - 4;
			do {
				system("cls");
				cout << "[" << match.custom_ship_main[choice][0].name << "]\n";
				cout << "Ship size: " << match.custom_ship_main[choice][0].size << "\nAmount: " << match.custom_ship_main[choice][0].amount << endl;
				cout << "\n[1] Change ship size\n[2] Change amount of this ship\n[3] Change the name\n\n[4] GO BACK" << endl;
				cin >> second_choice;
				switch (second_choice) {
				case 1: {
					cout << "Enter a value: ";
					cin >> match.custom_ship_main[choice][0].size;
					Custom_ship_update(match.custom_ship_main, choice);
					second_choice = 0;
				}break;
				case 2: {
					cout << "Enter a value: ";
					cin >> match.custom_ship_main[choice][0].amount;
					Custom_ship_update(match.custom_ship_main, choice);
					second_choice = 0;
				}break;
				case 3: {
					cout << "Enter a name: ";
					cin >> match.custom_ship_main[choice][0].name;
					Custom_ship_update(match.custom_ship_main, choice);
					second_choice = 0;
				}
				case 4: {
					choice = 0;
					break;
				}break;
				default: {
					cout << "Unexpected choice! Please try again..." << endl;
					Sleep(1000);
				}
				}
			} while (second_choice < 1 || second_choice > 4);
		}
	} while (choice < 1 || choice > 3);
	return match;
}

match_config Main_menu_custom_ship_creator(match_config &match) {
	ifstream Intro_image("ship_creator_ascii.txt");
	string ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Intro_image.close();

	cout << "\n\n[1] Create a new ship\n\n[2] GO BACK\n";
	int choice;
	string ship_name;
	int ship_size, ship_amount;
	do {
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Enter a ship name: ";
			cin >> ship_name;
			cout << "Enter a size of this ship: ";
			cin >> ship_size;
			cout << "Enter an amount of this ship: ";
			cin >> ship_amount;
			match.custom_ships_amount++;
		}break;
		case 2: {
			return Main_menu_play_custom(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	} while (choice < 1 || choice > 2);
	Generating_ship(ship(), match.custom_ship, match, ship_amount, ship_size, ship_name);
	match.custom_ship_main.push_back(match.custom_ship);
	match.custom_ship.clear();
	return Main_menu_play_custom(match);
}

match_config Main_menu_custom_boards(match_config &match) {

	short choice;

	do {
		ifstream Intro_image("boards_section_ascii.txt");
		string ascii_picture = Displaying_picture_ascii(Intro_image);
		cout << ascii_picture << endl;
		Intro_image.close();
		cout << "\n\nBoard dimensions:\nvertical: " << match.board_size_y << " horizontal: " << match.board_size_x << endl;
		cout << "\n[1] Change dimensions\n[2] GO BACK\n" << endl;
		cin >> choice;
		switch (choice) {
		case 0: {

		}break;
		case 1: {
			cout << "Enter vertical dimension: ";
			cin >> match.board_size_y;
			cout << "\nEnter horizontal dimension: ";
			cin >> match.board_size_x;
			system("cls");
			choice = 0;
		}break;
		case 2: {
			return Main_menu_play_custom(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
			Sleep(2000);
			system("cls");
		}break;
		}
	} while (choice < 1 || choice > 2);
	return match;
}

match_config Main_menu_custom_basic_rules(match_config &match) {
	cout << "[1] Ships beside (4th standard match rule)";
	if (match.ships_beside == false)
		cout << " [FALSE]\n";
	else cout << " [TRUE]\n";
	cout << "[2] Cross setting";
	if (match.cross_setting == false)
		cout << " [FALSE]\n";
	else cout << " [TRUE]\n";
	cout << "[3] Board int display";
	if (match.board_type_int == false)
		cout << " [FALSE]\n";
	else cout << " [TRUE]\n";
	cout << "[4] GO BACK\n";
	short choice;
	do {
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "//Now there not be necessary to leave 1 empty space between each ship" << endl;
			if (match.ships_beside == false)
				match.ships_beside = true;
			else match.ships_beside = false;
			Sleep(1000);
		}break;
		case 2: {
			cout << "//Now You will be able to set ships as cross pose" << endl;
			if (match.cross_setting == false)
				match.cross_setting = true;
			else match.cross_setting = false;
			Sleep(1000);
		}break;
		case 3: {
			cout << "//Now board coordinates will be presented as int values.\n[WARNING!] If board horizontal dimension is greater than 52 ";
			cout << "this option will be AUTOMATICLY set to [FALSE]" << endl;
			if (match.board_type_int == false)
				match.board_type_int = true;
			else match.board_type_int = false;
			Sleep(3000);
		}
		case 4: {
			return Main_menu_play_custom(match);
		}break;
		default: {
			cout << "Unexpected choice! Please try again..." << endl;
		}break;
		}
	} while (choice < 1 || choice > 4);
	return Main_menu_play_custom(match);
}

int Main_menu_choice(int &choice_value) {
	char key = _getch(); //_getch() read the key value from keyboard without displaying it.
	int choice = key;
	//inifinite loop
	while (1) {
		switch (choice) {
		case KEY_RIGHT: {
			choice_value++;
			return choice_value;
		}break;
		case KEY_LEFT: {
			choice_value--;
			return choice_value;
		} break;
		}
		key = _getch();
		choice = key;
	}
}

void Main_menu_copyright(match_config &match) {
	cout << "    --COPYRIGHT--\n" << endl;
	cout << "SHIP WARS THE FIRST" << endl;
	cout << "Creators: Szymon Buksak and Mikolaj Herzberg" << endl;
	cout << "\nThis game is on Public Copyright License." << endl;
	cout << "Project started in [28-12-2018] " << endl;
	cout << "\n\n\n\n [ < ] GO BACK TO MAIN MENU";

	int choice_value = 0;
	Main_menu_choice(choice_value);
	while (choice_value != -1) {
		choice_value = 0;
		Main_menu_choice(choice_value);
	}
	if (choice_value == -1) {
		system("cls");
		Main_menu(match);
	}
}

void Main_menu_exit(match_config &match) {
	//ASCII image
	ifstream Intro_image("exit_ascii.txt");
	string ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(2000);
	Intro_image.close();
	//----
	int choice_value = 0;
	Main_menu_choice(choice_value);

	if (choice_value == -1) {
		system("cls");
		Main_menu(match);
	}
	else {
		system("cls");
		cout << "Thanks for playing!" << endl;
		exit(1);
	}
}

//----[GENERATING FUNCTIONS]
vector <ship> Generating_ship(struct ship ship_struct, vector <ship> &custom_ship, match_config &match, short ship_amount, short ship_size, string ship_name) {
	for (int i = 0; i < ship_amount; i++) {
		custom_ship.push_back(ship_struct);
		custom_ship[i].size = ship_size;
		custom_ship[i].amount = ship_amount;
		custom_ship[i].name = ship_name;
		//[DEBUG] for tests only!
		//cout << "Ship [" << i << "] size: " << custom_ship[i].size << endl;
	}
	return custom_ship;
}

vector <vector<short>> Generating_board(vector <vector<short>> &board, match_config &match) {
	vector <short> board_fill; //used temporarily to initialize the board
	for (int i = 0; i < match.board_size_x + 2; i++) {
		board_fill.push_back(0);
	}
	for (int j = 0; j < match.board_size_y + 2; j++) {
		board.push_back(board_fill);
	}
	return board;
}

vector <vector<short>> Computer_shooting(vector <vector<short>> &computer_board_mirror, vector <vector<short>> &computer_board, vector <vector<short>> &oponent_board, match_config &match) {
	int cord_x, cord_y;
	cord_x = rand() % match.board_size_x + 1;
	cord_y = rand() % match.board_size_y + 1;
	//shot
	Beep(match.shot_tone, match.shot_duration);
	switch (oponent_board[cord_y][cord_x]) {
	case 0: {
		//miss
		Beep(match.miss_tone_1, match.miss_duration_1);
		Beep(match.miss_tone_2, match.miss_duration_2);
		computer_board_mirror[cord_y][cord_x] = 2;
	}break;
	case 1: {
		//hit
		Beep(match.hit_tone, match.hit_duration);
		computer_board_mirror[cord_y][cord_x] = 3;
		oponent_board[cord_y][cord_x] = 3;
	}break;
	case 3: {
		cout << "Computer shot drowned part of ship..." << endl;
	}break;
	}
	Displaying_board(computer_board_mirror, match);
	return computer_board_mirror;
}

vector <vector<short>> Computer_setup(match_config &match, vector <vector<short>> &board) {
	int cord_x, cord_y, position;
	string positions[3] = { "vertical","horizontal","cross" };
	//Battleship draw
	for (int i = 0; i < match.Battleship[0].amount; i++) {
		do {
			cord_x = rand() % match.board_size_x + 1;
			cord_y = rand() % match.board_size_y + 1;
			if (match.cross_setting == false) {
				position = rand() % 2;
				match.Battleship[i].position = positions[position];
			}
			else {
				position = rand() % 3;
				match.Battleship[i].position = positions[position];
			}
		} while (Board_collision(board, cord_x, cord_y, match.Battleship, i, match));
		Board_set(board, cord_x, cord_y, match.Battleship, i);
	}//Cruiser draw
	for (int i = 0; i < match.cruiser[0].amount; i++) {
		do {
			cord_x = rand() % match.board_size_x + 1;
			cord_y = rand() % match.board_size_y + 1;
			if (match.cross_setting == false) {
				position = rand() % 2;
				match.cruiser[i].position = positions[position];
			}
			else {
				position = rand() % 3;
				match.cruiser[i].position = positions[position];
			}
		} while (Board_collision(board, cord_x, cord_y, match.cruiser, i, match));
		Board_set(board, cord_x, cord_y, match.cruiser, i);
	}//Destroyer draw
	for (int i = 0; i < match.destroyer[0].amount; i++) {
		do {
			cord_x = rand() % match.board_size_x + 1;
			cord_y = rand() % match.board_size_y + 1;
			if (match.cross_setting == false) {
				position = rand() % 2;
				match.destroyer[i].position = positions[position];
			}
			else {
				position = rand() % 3;
				match.destroyer[i].position = positions[position];
			}
		} while (Board_collision(board, cord_x, cord_y, match.destroyer, i, match));
		Board_set(board, cord_x, cord_y, match.destroyer, i);
	}//Custom ships draw
	for (int i = 0; i < match.custom_ships_amount; i++) {
		for (int j = 0; j < match.custom_ship_main[i][0].amount; j++) {
			do {
				cord_x = rand() % match.board_size_x + 1;
				cord_y = rand() % match.board_size_y + 1;
				if (match.cross_setting == false) {
					position = rand() % 2;
					match.custom_ship_main[i][j].position = positions[position];
				}
				else {
					position = rand() % 3;
					match.custom_ship_main[i][j].position = positions[position];
				}
			} while (Board_collision(board, cord_x, cord_y, match.custom_ship_main[i], j, match));
			Board_set(board, cord_x, cord_y, match.custom_ship_main[i], j);
		}
	}
	return board;
}


//----[DISPLAYING FUNCTIONS]
string Displaying_picture_ascii(ifstream &ascii_picture) {
	string lines = "";
	if (ascii_picture) {
		while (ascii_picture.good()) {
			string templine;
			getline(ascii_picture, templine);
			templine += "\n";
			lines = lines + templine;
		}
		return lines;
	}
	else
	{
		return "ASCII image is missing...";
	}
}

void Game_intro() {
	system("pause");
	ifstream Intro_image("intro_ascii_1.txt");
	string ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(2000);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_2.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_3.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_1.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(1000);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_2.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_3.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(500);
	Intro_image.close();
	system("cls");

	Intro_image.open("intro_ascii_end.txt");
	ascii_picture = Displaying_picture_ascii(Intro_image);
	cout << ascii_picture << endl;
	Sleep(1500);
	Intro_image.close();
	system("cls");
}

void Displaying_ships(match_config &match) {
	for (int i = 0; i < 3 + match.custom_ships_amount; i++) {
		cout << "[" << i + 1 << "] ";
		switch (i) {
		case 0: {
			cout << match.Battleship_name << endl;
		}break;
		case 1: {
			cout << match.cruiser_name << endl;
		}break;
		case 2: {
			cout << match.destroyer_name << endl;
		}break;
		default: {
			cout << match.custom_ship_main[i - 3][0].name << endl;
		}break;
		}
	}
	cout << "[" << 4 + match.custom_ships_amount << "]" << " GO BACK" << endl;
}

void Displaying_board(vector <vector <short>> &board, match_config match) {
	//board size x < 52 -> displaying A - x on board where x is the last char of board_X dimension
	short formatting_value = 0;
	short formatting_value_x = 0, formatting_value_y = 0;
	formatting_value_x += short(log10(board[0].size() - 1));
	formatting_value_y += short(log10(board.size() - 1));
	formatting_value = formatting_value_x + formatting_value_y;
	short form_temp, form_temp_x;
	form_temp = formatting_value;
	if (formatting_value % 2 == 0) {
		form_temp *= 2;
	}
	else {
		form_temp_x = form_temp + 1;
	}

	//[DEBUG] for tests only!
	/*cout << "FORMATTING VALUE: " << formatting_value << endl;
	cout << "Formatting x value: " << formatting_value_x << endl;
	cout << "Formatting y value: " << formatting_value_y << "\n\n\n\n\n";*/

	if (formatting_value_y < formatting_value_x)
		for (int i = 0; i <= form_temp_x; i++)
			cout << " ";
	else if (formatting_value_x < formatting_value_y)
		for (int i = 0; i <= form_temp_x; i++)
			cout << " ";
	else
		for (int i = 0; i < form_temp; i++)
			cout << " ";
	//using size_t to solve mismatch warning
	if (board[0].size() - 2 <= 52 && match.board_type_int == false) {
		for (size_t i = 0; i < board[0].size() - 2; i++) {
			if (i < 26) {
				cout << char(65 + i);
				if (formatting_value_x != 0)
					cout << "  ";
			}
			else {
				cout << char(71 + i);
				if (formatting_value_x != 0)
					cout << "  ";
			}
		}
		cout << endl;
	}
	else if (board[0].size() - 2 <= 52 && match.board_type_int == true) {
		for (size_t i = 0; i < board[0].size() - 2; i++) {
			cout << i + 1;
			if (formatting_value_x != 0)
				cout << "  ";
		}
		cout << endl;
	}
	else {
		//board size x > 52 -> displaying 1 - x on board where x is the last value of board_X dimension
		for (size_t i = 0; i < board[0].size() - 2; i++) {
			cout << i + 1;
			if (formatting_value_x != 0)
				cout << "  ";
		}
		cout << endl;
	}
	//main display
	for (size_t i = 0; i < board.size() - 2; i++) {
		//formatting vertical 
		for (int i = 0; i < formatting_value; i++)
			cout << " ";
		if (log10(i + 1) >= 1)
			for (int format_y = 0; format_y < int(log10(i + 1)); format_y++)
				cout << "\b";
		cout << i + 1 << "|";
		for (size_t j = 0; j < board[0].size() - 2; j++) {
			//formatting horizontal
			if (j != 0) {
				for (int format_y = 0; format_y < formatting_value_x * 2; format_y++)
					cout << " ";
			}
			if (log10(j + 1) >= 1 && match.board_type_int == true)
				for (int format_y = 0; format_y < int(log10(j + 1)); format_y++)
					cout << " ";
			//there is no any ship
			if (board[i + 1][j + 1] == 0) {
				if (formatting_value_x != 0 && formatting_value_x > 1) {
					for (int format_y = 0; format_y < formatting_value_x; format_y++)
						cout << " ";
				}
				cout << "*";
			}
			//there is a ship
			else if (board[i + 1][j + 1] == 1)
				cout << char(254);
			//missed
			else if (board[i + 1][j + 1] == 2)
				cout << "-";
			//destroyed
			else if (board[i + 1][j + 1] == 3)
				cout << "X";
		}
		cout << endl;
	}
}

//----[PLAY FUNCTIONS]
vector <ship> Setting_ship(vector <ship> &custom_ship, match_config &match, vector <vector<short>> &board, short &current_ship, string player_name) {
	int choice;
	int cord_y;
	int cord_x = 0;


	//setting positon (vertical or horizontal)
	do {
		cout << "[" << player_name << " turn]" << endl;
		cout << "Select position:\n[1] Vertical\n[2] Horizontal\n";
		if (match.cross_setting == true)
			cout << "[3] Cross\n";
		do {
			cin >> choice;
			if (choice == 1) {
				custom_ship[current_ship].position = "vertical";
			}
			else if (choice == 2) {
				custom_ship[current_ship].position = "horizontal";
			}
			else if (match.cross_setting == true && choice == 3) {
				custom_ship[current_ship].position = "cross";
			}
			else {
				cout << "Unexpected choice! Please try again..." << endl;
			}
		} while ((choice < 1 || choice > 2) && (match.cross_setting == false || (choice < 1 || choice > 3)));
		Setting_coordinates(cord_y, cord_x, match);
	} while (Board_collision(board, cord_x, cord_y, custom_ship, current_ship, match) == true);
	Board_set(board, cord_x, cord_y, custom_ship, current_ship);
	Displaying_board(board, match);
	return custom_ship;
}

vector <vector<short>> Selecting_setup(match_config &match, vector <vector<short>> &board, string player_name) {
	size_t all_ships_amount = Ship_counting(match);
	short custom_ship_order = 0;
	int choice;

	do {
		cout << "\n\n[" << player_name << " turn]" << endl;
		cout << "Select a following ship to set up the formation: " << endl;
		for (int i = 0; i < 3 + match.custom_ships_amount; i++) {
			cout << "[" << i + 1 << "] ";
			switch (i) {
			case 0: {
				cout << match.Battleship_name << "[Available: " << match.Battleship[0].amount << "]" << endl;
			}break;
			case 1: {
				cout << match.cruiser_name << "[Available: " << match.cruiser[0].amount << "]" << endl;
			}break;
			case 2: {
				cout << match.destroyer_name << "[Available: " << match.destroyer[0].amount << "]" << endl;
			}break;
			default: {
				cout << match.custom_ship_main[custom_ship_order][0].name;
				cout << "[Available: " << match.custom_ship_main[custom_ship_order][0].amount << "]" << endl;
				custom_ship_order++;
			}break;
			}
		}
		cin >> choice;
		switch (choice) {
		case 1: {
			if (match.Battleship[0].amount != 0) {
				Setting_ship(match.Battleship, match, board, match.Battleship[0].setting_order, player_name);
				match.Battleship[0].setting_order++;
				match.Battleship[0].amount--;
				all_ships_amount--;
			}
			else cout << "You have already set all ships of this type... Please select another ship." << endl;
		}break;
		case 2: {
			if (match.cruiser[0].amount != 0) {
				Setting_ship(match.cruiser, match, board, match.cruiser[0].setting_order, player_name);
				match.cruiser[0].setting_order++;
				match.cruiser[0].amount--;
				all_ships_amount--;
			}
			else cout << "You have already set all ships of this type... Please select another ship." << endl;
		}break;
		case 3: {
			if (match.destroyer[0].amount != 0) {
				Setting_ship(match.destroyer, match, board, match.destroyer[0].setting_order, player_name);
				match.destroyer[0].setting_order++;
				match.destroyer[0].amount--;
				all_ships_amount--;
			}
			else cout << "You have already set all ships of this type... Please select another ship." << endl;
		}break;
		default: {
			if (choice < 1 || choice > 3 + match.custom_ships_amount) {
				cout << "Unexpected choice! Please try again...";
				break;
			}
			else {
				choice = choice - 4;
				if (match.custom_ship_main[choice][0].amount != 0) {
					Setting_ship(match.custom_ship_main[choice], match, board, match.custom_ship_main[choice][0].setting_order, player_name);
					match.custom_ship_main[choice][0].setting_order++;
					match.custom_ship_main[choice][0].amount--;
					all_ships_amount--;
				}
				else cout << "You have already set all ships of this type... Please select another ship." << endl;
			}
		}break;
		}custom_ship_order = 0; //resetting value
	} while ((choice < 1 || choice > 3 + match.custom_ships_amount) || all_ships_amount != 0);
	return board;
}

vector <vector<short>> Board_set(vector <vector<short>> &board, int cord_x, int cord_y, vector <ship> custom_ship, short current_ship) {
	if (custom_ship[current_ship].position == "vertical") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			board[cord_y + i][cord_x] = 1;
		}
	}
	else if (custom_ship[current_ship].position == "horizontal") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			board[cord_y][cord_x + i] = 1;
		}
	}
	else if (custom_ship[current_ship].position == "cross") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (i != 0)
				board[cord_y + i][cord_x + i] = 1;
			else
				board[cord_y][cord_x] = 1;
		}
	}
	return board;
}

vector <vector<short>> Player_shooting(vector <vector<short>> &player_board_mirror, match_config &match, vector <vector<short>> &oponent_board, string player_name) {
	cout << "\n\n[" << player_name << " turn]" << endl;
	int cord_x, cord_y;
	Setting_coordinates(cord_y, cord_x, match);
	//shot
	Beep(match.shot_tone, match.shot_duration);
	switch (oponent_board[cord_y][cord_x]) {
	case 0: {
		//miss
		Beep(match.miss_tone_1, match.miss_duration_1);
		Beep(match.miss_tone_2, match.miss_duration_2);
		player_board_mirror[cord_y][cord_x] = 2;
	}break;
	case 1: {
		//hit
		Beep(match.hit_tone, match.hit_duration);
		player_board_mirror[cord_y][cord_x] = 3;
		oponent_board[cord_y][cord_x] = 3;
	}break;
	case 3: {
		cout << "Congratulation! You have shot a drowned part of oponent's ship" << endl;
	}break;
	}
	Displaying_board(player_board_mirror, match);
	return player_board_mirror;
}

vector <vector<short>> Battle(vector <vector<short>> &player_board_mirror, vector <vector<short>> &oponent_board_mirror, match_config &match, vector <vector<short>> &oponent_board, vector <vector<short>> &player_board)
{
	do {
		Player_shooting(player_board_mirror, match, oponent_board, match.player1);
		if (Board_is_empty(oponent_board) == true) {
			match.winner = match.player1;
			Game_results(match);
			match.turn++;
			break;
		}
		if (match.oponent == "player") {
			Player_shooting(oponent_board_mirror, match, player_board, match.player2);
			if (Board_is_empty(player_board) == true) {
				match.winner = match.player2;
				Game_results(match);
				match.turn++;
				break;
			}
		}
		else if (match.oponent == "computer") {
			cout << "\n\n[COMPUTER'S TURN]\n" << endl;
			system("pause");
			for (int i = 0; i < match.computer_difficulty; i++)
				Computer_shooting(oponent_board_mirror, oponent_board, player_board, match);
			if (match.computer_difficulty > 8) match.computer_difficulty++; //[6] Difficulty  addon
			if (Board_is_empty(player_board) == true) {
				match.winner = match.player2;
				Game_results(match);
				match.turn++;
				break;
			}
		}
		match.turn++;
	} while (Board_is_empty(player_board) != true && Board_is_empty(oponent_board) != true);
	return player_board;
}

bool Board_is_empty(vector <vector<short>> board) {
	for (size_t i = 0; i < board.size() - 2; i++) {
		for (size_t j = 0; j < board[0].size() - 2; j++) {
			if (board[i + 1][j + 1] != 0 && board[i + 1][j + 1] != 3)
				return false;
		}
	}
	return true;
}

bool Board_collision(vector <vector<short>> &board, int cord_x, int cord_y, vector <ship> custom_ship, short current_ship, match_config match) {
	if (custom_ship[current_ship].position == "vertical") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (board[cord_y + i][cord_x] == 1)
			{
				cout << "Ooops! There would be a collision. Please try again..." << endl;
				return true;
			}
			if ((cord_y - 1) + custom_ship[current_ship].size > match.board_size_y) {
				cout << "This place is out of range! Please try again..." << endl;
				return true;
			}
		}
	}
	else if (custom_ship[current_ship].position == "horizontal") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (board[cord_y][cord_x + i] == 1)
			{
				cout << "Ooops! There would be a collision. Please try again..." << endl;
				return true;
			}
			if ((cord_x - 1) + custom_ship[current_ship].size > match.board_size_x) {
				cout << "This place is out of range! Please try again..." << endl;
				return true;
			}
		}
	}
	else if (custom_ship[current_ship].position == "cross") {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (board[cord_y + i][cord_x + i] == 1) {
				cout << "Ooops! There would be a collision. Please try again..." << endl;
				return true;
			}
			if (((cord_y - 1) + custom_ship[current_ship].size > match.board_size_y) || ((cord_x - 1) + custom_ship[current_ship].size > match.board_size_x)) {
				cout << "This place is out of range! Please try again..." << endl;
				return true;
			}
		}
	}
	//2=0 for new board!
	if (match.ships_beside == false) {
		for (int i = 0; i < custom_ship[current_ship].size; i++) {
			if (board[cord_y - 1][cord_x] == 1 || board[cord_y + 1][cord_x] == 1 || board[cord_y][cord_x + 1] == 1 || board[cord_y][cord_x - 1] == 1)
			{
				cout << "There must be 1 empty space between each ship!" << endl;
				return true;
			}
			if (custom_ship[current_ship].position == "vertical") {
				if (board[cord_y + i][cord_x + 1] == 1 || board[cord_y + i][cord_x - 1] == 1 || board[cord_y + custom_ship[current_ship].size][cord_x] == 1)
				{
					cout << "There must be 1 empty space between each ship!" << endl;
					return true;
				}
			}
			else if (custom_ship[current_ship].position == "horizontal") {
				if (board[cord_y + 1][cord_x + i] == 1 || board[cord_y - 1][cord_x + i] == 1 || board[cord_y][cord_x + custom_ship[current_ship].size] == 1) {
					cout << "There must be 1 empty space between each ship!" << endl;
					return true;
				}

			}
			else if (custom_ship[current_ship].position == "cross") {
				if (board[cord_y + custom_ship[current_ship].size][cord_x + custom_ship[current_ship].size] == 1) {
					cout << "There must be 1 empty space between each ship!" << endl;
					return true;
				}
				if (board[cord_y + i + 1][cord_x + i] == 1 || board[cord_y + i - 1][cord_x + i] == 1 || board[cord_y + i][cord_x + i + 1] == 1 || board[cord_y + i][cord_x + i - 1] == 1) {
					cout << "There must be 1 empty space between each ship!" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

int Setting_coordinates(int &cord_y, int &cord_x, match_config &match) {
	int cord_y_local;
	char cord_x_local = 0;
	short ending_x = 0;
	if (match.board_size_x <= 26)
		ending_x = -1;
	else ending_x = 5;

	//setting horizontal coordinates A-x 
	if (match.board_size_x <= 52 && match.board_type_int == false) {
		do {
			cout << "Enter horizontal coordinate from: A to " << char(int('A') + match.board_size_x + ending_x) << endl;
			cin >> cord_x_local;
			if (int(cord_x_local) < int('A') || (int(cord_x_local) > int(char('A') + match.board_size_x + ending_x)) || (int(cord_x_local) >= 91 && int(cord_x_local) < 97))
				cout << "The cord is out of range! Please try again..." << endl;
		} while (int(cord_x_local) < int('A') || (int(cord_x_local) > int(char('A') + match.board_size_x + ending_x)) || (int(cord_x_local) >= 91 && int(cord_x_local) < 97));
		//correcting cord_x value
		if (cord_x_local < 97)
			cord_x_local = cord_x_local - 65;
		else cord_x_local = cord_x_local - 71;
		cord_x = int(cord_x_local);
	}
	//setting horizontal coordinates 1-x
	else {
		do {
			cout << "Enter horizontal coordinate from: 1 to " << match.board_size_x << endl;
			cin >> cord_x;
			if (cord_x < 1 || cord_x > match.board_size_x)
				cout << "The cord is out of range! Please try again..." << endl;
		} while (cord_x < 1 || cord_x > match.board_size_x);
		cord_x -= 1;
	}
	do {
		cout << "Enter vertical coordinate from: 1 to " << match.board_size_y << endl;
		cin >> cord_y_local;
		if (cord_y_local < 1 || cord_y_local > match.board_size_y)
			cout << "The cord is out of range! Please try again..." << endl;
	} while (cord_y_local < 1 || cord_y_local > match.board_size_y);
	//correcting cord_y value
	cord_y_local -= 1;
	cord_y = cord_y_local;
	//correcting cords value [new board dimensions]
	cord_y += 1;
	cord_x += 1;

	return cord_y, cord_x;
}

//----[HELP FUNCTIONS]
vector <vector<ship>> Custom_ship_update(vector <vector<ship>> &custom_ship, int ship_type) {
	//Setting basic parameters(size,amount,name) of every ship as the first one
	int general_size;
	int general_amount;
	string general_name;

	general_size = custom_ship[ship_type][0].size;
	general_amount = custom_ship[ship_type][0].amount;
	general_name = custom_ship[ship_type][0].name;

	for (size_t i = 0; i < custom_ship[ship_type].size(); i++) {
		custom_ship[ship_type][i].size = general_size;
		custom_ship[ship_type][i].amount = general_amount;
		custom_ship[ship_type][i].name = general_name;
	}
	return custom_ship;
}

size_t Ship_counting(match_config &match) {
	size_t all_custom_ships = 0;
	size_t all_ships = 0;
	for (size_t i = 0; i < match.custom_ships_amount; i++) {
		all_custom_ships += match.custom_ship_main[i][0].amount;
	}
	all_ships = all_custom_ships + match.Battleship.size() + match.cruiser.size() + match.destroyer.size();
	return all_ships;
}

void Game_results(match_config &match) {
	system("cls");
	cout << "Congratulation!!!\nPlayer: " << match.winner << " won!" << endl;
	cout << "[RESULTS]: \n\n";
	cout << "Turns played: " << match.turn << endl;
	system("pause");
}