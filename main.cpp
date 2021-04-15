#include <iostream>
#include <iterator>

using namespace std;

enum State { empty, blue, red };

class Board {
  public:
    Board();
    void print_board();
    void add_on_row(int row, State state);
    State check_for_win();

  private:
    State board [12][8];
    template <size_t N1>
    State check_array(State (&arr)[N1]);
};

Board::Board() {
    for (int i=0; i<12; i++) {
        for (int j=0; j<8; j++) {
            board[i][j] = State::empty;
        };
    };
}

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

// I have the feeling this can be written better
template <size_t N1>
State Board::check_array(State (&arr)[N1]) {
    for ()
}

State Board::check_for_win() {
    
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
    Board board;
    while (true) {
        board = game_loop(board);
    }
}
