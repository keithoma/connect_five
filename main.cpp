#include <iostream>

using namespace std;

enum State { empty, blue, red };

class Board {
  public:
    Board();
    void print_board();
    void add_on_row(int row, State state);
  private:
    State board [12][8];
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
            cout << " ";
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

Board game_loop(Board board) {
    board.print_board();
    cout << "\n";
    cout << "It's blue player's turn. On which row do you want to put a stone?";
    int row;
    cin >> row;
    board.add_on_row(row, State::blue);
    board.print_board();
    cout << "\n";
    cout << "It's red player's turn. On which row do you want to put a stone?";
    cin >> row;
    board.add_on_row(row, State::red);
    return board;
}

int main() {
    Board obj;
    while (true) {
        obj = game_loop(obj);
    }
}
