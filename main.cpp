#include <iostream>
#include <vector>

using namespace std;

int WIDTH = 12;
int HEIGHT = 8;

enum State { empty, blue, red };

class Board {
  public:
    Board(int width, int height) : board(width, vector<State>(height, State::empty)) {}
    void print_board();
    void add_on_row(int row, State state);
    State check_for_win();

  private:
    vector<vector<State>> board;
    State check_vector(vector<State>);
    vector<vector<State>> transpose();
};

void Board::print_board() {
    for (int i=0; i<8; i++) {
        for (int j=0; j<12; j++) {
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
    vector<vector<State>> trans (HEIGHT, vector<State>(WIDTH, State::empty));
}

outtrans(out[0].size(),
                                    vector<double>(out.size()));
    for (size_t i = 0; i < out.size(); ++i)
        for (size_t j = 0; j < out[0].size(); ++j)
            outtrans[j][i] = out[i][j];

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
    cout << "It's blue player's turn. On which row do you want to put a stone?\n>>";
    cin >> row;
    board.add_on_row(row - 1, State::blue);
    board.print_board();
    cout << "\n";
    cout << "It's red player's turn. On which row do you want to put a stone?\n>>";
    cin >> row;
    board.add_on_row(row - 1, State::red);
    return board;
}

int main() {
    Board board(WIDTH, HEIGHT);
    while (true) {
        board = game_loop(board);
    }
}
