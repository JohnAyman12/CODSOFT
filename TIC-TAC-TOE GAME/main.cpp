#include <iostream>
#include <limits>

using namespace std;

char gameboard[3][3] =
{
    {'-', '*', '-'},
    {'*', '=', '*'},
    {'-', '*', '-'}
};

string player1, player2;

bool turn = true, win = false, playon = true;

char in;

int matchCount = 0;

void resetBoard()
{

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == 1 && j == 1) gameboard[i][j] = '=';
            else if((i+j) % 2 == 0) gameboard[i][j] = '-';
            else gameboard[i][j] = '+';
        }
    }
    turn = true;
    win = false;
    matchCount = 0;
}

void play()
{
    int row, col;
    if (turn)
    {
        cout << player1 << "'s turn!" << endl;
        cout << "Choose a place to put your X (enter row number then column number separated with a space): ";
        cin >> row >> col;
        while(cin.fail() || row >= 3 || col >= 3 || gameboard[row][col] == 'X' || gameboard[row][col] == 'O')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, choose a place to put your X (enter row number then column number separated with a space): ";
            cin >> row >> col;
        }
        gameboard[row][col] = 'X';
    }
    else
    {
        cout << player2 << "'s turn! " << endl;
        cout << "Choose a place to put your O (enter row number then column number separated with a space): ";
        cin >> row >> col;
        while(cin.fail() || row >= 3 || col >= 3 || gameboard[row][col] == 'X' || gameboard[row][col] == 'O')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, choose a place to put your O (enter row number then column number with a space in between): ";
            cin >> row >> col;
        }
        gameboard[row][col] = 'O';
    }
    cout << endl;
    turn = !turn;
}

bool checkWin()
{
    win = (gameboard[0][0] == gameboard[1][1] && gameboard[1][1] == gameboard[2][2]);
    win = win || (gameboard[0][2] == gameboard[1][1] && gameboard[1][1] == gameboard[2][0]);

    win = win || (gameboard[0][0] == gameboard[0][1] && gameboard[0][1] == gameboard[0][2]);
    win = win || (gameboard[1][0] == gameboard[1][1] && gameboard[1][1] == gameboard[1][2]);
    win = win || (gameboard[2][0] == gameboard[2][1] && gameboard[2][1] == gameboard[2][2]);

    win = win || (gameboard[0][0] == gameboard[1][0] && gameboard[1][0] == gameboard[2][0]);
    win = win || (gameboard[0][1] == gameboard[1][1] && gameboard[1][1] == gameboard[2][1]);
    win = win || (gameboard[0][2] == gameboard[1][2] && gameboard[1][2] == gameboard[2][2]);

    return win;
}

void Display()
{
    cout << "Board: " << endl;
    for(int i = 0; i < 3; i++)
    {
        cout << i;
        cout << "\t";
        for(int j = 0; j < 3; j++)
            cout << gameboard[i][j] << "\t";
        cout << endl << endl << endl;
    }
    cout << "\t";
    for(int i = 0; i < 3; i++)
        cout << i << "\t";
    cout << endl;
    if(checkWin()) cout << "Game state: Win";
    else
    {
        if(matchCount == 8) cout << "Game State: Draw";
        else cout << "Game state: Ongoing";
    }
    cout << endl << endl;
}

void getPlayers()
{
    cout << "Enter the first player's name: ";
    cin >> player1;
    cout << "Hello " << player1 << "! you will play with X." << endl;
    cout << "Enter the second player's name: ";
    cin >> player2;
    cout << "Hello " << player2 << "! you will play with O." << endl;
    cout << endl;
}

void declarResult()
{
    if(win)
    {
        turn = !turn;
        if(turn)
            cout << player1 << " won!" << endl;
        else
            cout << player2 << " won!" << endl;
    }
    else
        cout << "No one won."<< endl;

}

void newGamecheck()
{
    cout << "Play again? enter y for yes and n for no: ";
    cin >> in;
    while(cin.fail() || (in != 'y' && in != 'n' && in != 'Y' && in != 'N'))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, enter y for yes and n for no: ";
        cin >> in;
    }
    if(in == 'n' || in == 'N')
        playon = false;
    else
        resetBoard();
    cout << endl;
}

int main()
{
    while(playon)
    {
        cout << "***TIC-TAC-TOE GAME***" << endl;
        getPlayers();
        Display();
        for(matchCount; matchCount < 9; matchCount++)
        {
            play();
            Display();
            if(checkWin())
                break;
        }
        declarResult();

        newGamecheck();
    }

    cout << "See you soon!" << endl;

    return 0;
}
