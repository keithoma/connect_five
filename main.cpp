#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <list>
#include <unistd.h>
#include <vector>

using namespace std;

// after few rounds, out_of_bound error
// i really don't know why and where

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

	State at(int _col, int _row) const
	{
		return board.at(_col).at(_row);
	}

	void set(int _col, int _row, State _state)
	{
		board.at(_col).at(_row) = _state;
	}

    void print_board() const;
    State check_for_win() const;

    void add_and_animate(int _column, State _state);
	int number_of_empty_in_column(int _column) const;

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
            switch (board[column][row]) {
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
        if (at(_column, row) == State::empty) {
            set(_column, row, _state);
            if (row >= 1)
				set(_column, row - 1, State::empty);;
        } else {
            break;
        }
        print_board();
        usleep(100000); // 1 sec = 1000000
    }
}

State Board::check_for_win() const {
	return State::empty;
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

int Board::number_of_empty_in_column(int _column) const {
	int number_of_empty = 0;
	for (int row = 0; row < height; ++row) {
		if (at(_column, row) == State::empty) {
			++number_of_empty;
		}
	}
	return number_of_empty;
}

Board player_turn(Board board, Player _player) {
    board.print_board();
    cout << "\n";
    cout << "It's " << to_string(_player) << "'s player's turn. On which row do you want to put a stone?" << endl;

    int column;
    cin >> column;

	while (cin.fail() || column < 1 || column > 12 || board.number_of_empty_in_column(column) == 0) {
		if (board.number_of_empty_in_column(column) == 0) {
			cout << "That column is already full! Please enter another number!";
		} else {
			cout << "Please enter a valid integer between 1 and 12!\n";
		}
		cin.clear();
		cin.ignore(256, '\n');
		cin >> column;
	}

    board.add_and_animate(column - 1, to_state(_player));
    board.print_board();

    return board;
}

Board game(Board const& _board) {
	Board board = _board;
	board.print_board();

	for (Player const player: {Player::green, Player::red}) {
		board = player_turn(board, player);
		if (board.check_for_win() != State::empty) {
			return board;
		}

	}
	return game(board);
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
