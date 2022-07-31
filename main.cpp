#include <iostream>
#include <string>
#include <stdlib.h>

#define GRID_SIZE 3

using namespace std;

class Game {
    private:
        char gameboard[GRID_SIZE][GRID_SIZE];
    public: 
        void generateGameboard();
        void showGameboard();
        void askUserTurn();
        void checkForWin();
        void computerTurn();

        Game() {
            generateGameboard();
            showGameboard();
            checkForWin();
            while(true)
            {
                askUserTurn();
                checkForWin();

                computerTurn();
                showGameboard();
                checkForWin();
            }  
        }
};

void Game::generateGameboard() 
{
    int num = 1;
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            gameboard[x][y] = to_string(num).c_str()[0];
            num += 1;
        }
    }
}

void Game::showGameboard() 
{
    printf(" -------------\n");
    for (int x = 0; x < GRID_SIZE; x++) {
        printf(" |");
        for (int y = 0; y < GRID_SIZE; y++) {
            printf(" %c |", gameboard[x][y]);
        }
        printf("\n -------------\n");
    }
}

void Game::askUserTurn() 
{
    string userInput;
    while (true) 
    {
        cout << "What space would you like to play? " << endl;
        cin >> userInput;
        if (userInput != "")
        {
            char enteredChoice = userInput.c_str()[0];

            if (enteredChoice >= '1' && enteredChoice <= '9')
            {
                int enteredSpace = enteredChoice - '0';
                int index = enteredSpace - 1;

                int row = index / 3;
                int column = index % 3;

                char gameboardPosition = gameboard[row][column];

                if (gameboardPosition == 'X' || gameboardPosition == 'O')
                {
                    cout << "That gameboard position is already filled!" << endl;
                }
                else
                {
                    gameboard[row][column] = 'X';
                    break;
                }

            }
            else 
            {
                cout << "You must enter a numbered space between 1-9. " << endl;
            }
        }
        else if (userInput == "")
        {
            cout << "You must play a space. " << endl;
        }
    }
}

void Game::computerTurn() 
{
    while (true) 
    {
        int computerTurn = ( rand() % 9 ) + 1;

        int row = (computerTurn - 1) / 3;
        int column = (computerTurn - 1) % 3;

        char gridPosition = gameboard[row][column];

        if(gridPosition == 'X' || gridPosition == 'O') 
        {
            continue;
        }
        else 
        {
            printf("The computer played space %d.\n", computerTurn);
            gameboard[row][column] = 'O';
            break;
        }
    }
    
    

}

void Game::checkForWin() 
{
    const char* winningCombos[8] = {
        "123",
        "456",
        "789",
        "147",
        "258",
        "369",
        "159",
        "753"
    };

    for (int x = 0; x < 8; x++)
    {
        bool win = true;
        char previousGridSpace = '0';
        const char* winningCombo = winningCombos[x];

        for (int i = 0; i < 3; i++) 
        {
            char character = winningCombo[i];
            int enteredNum = character - '0';
            int gridSpace = enteredNum - 1;
            
            int row = gridSpace / GRID_SIZE;
            int column = gridSpace % GRID_SIZE;

            char gridChar = gameboard[row][column];

            if (previousGridSpace == '0')
            {
                previousGridSpace = gridChar;
            }
            else if (previousGridSpace == gridChar)
            {
                continue;
            }
            else
            {
                win = false;
                break;
            }
        }

        if (win)
        {
            cout << "********** Looks like we have a winner! **********" << endl;
            printf("It seems %c has won the game. Congratulations!\n\n", previousGridSpace);

            exit(0);
            break;
        
        }
    }
}

int main() {

    Game game;

    

    return 0;
}