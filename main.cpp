#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <unistd.h>
#include <vector>

using namespace std;

const unsigned short int BOARD_WIDTH = 12;
const unsigned short int BOARD_HEIGHT = 8;

enum State { empty, blue, red };

class Board {
  public:
    vector<vector<State>> board; // board[width][height]
                                 // board[column][row]

    Board(unsigned short int _width, unsigned short int _height)
        : 
          width { _width },
          height { _height },
          board { vector<vector<State>>(_width, vector<State>(_height, State::empty)) }
        {
        }

    void print_board();
    State check_for_win();

    void add_and_animate(int _column, State _state);

  private:
    unsigned short int width;
    unsigned short int height;

    State check_vector(vector<State>);
    vector<vector<State>> transpose();
};

void Board::print_board() {
    // header
    cout << "\033[2J\033[1;1H"; // clears screen
    cout << "\n";
    // centralize
    // C O N N E C T   F I V E   <---   23 char
    // 80 - 23 = 57
    // 29 and 28 spaces
    cout << "                             C O N N E C T   F I V E                            ";
    cout << "\n\n\n";

    // board
    // 12 columns   => 80 / 12 = 6.666
    //              => 12 * 5 = 60
    // Therefore, margin of 12 on each side
    // each column gets 4 spaces inbetween
    for (int row = 0; row < height; ++row) {
    cout << "            ";
        for (int column = 0; column < width; ++column) {
            switch (board[row][column]) {
                case State::blue:
                    cout << "\x1b[32mX\x1b[0m";
                    break;
                case State::red:
                    cout << "\x1b[31mX\x1b[0m";
                    break;
                default:
                    cout << "O";
                    break;
            }
            cout << "    ";
        }
        cout << "\n";
    }
    cout << "           [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10] [11] [12]";
    cout << "\n\n\n";
}

void Board::add_and_animate(int _column, State _state) {
    for (int row = 0; row < height; ++row) {
        if (board[row][_column] == State::empty) {
            board[row][_column] = _state;
            if (row >= 1) {
                board[row - 1][_column] = State::empty;
            }
        } else {
            break;
        }
        print_board();
        usleep(300000); // 1 sec = 1000000
    }
}

// should use negative numbers instead of two ints
State Board::check_vector(vector<State> vec) {
    int points_blue = 0;
    int points_red  = 0;
    for (State state : vec) {
        if (state == State::blue) {
            points_blue++;
            points_red = 0;
        } else if (state == State::red) {
            points_red++;
            points_blue = 0;
        } else {
            points_blue = 0;
            points_red = 0;
        }

        if (points_blue == 5) {
            return State::blue;
        } else if (points_red == 5) {
            return State::red;
        }
    }
    return State::empty;
}

// this should only give me a reference? pointer? but not create a new board.
vector<vector<State>> Board::transpose() {
    vector<vector<State>> trans (height, vector<State>(width, State::empty));
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            trans[j][i] = board[i][j];
    return trans;
}

State Board::check_for_win() {
    for (vector<State> column : board) {
        State win = check_vector(column);
        switch (win) {
            case State::blue : return State::blue;
            case State::red : return State::red;
        }
    }
}

Board game_loop(Board board) {
    int row;

    board.print_board();
    cout << "\n";
    cout << "It's GREEN's player's turn. On which row do you want to put a stone?" << endl;
    cin >> row;
    board.add_and_animate(row - 1, State::blue);
    board.print_board();
    cout << "\n";
    cout << "It's red player's turn. On which row do you want to put a stone?\n>>";
    cin >> row;
    board.add_and_animate(row - 1, State::red);
    return board;
}

int main() {
    Board board(BOARD_WIDTH, BOARD_HEIGHT);
    while (true) {
        board = game_loop(board);
    }
    return 0;
}
