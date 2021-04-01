#include <iostream>
#include <vector>
#include <map>
#include "Direction.hpp"
using namespace ariel;
using namespace std;

namespace ariel{

/*This class represents a message board which consist of the following:
 messageBoard(map) - holds as a key a positive integer which represents each row in the message board.The value of the row is
 a pair which holds an integer that represent the coloum which the first post in this row starts, and a vector of string
 that each post in the row is build in it.

 minCol(unsigned int) - the minimum col  which a post is started from, of all the rows.

 maxCol(unsigned int) - the maximum col which a post is ended, of all the rows.

 minRow(unsigned int) - the minimum row  which a post was posted in it.

 maxRow(unsigned int) - the maximum row  which a post was posted in it.
*/
class Board{

    private:
    std::map<unsigned int, pair<unsigned int, vector<char>> > messageBoard;
    unsigned int minCol = 0;
    unsigned int maxCol = 0;
    unsigned int minRow = 0;
    unsigned int maxRow = 0;
    bool isInit = false;

    
    public:
    /*Constructor*/
    Board(){
        messageBoard = map<unsigned int, pair<unsigned int, vector<char>> >();
     }
     /*Destructor*/
     ~Board(){};
     
     /*Returns a string that represents part of the messagboard, in the given coordinates and the wanted length.*/
    std::string read(unsigned int row, unsigned int col, Direction d, unsigned int length );

    /*Post a given string in the given coordinates in the message board.In case a post is already exist, an overrun should accourd.*/
    void post(unsigned int row, unsigned int col, Direction d, std::string s);

    /*Prints all the posts in the message board.*/
    void show();

    private:
    void updateH(unsigned int row, unsigned int col, string s);
    void updateV(unsigned int row, unsigned int col, char c);
    string readH(unsigned int row, unsigned int col, unsigned int length);
    char readV(unsigned int row, unsigned int col);
};
}