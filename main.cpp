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
    vector<vector<State>> transpose();
};

void Board::print_board() const {
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

constexpr int WIN_COUNT = 5;

State Board::check_for_win() const {
	// 1.) check for horizontal win
	for (size_t row = 0; row < BOARD_HEIGHT; ++row)
	{
		int red = 0;
		int blue = 0;
		State lastState = State::empty;
		for (size_t col = 0; col < BOARD_WIDTH - WIN_COUNT; ++col)
		{
			State const currentState = at(row, col);
			if (currentState != lastState)
			{
				red = 0;
				blue = 0;
				lastState = currentState;
			}
			switch (currentState)
			{
				case State::red:
					red++;
					break;
				case State::blue:
					blue++;
					break;
				case State::empty:
					break;
			}
			if (red == WIN_COUNT)
				return State::red;
			if (blue == WIN_COUNT)
				return State::blue;
		}
	}

	// 2.) check for vertical win
	for (size_t col = 0; col < BOARD_WIDTH; ++col)
	{
		for (size_t row = 0; row < BOARD_WIDTH - WIN_COUNT; ++row)
		{
			// TODO: check downwards
		}
	}

	// 3.) check for diagonal win of the upper triangle
	// TODO
	// for (size_t diag = 0; diag < min(BOARD_WIDTH, BOARD_HEIGHT) - WIN_COUNT; ++diag)
	// {
	// }
    //
	// for (size_t col = 0; col < BOARD_WIDTH - WIN_COUNT; ++col)
	// {
	// 	int red = 0;
	// 	int blue = 0;
	// 	for (size_t row = 0; row < BOARD_HEIGHT - WIN_COUNT; ++row)
	// 	{
	// 		State lastStae = State::empty;
	// 		State const currentState = at(row, col);
	// 		if (currentState != lastState)
	// 		{
	// 			red = 0;
	// 			blue = 0;
	// 			lastState = currentState;
	// 		}
	// 	}
	// }

	// 4.) check for diagonal win of the lower triangle
}

enum class Player { Red, Blue };
string to_string(Player _player) {
	switch (_player) {
		case Player::Red: return "RED";
		case Player::Blue: return "BLUE";
	}
	throw std::invalid_argument("Player");
}

State to_state(Player _player)
{
	switch (_player) {
		case Player::Red: return State::red;
		case Player::Blue: return State::blue;
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


	for (Player const player: {Player::Red, Player::Blue})
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
		case State::blue:
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
