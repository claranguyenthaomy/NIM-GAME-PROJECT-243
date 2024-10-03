// NIM GAME PROJECT.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Team members: Abinya Karthigesan (40298665) and Thao-My Nguyen (40297798)

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


void displayPiles(const vector<int>& piles) {
    char pileName = 'A';
    for (int i = 0; i < piles.size(); ++i) {
        cout << pileName++ << ": ";
        for (int j = 0; j < piles[i]; ++j) {
            cout << "O ";
        }
        cout << endl;
    }
}


bool anyTokensLeft(const vector<int>& piles) {
    for (int tokens : piles) {
        if (tokens > 0) {
            return true;
        }
    }
    return false;
}


bool isValidMove(const vector<int>& piles, char pile, int tokens) {
    int pileIndex = pile - 'A';
    if (pileIndex < 0 || pileIndex >= piles.size() || piles[pileIndex] < tokens || tokens < 1 || tokens > 2) {
        return false;
    }
    return true;
}


void userMove(vector<int>& piles, const string& playerName) {
    char pile;
    int tokens;

    while (true) {
        cout << playerName << ", enter your move (e.g., A2): ";
        cin >> pile >> tokens;

        if (!isValidMove(piles, pile, tokens)) {
            cout << "Invalid move. Try again." << endl;
        }
        else {
            int pileIndex = pile - 'A';
            piles[pileIndex] -= tokens;
            break;
        }
    }
}


void computerMove(vector<int>& piles) {

    for (int i = 0; i < piles.size(); ++i) {
        if (piles[i] > 0) {
            int tokensToRemove = (rand() % 2) + 1;
            cout << "Computer removes " << tokensToRemove << " tokens from pile " << char('A' + i) << endl;
            piles[i] -= tokensToRemove;
            return;
        }
    }
}


void playNim(int numPiles, const string& player1, const string& player2, bool vsComputer) {
    vector<int> piles(numPiles);


    srand(time(nullptr));
    for (int i = 0; i < numPiles; ++i) {
        double tokens = floor(10 * exp(-pow(i - 5, 2) / 10.89));
        piles[i] = max(1, static_cast<int>(tokens));
    }

    cout << "Initial piles:" << endl;
    displayPiles(piles);
    cout << endl;

    bool player1Turn = true;

    while (anyTokensLeft(piles)) {
        if (player1Turn) {
            userMove(piles, player1);
        }
        else {
            if (vsComputer) {
                computerMove(piles);
            }
            else {
                userMove(piles, player2);
            }
        }

        displayPiles(piles);
        cout << endl;
        player1Turn = !player1Turn;
    }

    if (vsComputer) {
        if (player1Turn) {
            cout << "PC wins!" << endl;
        }
        else {
            cout << player1 << " wins!" << endl;
        }
    }
    else {
        if (player1Turn) {
            cout << player2 << " wins!" << endl;
        }
        else {
            cout << player1 << " wins!" << endl;
        }
    }
}

int main() {
    cout << "Welcome to the Nim game!" << endl;

    int option;
    cout << "Select the game mode:" << endl;
    cout << "1. Two players (user vs user)" << endl;
    cout << "2. Two players (PC vs user)" << endl;
    cin >> option;


    string player1, player2;
    if (option == 1) {
        cout << "Enter player 1 name: ";
        cin >> player1;
        cout << "Enter player 2 name: ";
        cin >> player2;
    }
    else {
        cout << "Enter your name: ";
        cin >> player1;
    }


    int numPiles;
    if (option == 1) {
        numPiles = 5;
    }
    else {
        cout << "Enter number of piles (between 2 and 10): ";
        cin >> numPiles;
        if (numPiles < 2 || numPiles > 10) {
            cout << "Invalid number of piles. Exiting..." << endl;
            return 1;
        }
    }

    bool vsComputer = (option == 2);

    playNim(numPiles, player1, player2, vsComputer);

    return 0;
}

