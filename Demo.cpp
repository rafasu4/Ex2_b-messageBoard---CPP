/**
 * Demo program for message-board exercise.
 * 
 * Author: Erel Segal-Halevi
 * Since : 2021-03
 */

#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;
const Direction HORI = Direction::Horizontal;
const Direction VER = Direction::Vertical;

int main() {
	ariel::Board b;
	b.post(28, 41, HORI, "rand ");
	//b.show();
	cout << endl;
	cout << b.read(28,41,HORI, 50);
	
	
    // board.read(5, 3, Direction::Horizontal, 4);
    // board.read(5, 2, Direction::Horizontal, 5);
    // board.read(5, 2, Direction::Horizontal, 6);
	//cout << board.read(5, 2, Direction::Horizontal, 6);
	// 	// prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
	// board.post(/*row=*/99, /*column=*/202, Direction::Vertical, "xyz");
	// cout << board.read(/*row=*/100, /*column=*/200, Direction::Horizontal, /*length=*/6) << endl;  
	// 	// prints "abyd__" (First letters are ab; then y from the "xyz"; then d; then two empty cells).

	// b.show(); // shows the board in a reasonable way. For example:
		//    98:  _________
		//    99:  ____x____
		//    100: __abyd___
		//    101: ____z____
		//    102: _________
}

