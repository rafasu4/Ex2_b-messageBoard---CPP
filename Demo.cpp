
#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
	ariel::Board board;
	 board.post(0, 0, Direction::Horizontal, "Reut");
    board.post(0, 0, Direction::Vertical, "Reut");
    board.post(0, 3, Direction::Vertical, "Mas");
    board.post(5, 2, Direction::Horizontal, "Yakir");
    board.post(4, 6, Direction::Horizontal, "temp");
    board.post(1, 6, Direction::Vertical, "ariela");
    board.post(5, 6, Direction::Vertical, "W"); 
	cout << board.read(5, 2, Direction::Horizontal, 7) << endl; 
	board.show(); // shows the board in a reasonable way. For example:
		//    98:  _________
		//    99:  ____x____
		//    100: __abyd___
		//    101: ____z____
		//    102: _________
}