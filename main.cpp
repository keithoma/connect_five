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

State Board::check_vector(vector<State>) {

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
    Board board(WIDTH, HEIGHT);
    while (true) {
        board = game_loop(board);
    }
}
