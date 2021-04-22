#include <iostream>
#include <vector>

using namespace std;

const unsigned short int BOARD_WIDTH = 12;
const unsigned short int BOARD_HEIGHT = 8;

enum State { empty, blue, red };

class Board {
  public:
    Board(unsigned short int _width, unsigned short int _height)
        : 
          width { _width },
          height { _height },
          board { (width, vector<State>(height, State::empty)) }
        {
        }
    void print_board();
    void add_on_row(int row, State state);
    State check_for_win();

  private:
    unsigned short int width;
    unsigned short int height;
    vector<vector<State>> board;

    State check_vector(vector<State>);
    vector<vector<State>> transpose();
};

void Board::print_board() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (board[j][i] == State::empty) {
                cout << "O";
            } else if (board[j][i] == State::blue) {
                cout << "X";
            } else {
                cout << "Y";
            }
            cout << "   ";
        }
        cout << "\n";
    }
}

void Board::add_on_row(int row, State state) {
    for (int i=7; i>=0; i--) {
        if (board[row][i] == State::empty) {
            board[row][i] = state;
            break;
        }
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

    cout << "Hi";
    board.print_board();
    cout << "\n";
    cout << "It's blue player's turn. On which row do you want to put a stone?\n>>";
    cin >> row;
    // board.add_on_row(row - 1, State::blue);
    // board.print_board();
    cout << "\n";
    cout << "It's red player's turn. On which row do you want to put a stone?\n>>";
    cin >> row;
    // board.add_on_row(row - 1, State::red);
    return board;
}

int main() {
    Board board(BOARD_WIDTH, BOARD_HEIGHT);
    while (true) {
        board = game_loop(board);
    }
    return 0;
}
