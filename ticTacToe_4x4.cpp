#include <bits/stdc++.h>
using namespace std;

bool equals4(int a, int b, int c, int d)
{
    return a == b && b == c && c == d && a != ' ' &&b!=' '&&c!=' ';
}
char checkWin(vector<vector<char>> board)
{
    int emptySpaces = 0;
    char res = ' ';
    for (int i = 0; i < 4; i++)
    {
        // row wise
        if (equals4(board[i][0], board[i][1], board[i][2], board[i][3]))
            res = board[i][0];

        // column wise
        if (equals4(board[0][i], board[1][i], board[2][i], board[3][i]))
            res = board[0][i];
    }

    //diagonal ->\ 
    if (equals4(board[0][0], board[1][1], board[2][2], board[3][3]))
    res = board[0][0];
    // diagonal -> /
    if (equals4(board[0][3], board[1][2], board[2][1], board[3][0]))
        res = board[0][3];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j], ' ')
            {
                emptySpaces++;
            }
        }
    }
    if (res != ' '&&!emptySpaces)
        return res;
    else
        return 't';
}

int minimax(vector<vector<char>> &board, int depth, bool isMaxmizing)
{
    char res = checkWin(board);
    if (res== 'X')
        return 1;
    if (res== '0')
        return -1;
    if (res== 't')
        return 0;

    if (isMaxmizing)
    {
        int score, bestScore = INT_MIN;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (board[i][j], ' ')
                {
                    board[i][j] = 'X';
                    score = minimax(board, depth + 1, false);
                    bestScore = max(score, bestScore);
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
    else
    {
        int score, bestScore = INT_MAX;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (board[i][j], ' ')
                {
                    board[i][j] = 'X';
                    score = minimax(board, depth + 1, true);
                    bestScore = min(score, bestScore);
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

void printBoard(vector<vector<char>> vec)
{
    cout << "\n-----------------"<<endl;
    for (auto a : vec)
    {
        cout << "| ";
        for (auto b : a)
            cout << b << " | ";
        cout << "\n-----------------";
        cout << endl;
    }
}

int main()
{
    vector<vector<char>> board{{' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' '}};

    char human = '0', computer = 'X';
    int n = 16;
    pair<int, int> bestMove, userMove;
    cout <<endl<< "User move format (row, column) you want to move (starting from 0th index)" << endl<<endl;

    while (n != 0)
    {
        int score = 0, bestScore = INT_MIN;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (board[i][j] == ' ')
                {

                    board[i][j] = computer;
                    score = minimax(board, 0, true);
                    board[i][j] = ' ';

                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestMove = make_pair(i, j);
                    }
                }
            }
        }
        board[bestMove.first][bestMove.second] = computer;
        cout <<endl<< "Computer move :  "<<bestMove.first<<" " <<bestMove.second<<endl;

        printBoard(board);
        checkWin(board);
        n--;
        cout <<endl << "User turn :  ";
        cin >> userMove.first;
        cin >> userMove.second;
        board[userMove.first][userMove.second] = human;
        n--;
        checkWin(board);

        printBoard(board);
        cout<<endl<<endl;
    }
}