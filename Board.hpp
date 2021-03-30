#include <iostream>
#include <vector>
#include <map>
#include "Direction.hpp"
using namespace ariel;
using namespace std;

namespace ariel{

class Board{

    private:
    std::map<unsigned int, pair<unsigned int, vector<char>> > messageBoard;
    unsigned int minCol = 0;
    unsigned int maxCol = 0;
    unsigned int minRow = 0;
    unsigned int maxRow = 0;
    bool isInit = false;

    
    public:
    Board(){
        messageBoard = map<unsigned int, pair<unsigned int, vector<char>> >();
     }
     ~Board(){};
    std::string read(unsigned int row, unsigned int col, Direction d, unsigned int length );

    void post(unsigned int row, unsigned int col, Direction d, std::string s);

    void show();

    private:
    void updateH(unsigned int row, unsigned int col, string s);
    void updateV(unsigned int row, unsigned int col, char c);
    string readH(unsigned int row, unsigned int col, unsigned int length);
    char readV(unsigned int row, unsigned int col);
};
}