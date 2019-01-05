#include <iostream>
#include <string>
#include <cstdlib>
//#include <unistd.h>

using namespace std;

//void clear_screen();
//void sleep_screen();
void create_battleship(int tryb_gry, string sprawdzenie, string player, int wybor, int rzad, int kolumna, int board[10][10], bool flaga);
void create_cruiser(int tryb_gry, string sprawdzenie, string player, int wybor, int rzad, int kolumna, int board[10][10], bool flaga);
void create_destroyer(int tryb_gry, string sprawdzenie, string player, int wybor, int rzad, int kolumna, int board[10][10], bool flaga);
void print_board(int board_1[10][10]);
void print_board_while_setting(int board_1[10][10]);
void shoot(int tryb_gry, string sprawdzenie, string player, int row, int colum, int ile_statkow_gracza, int board_1[10][10], int ilosc_trafien_gracza);
int menu_game_mod(int &tryb_gry);

int main()
{
    srand(time(NULL));

    int board_1[10][10] = //plansza gracza nr 1.
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };
    int board_2[10][10] = //plansza gracza nr 2.
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        };

    int row_shoot;
    int column_shoot;
    int row;
    int column;
    int how_many_ships_player_1 = 16;
    int how_many_ships_player_2 = 16;
    int hits_player_1 = 0;
    int hits_player_2 = 0;
    int choice = rand() % 2 + 1;
    bool flag = false;
    int game_mod = 0;

    string player_1 = "szymek";
    string player_2 = "miki";
    string check = player_2;

    print_board(board_1);
    menu_game_mod(game_mod);
    create_battleship(game_mod, check, player_1, choice, row, column, board_1, flag);
    system("cls");
    print_board_while_setting(board_1);
    create_cruiser(game_mod, check, player_1, choice, row, column, board_1, flag);
    system("cls");
    print_board_while_setting(board_1);
    create_destroyer(game_mod, check, player_1, choice, row, column, board_1, flag);
    system("cls");
    print_board(board_2);
    create_battleship(game_mod, check, player_2, choice, row, column, board_2, flag);
    system("cls");
    print_board_while_setting(board_2);
    create_cruiser(game_mod, check, player_2, choice, row, column, board_2, flag);
    system("cls");
    print_board_while_setting(board_2);
    create_destroyer(game_mod, check, player_2, choice, row, column, board_2, flag);
    system("cls");

    while ((how_many_ships_player_1 > 0) || (how_many_ships_player_2 > 0))
    {
        print_board(board_1);
        shoot(game_mod, check, player_2, row_shoot, column_shoot, how_many_ships_player_1, board_1, hits_player_2);
        Sleep(3000);
        system("cls");
        print_board(board_2);
        shoot(game_mod, check, player_1, row_shoot, column_shoot, how_many_ships_player_2, board_2, hits_player_1);
        Sleep(3000);
        system("cls");
    }

    return 0;
}

void print_board_while_setting(int board_1[10][10])
{
    char kol = 65;
    cout << " ";
    for (int i = 0; i < 10; i++)
    {
        cout << " " << kol;
        kol++;
    }

    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        if (i == 9)
        {
            cout << i + 1;
            for (int j = 0; j < 10; j++)
            {
                if (board_1[i][j] == 1)
                {
                    cout << "+ ";
                }
                else if (board_1[i][j] == 0)
                {
                    cout << "* ";
                }
            }
            cout << endl;
        }
        else
        {
            cout << i + 1 << " ";
            for (int j = 0; j < 10; j++)
            {
                if (board_1[i][j] == 1)
                {
                    cout << "+ ";
                }
                else if (board_1[i][j] == 0)
                {
                    cout << "* ";
                }
            }
            cout << endl;
        }
    }
}

void print_board(int board_1[10][10])
{
    char kol = 65;
    cout << " ";
    for (int i = 0; i < 10; i++)
    {
        cout << " " << kol;
        kol++;
    }

    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        if (i == 9)
        {
            cout << i + 1;
            for (int j = 0; j < 10; j++)
            {
                if (board_1[i][j] == 1)
                {
                    cout << "* ";
                }
                else if (board_1[i][j] == 0)
                {
                    cout << "* ";
                }
                else if (board_1[i][j] == 2)
                {
                    cout << "+ ";
                }
                else if (board_1[i][j] == 3)
                {
                    cout << "- ";
                }
            }
            cout << endl;
        }
        else
        {
            cout << i + 1 << " ";
            for (int j = 0; j < 10; j++)
            {
                if (board_1[i][j] == 1)
                {
                    cout << "* ";
                }
                else if (board_1[i][j] == 0)
                {
                    cout << "* ";
                }
                else if (board_1[i][j] == 2)
                {
                    cout << "+ ";
                }
                else if (board_1[i][j] == 3)
                {
                    cout << "- ";
                }
            }
            cout << endl;
        }
    }
}

void create_battleship(int tryb_gry, string sprawdzenie, string player, int wybor, int rzad, int kolumna, int board[10][10], bool flaga)
{

    if ((tryb_gry == 1) || (player == sprawdzenie))
    {
        cout << "Ustawienie czteromasztowca gracza " << player << ":" << endl;
        cout << "1. Pionowo" << endl;
        cout << "2. Poziomo" << endl;
        cout << "Wybierz: ";
        cin >> wybor;
    }
    else if (tryb_gry == 2)
    {
        wybor == rand() % 2 + 1;
    }

    switch (wybor)
    {
    case 1:
    {
        while (flaga == false)
        {
            if ((tryb_gry == 1) || (player == sprawdzenie))
            {
                cout << "Podaj rzad w ktorym chcesz ustawic statek: ";
                cin >> rzad;
                cout << "Podaj kolumne w ktorej chcesz ustawic statek: ";
                cin >> kolumna;
            }
            else if (tryb_gry == 2)
            {
                rzad = rand() % 10 + 1;
                kolumna = rand() % 10 + 1;
            }

            rzad -= 1;
            kolumna -= 1;

            if (rzad + 4 > 10) // sprawdza czy statek nie wtjdzie poza plansze
            {
                if ((tryb_gry == 1) || (player == sprawdzenie))
                {
                    cout << "Nie mozesz tak ustawic statku poniewaz wychodzi poza plansze" << endl;
                }
                flaga = false;
            }

            else
            {
                flaga = true;
                for (int i = rzad; i <= rzad + 3; i++) // sprawdza czy na danych indeksach tablicy nie istnieje juz statek
                {
                    if (rzad == 1)
                    {
                        if ((board[i][kolumna] == 1) || (board[i][kolumna - 1] == 1) || (board[i][kolumna + 1] == 1) || (board[i + 4][kolumna] == 1))
                        {
                            cout << " Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                        }
                    }
                    else if (rzad > 1)
                    {
                        if ((board[i][kolumna] == 1) || (board[i][kolumna - 1] == 1) || (board[i][kolumna + 1] == 1) || (board[i - 1][kolumna] == 1) || (board[i + 4][kolumna] == 1))
                        {
                            if ((tryb_gry == 1) || (player == sprawdzenie))
                            {
                                cout << "Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                            }
                            flaga = false;
                            break;
                        }
                    }
                }
            }
        }

        board[rzad][kolumna] = 1;
        board[rzad + 1][kolumna] = 1;
        board[rzad + 2][kolumna] = 1;
        board[rzad + 3][kolumna] = 1;
        break;
    }

    case 2:
    {
        while (flaga == false)
        {
            if ((tryb_gry == 1) || (player == sprawdzenie))
            {
                cout << "Podaj rzad w ktorym chcesz ustawic statek: ";
                cin >> rzad;
                cout << "Podaj kolumne w ktorej chcesz ustawic statek: ";
                cin >> kolumna;
            }
            else if (tryb_gry == 2)
            {
                rzad = rand() % 10 + 1;
                kolumna = rand() % 10 + 1;
            }

            rzad -= 1;
            kolumna -= 1;

            if (kolumna + 4 > 10) // sprawdza czy statek nie wtjdzie poza plansze
            {
                if ((tryb_gry == 1) || (player == sprawdzenie))
                {
                    cout << "Nie mozesz tak ustawic statku poniewaz wychodzi poza plansze" << endl;
                }
                flaga = false;
            }

            else
            {
                flaga = true;
                for (int i = kolumna; i <= kolumna + 3; i++) // sprawdza czy na danych indeksach tablicy nie istnieje juz statek
                {

                    if ((board[rzad][i] == 1) || (board[rzad - 1][i] == 1) || (board[rzad + 1][i] == 1))
                    {
                        if ((tryb_gry == 1) || (player == sprawdzenie))
                        {
                            cout << "Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                        }
                        flaga = false;
                        break;
                    }
                }
            }
        }

        board[rzad][kolumna] = 1;
        board[rzad][kolumna + 1] = 1;
        board[rzad][kolumna + 2] = 1;
        board[rzad][kolumna + 3] = 1;
        break;
    }
    }
}
void create_cruiser(int tryb_gyr, string sprawdzenie, string player, int wybor, int rzad, int kolumna, int board[10][10], bool flaga)
{

    if ((tryb_gyr == 1) || (player == sprawdzenie))
    {
        cout << "Ustawienie trzymasztowca gracza " << player << ":" << endl;
        cout << "1. Pionowo" << endl;
        cout << "2. Poziomo" << endl;
        cout << "Wybierz: ";
        cin >> wybor;
    }
    else if (tryb_gyr == 2)
    {
        wybor = rand() % 2 + 1;
    }
    switch (wybor)
    {
    case 1:
    {
        while (flaga == false)
        {
            if ((tryb_gyr == 1) || (player == sprawdzenie))
            {
                cout << "Podaj rzad w ktorym chcesz ustawic statek: ";
                cin >> rzad;
                cout << "Podaj kolumne w ktorej chcesz ustawic statek: ";
                cin >> kolumna;
            }
            else if (tryb_gyr == 2)
            {
                rzad = rand() % 10 + 1;
                kolumna = rand() % 10 + 1;
            }
            rzad -= 1;
            kolumna -= 1;

            if (rzad + 3 > 10) // sprawdza czy statek nie wtjdzie poza plansze
            {
                if ((tryb_gyr == 1) || (player == sprawdzenie))
                {
                    cout << "Nie mozesz tak ustawic statku poniewaz wychodzi poza plansze" << endl;
                }
                flaga = false;
            }

            else
            {
                flaga = true;
                for (int i = rzad; i <= rzad + 2; i++) // sprawdza czy na danych indeksach tablicy nie istnieje juz statek
                {

                    if ((board[i][kolumna] == 1) || (board[i][kolumna - 1] == 1) || (board[i][kolumna + 1] == 1) || (board[i - 1][kolumna] == 1) || (board[i + 3][kolumna] == 1))
                    {
                        if ((tryb_gyr == 1) || (player == sprawdzenie))
                        {
                            cout << "Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                        }
                        flaga = false;
                        break;
                    }
                }
            }
        }

        board[rzad][kolumna] = 1;
        board[rzad + 1][kolumna] = 1;
        board[rzad + 2][kolumna] = 1;
        break;
    }

    case 2:
    {
        while (flaga == false)
        {
            if ((tryb_gyr == 1) || (player == sprawdzenie))
            {
                cout << "Podaj rzad w ktorym chcesz ustawic statek: ";
                cin >> rzad;
                cout << "Podaj kolumne w ktorej chcesz ustawic statek: ";
                cin >> kolumna;
            }

            else if (tryb_gyr == 2)
            {
                rzad = rand() % 10 + 1;
                kolumna = rand() % 10 + 1;
            }

            rzad -= 1;
            kolumna -= 1;

            if (kolumna + 3 > 10) // sprawdza czy statek nie wtjdzie poza plansze
            {
                if ((tryb_gyr == 1) || (player == sprawdzenie))
                {
                    cout << "Nie mozesz tak ustawic statku poniewaz wychodzi poza plansze" << endl;
                }
                flaga = false;
            }

            else
            {
                flaga = true;
                for (int i = kolumna; i <= kolumna + 2; i++) // sprawdza czy na danych indeksach tablicy nie istnieje juz statek
                {

                    if ((board[rzad][i] == 1) || (board[rzad - 1][i] == 1) || (board[rzad + 1][i] == 1))
                    {
                        if ((tryb_gyr == 1) || (player == sprawdzenie))
                        {
                            cout << "Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                        }
                        flaga = false;
                        break;
                    }
                }
            }
        }

        board[rzad][kolumna] = 1;
        board[rzad][kolumna + 1] = 1;
        board[rzad][kolumna + 2] = 1;
        break;
    }
    }
}

void create_destroyer(int tryb_gry, string sprawdzenie, string player, int wybor, int rzad, int kolumna, int board[10][10], bool flaga)
{

    if ((tryb_gry == 1) || (player == sprawdzenie))
    {
        cout << "Ustawienie dwumasztowca gracza " << player << ":" << endl;
        cout << "1. Pionowo" << endl;
        cout << "2. Poziomo" << endl;
        cout << "Wybierz: ";
        cin >> wybor;
    }
    else if (tryb_gry == 2)
    {
        wybor = rand() % 2 + 1;
    }
    switch (wybor)
    {
    case 1:
    {
        while (flaga == false)
        {
            if ((tryb_gry == 1) || (player == sprawdzenie))
            {
                cout << "Podaj rzad w ktorym chcesz ustawic statek: ";
                cin >> rzad;
                cout << "Podaj kolumne w ktorej chcesz ustawic statek: ";
                cin >> kolumna;
            }

            else if (tryb_gry == 2)
            {
                rzad = rand() % 10 + 1;
                kolumna = rand() % 10 + 1;
            }
            rzad -= 1;
            kolumna -= 1;

            if (rzad + 2 > 10) // sprawdza czy statek nie wtjdzie poza plansze
            {
                if ((tryb_gry == 1) || (player == sprawdzenie))
                {
                    cout << "Nie mozesz tak ustawic statku poniewaz wychodzi poza plansze" << endl;
                }
                flaga = false;
            }

            else
            {
                flaga = true;
                for (int i = rzad; i <= rzad + 1; i++) // sprawdza czy na danych indeksach tablicy nie istnieje juz statek
                {

                    if ((board[i][kolumna] == 1) || (board[i][kolumna - 1] == 1) || (board[i][kolumna + 1] == 1))
                    {
                        if ((tryb_gry == 1) || (player == sprawdzenie))
                        {
                            cout << "Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                        }
                        flaga = false;
                        break;
                    }
                }
            }
        }

        board[rzad][kolumna] = 1;
        board[rzad + 1][kolumna] = 1;
        break;
    }

    case 2:
    {
        while (flaga == false)
        {
            if ((tryb_gry == 1) || (player == sprawdzenie))
            {
                cout << "Podaj rzad w ktorym chcesz ustawic statek: ";
                cin >> rzad;
                cout << "Podaj kolumne w ktorej chcesz ustawic statek: ";
                cin >> kolumna;
            }
            else if (tryb_gry == 2)
            {
                rzad = rand() % 10 + 1;
                kolumna = rand() % 10 + 1;
            }

            rzad -= 1;
            kolumna -= 1;

            if (kolumna + 2 > 10) // sprawdza czy statek nie wtjdzie poza plansze
            {
                if ((tryb_gry == 1) || (player == sprawdzenie))
                {
                    cout << "Nie mozesz tak ustawic statku poniewaz wychodzi poza plansze" << endl;
                }
                flaga = false;
            }

            else
            {
                flaga = true;
                for (int i = kolumna; i <= kolumna + 1; i++) // sprawdza czy na danych indeksach tablicy nie istnieje juz statek
                {

                    if ((board[rzad][i] == 1) || (board[rzad - 1][i] == 1) || (board[rzad + 1][i] == 1))
                    {
                        if ((tryb_gry == 1) || (player == sprawdzenie))
                        {
                            cout << "Nie mozesz tak ustawic statku bo kolizuje on z innym statkiem" << endl;
                        }
                        flaga = false;
                        break;
                    }
                }
            }
        }

        board[rzad][kolumna] = 1;
        board[rzad][kolumna + 1] = 1;
        break;
    }
    }
}

void shoot(int tryb_gry, string sprawdzenie, string player, int row, int colum, int ile_statkow_gracza, int board_1[10][10], int ilosc_trafien_gracza)
{
    if ((tryb_gry == 1) || (player == sprawdzenie))
    {
        cout << "Strzela: " << player << endl;
        cout << "Podaj rzad: ";
        cin >> row;
        cout << "Podaj kolumne: ";
        cin >> colum;
    }
    else
    {
        row = rand() % 10 + 1;
        colum = rand() % 10 + 1;
    }

    row -= 1;
    colum -= 1;

    if (board_1[row][colum] == 1)
    {
        cout << player << " Trafil!" << endl;
        board_1[row][colum] = 2;
        ile_statkow_gracza--;
        ilosc_trafien_gracza++;
        cout << "Ilosc trafien gracza: " << player << " Wynosi: " << ilosc_trafien_gracza << endl;
    }
    else if (board_1[row][colum] == 0)
    {
        cout << player << " nie trafil!" << endl;
        board_1[row][colum] = 3;
    }
}

int menu_game_mod(int &tryb_gry)
{
    cout << "MENU" << endl;
    cout << "1. Rozgrywka gracz vs gracz" << endl;
    cout << "2. Rozgrywka gracz vs komputer" << endl;
    cout << "Wybor trybu gry:";
    cin >> tryb_gry;
    return tryb_gry;
}

/*void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
}

void sleep_screen()
{
#ifdef WINDOWS
    Sleep(3000);
#else
    // Assume POSIX
    sleep(3);
#endif
}
*/
