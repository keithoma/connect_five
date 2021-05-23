#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <list>
#include <unistd.h>
#include <vector>

using namespace std;


// the dimension of the board is not working

constexpr unsigned short int BOARD_WIDTH = 12;
constexpr unsigned short int BOARD_HEIGHT = 8;

enum State { empty, green, red };

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

	State at(int _row, int _col) const
	{
		return board.at(_row).at(_col);
	}

	void set(int _row, int _col, State _value)
	{
		board.at(_row).at(_col) = _value;
	}

    void print_board() const;
    State check_for_win() const;

    void add_and_animate(int _column, State _state);


  private:
    unsigned short int width;
    unsigned short int height;

    State check_vector(vector<State>);
};

void Board::print_board() const {
    // clear screen
    cout << "\033[2J\033[1;1H" << "\n";

    // header
    cout << "                             C O N N E C T   F I V E                            \n\n\n";

    // board
    for (int row = 0; row < height; ++row) {
    cout << "            ";
        for (int column = 0; column < width; ++column) {
            switch (board[row][column]) {
                case State::green:
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
    cout << "           [1]  [2]  [3]  [4]  [5]  [6]  [7]  [8]  [9]  [10] [11] [12]\n\n\n";
}

void Board::add_and_animate(int _column, State _state) {
    for (int row = 0; row < height; ++row) {
        if (at(row, _column) == State::empty) {
            set(row, _column, _state);
            if (row >= 1)
				set(row - 1, _column, State::empty);;
        } else {
            break;
        }
        print_board();
        usleep(300000); // 1 sec = 1000000
    }
}

State Board::check_for_win() const {

}

enum class Player { green, red };

string to_string(Player _player) {
	switch (_player) {
		case Player::green: return "\x1b[32mGREEN\x1b[0m";
		case Player::red: return "\x1b[31mRED\x1b[0m";
	}
	throw std::invalid_argument("Player");
}

State to_state(Player _player) {
	switch (_player) {
		case Player::green: return State::green;
		case Player::red: return State::red;

	}
	throw std::invalid_argument("Player");
}

Board player_turn(Board board, Player _player) {
    board.print_board();
    cout << "\n";
    cout << "It's " << to_string(_player) << "'s player's turn. On which row do you want to put a stone?" << endl;

    int row;
    cin >> row;

    board.add_and_animate(row - 1, to_state(_player));
    board.print_board();

    return board;
}

Board game(Board const& _board)
{
	Board board = _board; // python: baord = copy(_board);
	board.print_board();

	Board const& bref = _board;
	bref.print_board();

	Board const* pref = &_board;
	pref->print_board();


	for (Player const player: {Player::green, Player::red})
	{
		board = player_turn(board, player);
		switch (board.check_for_win())
		{
			case State::empty:
				return game(board);
			default:
				break;
		}
	}
	return board;
}

int main()
{
	auto const resultBoard = game(Board(BOARD_WIDTH, BOARD_HEIGHT));

	switch (resultBoard.check_for_win())
	{
		case State::red:
			cout << "Team RED has won!\n";
			break;
		case State::green:
			cout << "Team BLUE has won!\n";
			break;
		case State::empty:
			cout << "HOLY SHIT YOU BROKE THE SYSTEM\n";
			break;
	}

    // while (true) {
    //     board = game_loop(board);
    // }
    return 0;
}
