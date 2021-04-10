
#include "Board.hpp"
#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    Board b;
	string c;
    string name = "Raphael";
    for (unsigned int i = 0; i < name.length(); i++)
    {
         c = name.at(i);
        b.post(10 + i, 10 + i, Direction::Horizontal, c);
    }
	 b.post(11,11,Direction::Vertical,"ariel");
	 b.post(15,15,Direction::Vertical,"ex2");
	 b.show();
    
    return 0;
}