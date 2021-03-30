#include "Board.hpp"
constexpr char SPACE = '_';
constexpr int noNeedSpaceInPrint = 100;

namespace ariel
{

    std::string Board::read(unsigned int row, unsigned int col, Direction d, unsigned int length)
    {
        if (length < 0)
        {
            throw std::logic_error("length of a word cann't be negative!");
        }
        string ans;
        if (d == Direction::Horizontal)
        {
            ans = readH(row, col, length);
        }
        else
        {
            for (unsigned i = 0; i < length; i++)
            {
                ans += readV(row + i, col);
            }
        }
        return ans;
    }

    void Board::post(unsigned int row, unsigned int col, Direction d, std::string s)
    {
        //if the string is empty - nothing to be changed
        if (!s.empty())
        {
            //checking and updating, in case of the following ,the borders for show function
            if(!isInit){
                minRow = maxRow = row;
                minCol = col;
                maxCol = col + s.size();
                isInit = true;
            }
            else{
                if(row < minRow){
                    minRow = row;
                }
                if(row > maxRow){
                    maxRow = row;
                }
                if(col < minCol){
                    minCol = col;
                }
                if(col > maxCol){
                    maxCol = col;
                }
            }
            if (d == Direction::Horizontal)
            {
                //if the giving row is in the board
                if (messageBoard.count(row) > 0)
                {
                    updateH(row, col, s);
                }
                else //creat a new pair with the giving input
                {
                    vector<char> newPost = vector<char>();
                    for (char c : s)
                    {
                        newPost.push_back(c);
                    }
                    pair<unsigned int, vector<char>> newRow = {col, newPost};
                    messageBoard[row] = newRow;
                }
            }
            //if the direction is vertical
            else
            {
                string::iterator it;
                unsigned int i = 0;
                for (it = s.begin(); it < s.end(); it++)
                {
                    //if the current row is in the board
                    if (messageBoard.count(row + i) > 0)
                    {
                        updateV(row + i, col, *it);
                    }
                    else //creat a new pair with the giving input
                    {
                        pair<unsigned int, vector<char>> newPair = pair<unsigned int, vector<char>>();
                        newPair.first = col;
                        newPair.second.push_back(*it);
                        messageBoard[row + i] = newPair;
                    }
                    i++;
                }
            }
        }
    }

    void Board::show()
    {
        map<unsigned int, pair<unsigned int, vector<char>>>::iterator it = messageBoard.begin();
        unsigned int firstLine = minRow;
        while(firstLine <= maxRow){
            unsigned int sizeOfPrintingLine = maxCol - minCol + 1;
            if(messageBoard.count(firstLine) > 0){
                if(firstLine < noNeedSpaceInPrint){
                    cout << " ";
                }
                cout << firstLine << ":";
                cout << this->readH(firstLine, minCol, sizeOfPrintingLine);
            }
            else{
                if(firstLine < noNeedSpaceInPrint){
                    cout << " ";
                }
                cout << firstLine << ":";
                for (int i = 0; i < sizeOfPrintingLine; i++)
                {
                    cout << SPACE;
                }
            }
            cout <<endl;
            firstLine++;
        }
    }

    void Board::updateH(unsigned int row, unsigned int col, string s)
    {
        pair<unsigned int, vector<char>> currentLine = messageBoard[row];
        unsigned int startOfPost = currentLine.first;
        vector<char> currentPost = currentLine.second;
        unsigned int sizeOfCurrentPost = currentPost.size();
        //if the given col is within the range of the existing post - an overlap
        if (startOfPost <= col && col <= startOfPost + sizeOfCurrentPost)
        {
            unsigned int stringIndex = 0;
            unsigned int i = col - startOfPost;
            for (; i < currentPost.size(); i++)
            {
                if (stringIndex == s.size())
                {
                    break;
                }
                currentPost.at(i) = s.at(stringIndex);
                stringIndex++;
            }
            while (stringIndex < s.size())
            {
                if (i >= sizeOfCurrentPost)
                {
                    currentPost.push_back(s.at(stringIndex));
                }
                else
                {
                    currentPost.at(i) = s.at(stringIndex);
                }
                i++;
                stringIndex++;
            }
            pair<unsigned int, vector<char>> updatedLine = {startOfPost, currentPost};
            messageBoard[row] = updatedLine;
        }
        //if the giving col isn't within range of the current post
        else
        {
            if (col < startOfPost)
            {
                vector<char> newPost = vector<char>();
                //adding the new post
                for (char c : s)
                {
                    newPost.push_back(c);
                }
                unsigned int newPostSize = col + s.length();
                //if there is a space between the two posts
                if (newPostSize < startOfPost)
                {
                    while (newPostSize < startOfPost)
                    {
                        newPost.push_back(SPACE);
                        newPostSize++;
                    }
                    for (char c : currentLine.second)
                    {
                        newPost.push_back(c);
                    }
                }
                //if the new post overrun part of the old post
                else if (newPostSize < startOfPost + sizeOfCurrentPost)
                {
                    unsigned int startCopy = col + newPostSize - startOfPost + 1;
                    while (startCopy < startOfPost + sizeOfCurrentPost)
                    {
                        newPost.push_back(currentPost.at(startCopy));
                        startCopy++;
                    }
                }
                pair<unsigned int, vector<char>> updatedLine = {col, newPost};
                messageBoard[row] = updatedLine;
            }
            //if the given col is bigger than the size of the whole post
            else
            {
                unsigned int totalSize = startOfPost + sizeOfCurrentPost;
                while (totalSize < col)
                {
                    currentPost.push_back(SPACE);
                    totalSize++;
                }
                for (char c : s)
                {
                    currentPost.push_back(c);
                }
                pair<unsigned int, vector<char>> updatedLine = {startOfPost, currentPost};
                messageBoard[row] = updatedLine;
            }
        }
    }

    void Board::updateV(unsigned int row, unsigned int col, char c)
    {
        pair<unsigned int, vector<char>> currentLine = messageBoard[row];
        unsigned int startOfPost = currentLine.first;
        vector<char> currentPost = currentLine.second;
        unsigned int sizeOfCurrentPost = currentPost.size();
        if (startOfPost <= col && col <= startOfPost + sizeOfCurrentPost)
        {
            currentPost.at(col - startOfPost) = c;
            messageBoard[row] = {startOfPost, currentPost};
        }
        else if (col < startOfPost)
        {
            vector<char> updatedPost = vector<char>();
            updatedPost.push_back(c);
            unsigned int i = col;
            while (i < startOfPost)
            {
                updatedPost.push_back(SPACE);
                i++;
            }
            for (char c : currentPost)
            {
                updatedPost.push_back(c);
            }
            messageBoard[row] = {col, updatedPost};
        }
        else
        {
            unsigned int i = startOfPost + sizeOfCurrentPost;
            while (i < col)
            {
                currentPost.push_back(SPACE);
                i++;
            }
            currentPost.push_back(c);
            messageBoard[row] = {startOfPost, currentPost};
        }
    }

    string Board::readH(unsigned int row, unsigned int col, unsigned int length)
    {
        string ans;
        //if there isn't existing row in the board - an empty post
        if (messageBoard.count(row) <= 0)
        {
            for (int i = 0; i < length; i++)
            {
                ans += SPACE;
            }
        }
        else
        {
            pair<unsigned int, vector<char>> line = messageBoard[row];
            unsigned int startOfPostIndex = line.first;
            vector<char> currentPost = line.second;
            //if the wanted post starts before the first char in the existing post - add spaces
            if (col < startOfPostIndex)
            {
                unsigned int sizeOfAns = 0;
                while (col < startOfPostIndex)
                {
                    ans += SPACE;
                    col++;
                    sizeOfAns++;
                }
                //if the size of ans isn't yet the wanted size
                if (sizeOfAns < length)
                {
                    unsigned int postIndex = 0;
                    for (; sizeOfAns < length; sizeOfAns++)
                    {
                        //if there isn't more posts in this line - add spaces
                        if (postIndex >= currentPost.size())
                        {
                            ans += SPACE;
                        }
                        else
                        {
                            ans += currentPost.at(postIndex);
                            postIndex++;
                        }
                    }
                }
            }

            else
            {
                unsigned int postSizeInLine = currentPost.size();
                //if the wanted col is bigger than the whole existing post - return only spaces
                if (col > postSizeInLine + startOfPostIndex)
                {
                    for (int i = 0; i < length; i++)
                    {
                        ans += SPACE;
                    }
                }
                else
                {
                    unsigned int readIndex = col - startOfPostIndex; //indexing to the post array
                    unsigned int i = 0;
                    while (i < length)
                    {
                        //if current index isn't it the range of the post
                        if (readIndex >= postSizeInLine)
                        {
                            ans += SPACE;
                        }
                        else
                        {
                            ans += currentPost.at(readIndex);
                        }
                        readIndex++;
                        i++;
                    }
                }
            }
        }
        return ans;
    }

    char Board::readV(unsigned int row, unsigned int col)
    {
        char ans = SPACE;
        //if the row exist in the board
        if (messageBoard.count(row) > 0)
        {
            pair<unsigned int, vector<char>> currentLine = messageBoard[row];
            unsigned int startOfPostIndex = currentLine.first;
            vector<char> currentPost = currentLine.second;
            //if the giving col is within the rang of the size of the existing post
            if (startOfPostIndex <= col && col <= startOfPostIndex + currentPost.size())
            {
                ans = currentPost.at(col - startOfPostIndex);
            }
        }

        return ans;
    }
}