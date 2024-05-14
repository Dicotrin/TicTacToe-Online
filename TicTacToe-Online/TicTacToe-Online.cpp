#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

CONST int HEIGHT = 5;
CONST int WEIGHT = 16;

bool CheckWin(string field[5][16])
{
    if (field[0][2] == field[0][8] && field[0][2] == field[0][14] && field[0][2] != " ")
        return true;
    if (field[2][2] == field[2][8] && field[2][2] == field[2][14] && field[2][2] != " ")
        return true;
    if (field[4][2] == field[4][8] && field[4][2] == field[4][14] && field[4][2] != " ")
        return true;
    if (field[0][2] == field[2][2] && field[0][2] == field[4][2] && field[0][2] != " ")
        return true;
    if (field[0][8] == field[2][8] && field[0][8] == field[4][8] && field[0][8] != " ")
        return true;
    if (field[0][14] == field[2][14] && field[0][14] == field[4][14] && field[0][14] != " ")
        return true;
    if (field[0][2] == field[2][8] && field[0][2] == field[4][14] && field[0][2] != " ")
        return true;
    if (field[4][2] == field[2][8] && field[4][2] == field[0][14] && field[4][2] != " ")
        return true;
    return false;
}

void DrawField(string field[5][16])
{
    system("cls");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WEIGHT; j++)
        {
            cout << field[i][j];
        }
        cout << "\n";
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    CONST int HEIGHT = 5;
    CONST int WEIGHT = 16;
    bool turn = false;
    bool win = false;
    string winer = "";
    string retry = "";

    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE); // получаем дескриптор
    INPUT_RECORD InputRecord; // используется для возвращения информации о входных сообщениях в консольном входном буфере
    DWORD Events; // unsigned long
    COORD coord; // для координат X, Y

    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    string yesNo[2] = { "Да", "Нет" };

    string field[HEIGHT][WEIGHT]
    {
        {" ", "[", " ", "]", " ", "|", " ", "[", " ", "]", " ", "|", " ", "[", " ", "]"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {" ", "[", " ", "]", " ", "|", " ", "[", " ", "]", " ", "|", " ", "[", " ", "]"},
        {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"},
        {" ", "[", " ", "]", " ", "|", " ", "[", " ", "]", " ", "|", " ", "[", " ", "]"},
    };

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WEIGHT; j++)
        {
            cout << field[i][j];
        }
        cout << "\n";
    }

    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку мыши

    while (true)
    {
        ReadConsoleInput(hin, &InputRecord, 1, &Events); // считывание 

        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) // левая кнопка
        {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

            if ((coord.X == 2 || coord.X == 8 || coord.X == 14) && (coord.Y == 0 || coord.Y == 2 || coord.Y == 4) && field[coord.Y][coord.X] == " " && win == false)
            {
                if (turn == false)
                {
                    field[coord.Y][coord.X] = "O";
                    turn = true;
                }
                else
                {
                    field[coord.Y][coord.X] = "X";
                    turn = false;
                }

                DrawField(field);

                if (CheckWin(field))
                {
                    win = true;
                    if (turn == false)
                    {
                        winer = "Победили крестики\n";
                        cout << winer;
                    }
                    else
                    {
                        winer = "Победили нолики\n";
                        cout << winer;
                    }
                }
                SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку 
            }
            if (win == true)
            {
                DrawField(field);

                cout << winer;
                cout << "Хотите начать заново?\n";
                cout << yesNo[0] + " " + yesNo[1] + "\n";

                SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку

                if ((coord.X == 0 && coord.Y == 7) || (coord.X == 1 && coord.Y == 7))
                {
                    for (int i = 0; i < HEIGHT; i++)
                    {
                        for (int j = 0; j < WEIGHT; j++)
                        {
                            if (field[i][j] == "O" || field[i][j] == "X")
                            {
                                field[i][j] = " ";
                            }
                        }
                    }
                    DrawField(field);
                    win = false;
                    SetConsoleMode(hin, ENABLE_MOUSE_INPUT); // разрешаем обработку 
                }
                else if ((coord.X == 3 && coord.Y == 7) || (coord.X == 4 && coord.Y == 7) || (coord.X == 5 && coord.Y == 7))
                {
                    win = false;
                    return 0;
                }
            }
        }
    }
}