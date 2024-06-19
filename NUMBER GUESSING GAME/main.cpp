#include <iostream>
#include<cstdlib>
#include<time.h>
#include<fstream>
#include<string>

using namespace std;

int main()
{
    // getting best previous score if available.
    string bestScoreStr;
    ifstream BestScoreFile("best score.txt");
    if (!BestScoreFile)
        cout << "Error opening the file." << endl;
    getline(BestScoreFile, bestScoreStr);
    int bestScore = 0;
    if(bestScoreStr.length() != 0 && isdigit(bestScoreStr[0]))
        bestScore = stoi(bestScoreStr);
    BestScoreFile.close();

    // initializing the new number.
    srand(time(0));
    int random = rand() % 100;

    // playing the game with the user.
    int input, counter = 1;
    cout << "****NUMBER GUESSING GAME****" << endl;
    cout << "Let's see if your skills in guessing guess :)" << endl;
    cout << "Enter a number: ";
    cin >> input;
    while(input != random)
    {
        counter++;
        if(input > random)
            cout << "Too high. Chose a smaller number: ";
        if(input < random)
            cout << "Too low. Chose a higher number: ";
        cin >> input;
    }
    cout << endl;

    // evaluating number of trials to update the high score if needed.
    if(counter >= bestScore)
    {
        if (counter == 1)
            cout << "Correct! you got it after 1 trial." << endl;
        else
            cout << "Correct! you got it after " << counter << " trials." << endl;
        cout << "High score: " << bestScore;
    }
    else
    {
        cout << "Congratulations! you made a new high score" << endl;
        cout << "Previous high score: " << bestScore << endl;
        cout << "New high score: " << counter << endl;

        ofstream MyFile("best score.txt");
        MyFile << counter;
    }

    cout << endl;
    return 0;
}
