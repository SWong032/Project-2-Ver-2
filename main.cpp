/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: Sydney Wong
 *
 * Created on May 20, 2023, 4:31 PM
 * Purpose: Project 2 Ver 2 
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function Prototypes
void selSort(vector<int>&); //selection sort
bool linSrch(const vector<int>&, int); //linear search
void Bets(int, int[]);
void Scores(const int[], const float); 
void pTurn(int[], const char, const int); //player's turn
void dTurn(float&); //dealer's turn
void Winner(const int[], const float); //determine winner

int main(int argc, char** argv) {
    const int numPlay = 2; //number of players
    int pScores[numPlay] = {0}; //single dimensioned array for player scores
    float dealer = rand() % 10 + 12; // Dealer starts with random score between 12 and 21 (can't be 13 since it'll go over 21)

    // Draw two cards for each player
    pScores[0] += rand() % 10 + 2; 
    pScores[1] += rand() % 10 + 2;
    string intro = "                                A Game of Blackjack";
    cout << intro << endl;

    // Print out instructions
    cout << endl;
    cout << "                                   -Instructions-        \n";
   
    cout << " ---------------------------------------------------------------------------------------- \n";
    cout << "|A simple multiplayer card game. An easy game of chance, just like rock, paper, scissors.|\n";
    cout << "|The goal of Blackjack is to beat the dealer or get close to 21. First step is to place  |\n";
    cout << "|in your bets. Players either choose hit or stand. If you choose hit, another card will  |\n";
    cout << "|be added to your deck to add to your card value. If you choose stand, you keep your card|\n";
    cout << "|value. Each player's card value will total up which will determine whether you win or   |\n";
    cout << "|lose. For example, your first card is a 10 and you choose to hit. The second card is 9  |\n";
    cout << "|which totals to 19, if the dealer's hand is 20, the player can hit or stand until the   |\n";
    cout << "|dealer reveals their hand. If the player's hand is closer to 21, you win. You lose if   |\n";
    cout << "|your hand went over 21 or under since your goal is to beat other players and the dealer.|\n";
    cout << "|                                  Best of luck!                                         |\n";
    cout << " ---------------------------------------------------------------------------------------- \n";
    cout << endl << endl;

    //Easy to read instructions
    cout << "***If you didn't bother reading the instructions, here's how it works.***\n";
    cout << "1. Win? You want to score under 21 and not over to beat the dealer.\n";
    cout << "2. How? The cards given to you are your score and it either adds or doesn't.\n";
    cout << "3. Add to your score? Choose hit.\n";
    cout << "4. Don't want to add to your score?  Choose stand.\n";
    cout << "5. Score = close to 21 & dealer & other players' hand is lower than yours. Win.\n";
    cout << "6. Score = lower than dealer & other player's hand. Lose.\n";
    cout << "7. Strategize because you placed bets, or not and just wing it.\n";
    cout << endl << endl;
    
    //Table to show player(s) the betting options
    cout << "              ---------------------------------------------------------- \n";
    cout << "             |                         {BETS}                           |\n"; 
    cout << "             |Yes. You can bet fake money with imaginary chips because  |\n"; 
    cout << "             |this is a legal family-friendly game so no one will go    |\n"; 
    cout << "             |into debt nor will someone come for you for money. Unless |\n"; 
    cout << "             |you owe real money in the real world aka outside this     |\n"; 
    cout << "             |computer screen. Players of this game can bet in the range|\n"; 
    cout << "             |from $1 to $500. Because this game is still in development|\n"; 
    cout << "             |players will only need to insert the amount they desire   |\n"; 
    cout << "             |before playing. Then after the game, it will determine    |\n"; 
    cout << "             |whether or not you or other players will keep or lose     |\n"; 
    cout << "             |their bets depending on the result.                       |\n";
    cout << "              ---------------------------------------------------------- \n";
    
    cout << endl;
    cout << "                                       *Notice* \n"; //Note for development
    cout << "     Please be aware this game is in development so bugs and errors might appear. \n";
    cout << endl;
    cout << "======================================================================================\n";
    bool playing = true;

    ofstream myFile;
    myFile.open("myFile.txt");

    do {
         // Players place bets
        int Betting[numPlay] = {0}; // Using single dimensioned array for player bets
        Bets(numPlay, Betting);
        Scores(pScores, dealer);

        // Player 1's turn
        pTurn(pScores, '1', 0);

        // Player 2's turn
        pTurn(pScores, '2', 1);

        // Dealer's turn
        dTurn(dealer);

        // Determine the winner
        Winner(pScores, dealer);

        playing = false;
    } while (playing);

    myFile.close();

    return 0;
}

// Function to place bets for each player
void Bets(int Numbers, int Betting[]) {
    cout << "Player 1, place your bet: ";
    cin >> Betting[0];

    cout << "Player 2, place your bet: ";
    cin >> Betting[1];

    // Default bet amount if invalid input
    if (Betting[0] <= 0)
        Betting[0] = 10;
    if (Betting[1] <= 0)
        Betting[1] = 10;
}

//Scoring display
void Scores(const int pScores[], const float dScore) {
    cout << endl;
    cout << "Scoreboard" << endl;
    cout << "Player 1 score: " << pScores[0] << endl;
    cout << "Player 2 score: " << pScores[1] << endl;
    cout << "Dealer score: " << dScore << endl;
    cout << endl;
}

// Function for each player's turn
void pTurn(int pScores[], const char pNum, const int index) { //player's number
    cout << "Player " << pNum << ", would you like to hit or stand? (Press h or s)" << endl;
    char choice;
    cin >> choice;

    if (choice == 'h') {
        pScores[index] += static_cast<int>(rand() % 10 + 2);
        if (pScores[index] > 21) {
            cout << "Player " << pNum << " busts! Better luck next time!" << endl;
        }
    }
}

// Function for dealer's turn
void dTurn(float& dScore) {
    while (dScore < 17) {
        dScore += static_cast<int>(rand() % 10 + 2);
    }
}

// Function to determine the winner
void Winner(const int pScores[], const float dScore) {
    if (dScore > 21) {
        cout << "Dealer busts! Both players win!" << endl;
    }
    else if (dScore >= 17 && dScore <= 21) {
        if (pScores[0] > 21 && pScores[1] > 21) {
            cout << "Both players bust! Dealer wins!" << endl;
        }
        else if (pScores[0] > 21 && pScores[1] <= 21) {
            cout << "Player 2 beats the dealer! Congrats on winning!" << endl;
        }
        else if (pScores[0] <= 21 && pScores[1] > 21) {
            cout << "Player 1 beats the dealer! Congrats on winning!" << endl;
        }
        else {
            if (pScores[0] > dScore && pScores[1] > dScore) {
                cout << "Both players beat the dealer! Congrats on winning!" << endl;
            }
            else if (pScores[0] > dScore && pScores[1] <= dScore) {
                cout << "Player 1 beats the dealer! Congrats on winning!" << endl;
            }
            else if (pScores[0] <= dScore && pScores[1] > dScore) {
                cout << "Player 2 beats the dealer! Congrats on winning!" << endl;
            }
            else {
                cout << "Dealer beats everyone! Better luck next time!" << endl;
            }
        }
    }
}

// Selection sort
void selSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Linear search
bool linSrch(const vector<int>& arr, int target) {
    return find(arr.begin(), arr.end(), target) != arr.end();
}
