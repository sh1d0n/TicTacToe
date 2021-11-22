#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
const char LOSE = 'L';
int autoLose = 0;

void instructions()
{
    std::cout << "Добро пожаловать в игру Крестики-Нолики.\n";
    std::cout << "Сделать свой ход в игре вы сможете выбрав цифру от одного до 0-8.\n";
    std::cout << "Эти цифры обозначают клетки на игровом поле, как показано на изображении:\n\n";
    std::cout << " 0 | 1 | 2\n";
    std::cout << " ---------\n";
    std::cout << " 3 | 4 | 5\n";
    std::cout << " ---------\n";
    std::cout << " 6 | 7 | 8\n\n";
    std::cout << "Советую хорошо подготовиться. Битва с искуственным интелектом вот вот начнется. Удачи!\n" << std::endl;
}

char playerPiece()
{
    int piece = 0;

    while (piece != 1 && piece != 2)
    {
        std::cout << "Выберите за кого вы будете играть (X - 1, O - 2): ";
        std::cin >> piece;

        switch (piece)
        {
        case 1:
            std::cout << "\nВы выбрали X, ваш ход будет первым!\n" << std::endl;
            return X;
        case 2:
            std::cout << "\nВы выбрали О, первым будет ходить компьютер!\n" << std::endl;
            return O;
        default:
            std::cout << "\nВы ввели некорректное число.\nПопробуйте еще раз или победа будет присвоена компьютеру\n" << std::endl;
            autoLose++;
            break;
        }

        if (autoLose == 3)
        {
            break;
        }
    }

}

char opponent(char piece)
{
    if (piece == X)
    {
        return O;
    }
    else
    {
        return X;
    }
}

char askNumber(std::string question, int high, int low = 0)
{
    int number;

    do
    {
        std::cout << question << " ( " << low << "-" << high << "): ";
        std::cin >> number;
    } while (number > high || number < low);

    return number;
}

void displayBoard(const std::vector<char>& board)
{
    std::cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    std::cout << "\n\t---------";
    std::cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    std::cout << "\n\t---------";
    std::cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    std::cout << "\n\n";
}

char winner(const std::vector<char>& board)
{
    const int WINNING_ROWS[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
    const int TOTAL_ROWS = 8;
    
    if (autoLose == 3)
    {
        return LOSE;
    }

    for (int row = 0; row < TOTAL_ROWS; row++)
    {
        if ((board[WINNING_ROWS[row][0]] != EMPTY) && (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
        {
            return board[WINNING_ROWS[row][0]];
        }
    }

    if (count(board.begin(), board.end(), EMPTY) == 0)
    {
        return TIE;
    }

    return NO_ONE;
}

inline bool isLegal(const std::vector<char>& board, int move)
{
    return (board[move] == EMPTY);
}

int playerMove(const std::vector<char>& board)
{
    int move = askNumber("Куда вы желаете сходить?", (board.size() - 1));
    while (!isLegal(board, move))
    {
        std::cout << "\nЭта клетка уже занята!!!\n";
        move = askNumber("Куда вы желаете сходить?", (board.size() - 1));
    }

    std::cout << "\nХороший ход!\n";
    return move;
}

int computerMove(std::vector<char> board, char computer)
{
    size_t move = 0;
    bool found = false;

    while (!found && move < board.size())
    {
        if (isLegal(board, move))
        {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }

        if (!found)
        {
            move++;
        }
    }

    if (!found)
    {
        move = 0;
        char player = opponent(computer);

        while (!found && move < board.size())
        {
            if (isLegal(board, move))
            {
                board[move] = player;
                found = winner(board) == player;
                board[move] = EMPTY;
            }

            if (!found)
            {
                move++;
            }
        }
    }

    if (!found)
    {
        move = 0;
        size_t i = 0;
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        while (!found && i < board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(board, move))
            {
                found = true;
            }
            i++;
        }
    }

    std::cout << "Компьютер сделал ход в клетку: " << move << std::endl;
    return move;
}

void announceWinner(char winner, char computer, char player)
{
    if (winner == computer)
    {
        std::cout << "\nПобедил компьютер!\n\n";
        std::cout << "Тебе еще далеко до компьютера XD.\n";
        std::cout << "Увидимся когда ты станешь сильнее!\n";
    }
    else if (winner == player)
    {
        std::cout << "\nПобедил игрок!\n\n";
        std::cout << "Не может быть :O.\n";
        std::cout << "Вот увидишь, в следующий раз я тебе не проиграю!\n";
    }
    else if (winner == TIE)
    {
        std::cout << "\nНичья.\n\n";
        std::cout << "Тебе повезло.\n";
        std::cout << "Радуйся, ведь только так ты можешь не проиграть мне!!!\n";
    }
    else if (winner == LOSE)
    {
        std::cout << "ХА! Ты смог проиграть даже до начала игры.\n";
        std::cout << "Приходи когда найдешь на клавиатуре нужные кнопки.\n";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int move;
    const int NUM_BOARD = 9;
    std::vector<char> board(NUM_BOARD, EMPTY);
    char player;
    char computer;

    instructions();

    player = playerPiece();
    computer = opponent(player);
    char turn = X;
    displayBoard(board);
    while (winner(board) == NO_ONE)
    {
        if (turn == player)
        {
            move = playerMove(board);
            board[move] = player;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        displayBoard(board);
        turn = opponent(turn);
    }

    announceWinner(winner(board), computer, player);

    return 0;
}