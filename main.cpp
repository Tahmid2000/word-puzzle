/* Tahmid Imran
 * assignment1.cpp
 * The purpose of this project is to iterate through a crossword puzzle
 * to find specified words using 2 files.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cctype>

using namespace std;


enum direction {LEFT_RIGHT, RIGHT_LEFT, DOWN, UP, RIGHT_DOWN, RIGHT_UP, LEFT_DOWN, LEFT_UP};
direction dir;

const int MAX = 50;

//sturct for the attributes of the puzzle
struct wordGame
{
    int version;
    int numberRows;
    int numberColumns;
    char puzzle[MAX][MAX];
};

//struct for the attributes of a the word being searched for in the puzzle
struct wordFind
{
    string word;
    bool found;
    int row;
    int column;
    direction where;
    int foundCount;
};

// find the word that is part of the wordFind structure inside the wordGame structure.
// If the word is found the wordFind structure will be updated.
void findWord(wordGame &game, wordFind &theFind){
    theFind.foundCount = 0; //how many times the word was found
    theFind.found = false; //changes to true if word found
    theFind.row = 0; //the row of where the first letter of the word was found
    theFind.column = 0; //the column of where the first letter of the word was found
    int foundRow = 0; //the row of where the word was found
    int foundCol = 0; //the column of where the word was found
    
    //LEFT_RIGHT
    int textLen = static_cast<int>(theFind.word.length());
    int indexCounter = 0;
    int i = 0;
    //checks puzzle from left to right
    while(i < game.numberRows){
        for(int j = 0; j < (game.numberColumns - textLen + 1); j++){
            //i - row
            //j - col
            //stops loop if out of bounds
            if(i > game.numberRows || j > game.numberColumns){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[i][j] == theFind.word.at(0)) && (game.puzzle[i][j+1] == theFind.word.at(1)) && (game.puzzle[i][j + (textLen - 2)] == theFind.word.at(textLen - 2))){
                theFind.row = i;
                theFind.column = j;
                indexCounter = 0;
                //if the check above works, then the rest of the column is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row][theFind.column + k] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = LEFT_RIGHT;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i++;
    }
     
    //RIGHT_LEFT
    i = 0;
    //checks puzzle from right to left
    while(i < game.numberRows){
        for(int j = game.numberColumns - 1; j >= (textLen - 1); j--){
            //i - row
            //j - col
            //stops loop if out of bounds
            if(i > game.numberRows || j < 0){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if(game.puzzle[i][j] == theFind.word.at(0) && (game.puzzle[i][j - 1] == theFind.word.at(1)) && (game.puzzle[i][j - (textLen - 2)] == theFind.word.at(textLen - 2))){
                theFind.row = i;
                theFind.column = j;
                indexCounter = 0;
                //if the check above works, then the rest of the column is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row][theFind.column - k] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = RIGHT_LEFT;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i++;
    }
        
    //DOWN
    i = 0;
    //checks puzzle top to bottom
    while(i < game.numberColumns){
        for(int j = 0; j < (game.numberRows - textLen + 1); j++){
            //i - col
            //j - row
            //stops loop if out of bounds
            if(i > game.numberColumns || j > game.numberRows){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[j][i] == theFind.word.at(0)) && (game.puzzle[j + 1][i] == theFind.word.at(1)) && (game.puzzle[j + (textLen - 2)][i] == theFind.word.at(textLen - 2))){
                theFind.column = i;
                theFind.row = j;
                indexCounter = 0;
                //if the check above works, then the rest of the row is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row + k][theFind.column] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = DOWN;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i++;
    }
        
    //UP
    i = 0;
    //checks puzzle bottom top
    while(i < game.numberColumns){
        for(int j = game.numberRows - 1; j >= (textLen - 1); j--){
            //i - col
            //j - row
            //stops loop if out of bounds
            if(i > game.numberColumns || j < 0){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[j][i] == theFind.word.at(0))  && (game.puzzle[j - 1][i] == theFind.word.at(1)) && (game.puzzle[j - (textLen - 2)][i] == theFind.word.at(textLen - 2))){
                theFind.column = i;
                theFind.row = j;
                indexCounter = 0;
                //if the check above works, then the rest of the row is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row - k][theFind.column] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = UP;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i++;
    }
    
    //RIGHT-DOWN
    i = 0;
    //checks puzzle diagonally downward and to the right
    while(i < game.numberRows){
        for(int j = 0; j < (game.numberColumns - textLen + 1); j++){
            //i - row
            //j - col
            //stops loop if out of bounds
            if(i > game.numberRows || j > game.numberColumns){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[i][j] == theFind.word.at(0)) && (game.puzzle[i + 1][j + 1] == theFind.word.at(1)) && (game.puzzle[i + (textLen - 2)][j + (textLen - 2)] == theFind.word.at(textLen - 2))){
                theFind.row = i;
                theFind.column = j;
                indexCounter = 0;
                //if the check above works, then the rest of the row and column is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row + k][theFind.column + k] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = RIGHT_DOWN;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i++;
    }
    
    //RIGHT-UP
    i = 0;
    //checks puzzle diagonally upward and to the right
    while(i < game.numberColumns){
        for(int j = game.numberRows - 1; j >= (textLen - 1); j--){
            //i - col
            //j - row
            //stops loop if out of bounds
            if(i > game.numberColumns || j < 0){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[j][i] == theFind.word.at(0))  && (game.puzzle[j - 1][i + 1] == theFind.word.at(1)) && (game.puzzle[j - (textLen - 2)][i + (textLen - 2)] == theFind.word.at(textLen - 2))){
                theFind.column = i;
                theFind.row = j;
                indexCounter = 0;
                //if the check above works, then the rest of the row and column is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row - k][theFind.column + k] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = RIGHT_UP;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
            i++;
    }
    
    //LEFT-DOWN
    i = 0;
    //checks puzzle diagonally downward and to the left
    while(i < game.numberRows){
        for(int j = game.numberColumns - 1; j >= 0; j--){
            //i - row
            //j - col
            //stops loop if out of bounds
            if(i > game.numberRows || j < 0){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[i][j] == theFind.word.at(0)) && (game.puzzle[i + 1][j - 1] == theFind.word.at(1)) && (game.puzzle[i + (textLen - 2)][j - (textLen - 2)] == theFind.word.at(textLen - 2))){
                theFind.row = i;
                theFind.column = j;
                indexCounter = 0;
                //if the check above works, then the rest of the row and column is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row + k][theFind.column - k] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = LEFT_DOWN;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i++;
    }
    
    //LEFT-UP
    i = game.numberRows - 1;
    //checks puzzle diagonally upward and to the left
    while(i >= 0){
        for(int j = game.numberColumns - 1; j >= 0; j--){
            //i - row
            //j - col
            //stops loop if out of bounds
            if(i < 0|| j < 0){
                return;
            }
            //checks if at the current index, the first letter, the second letter, and second to last letter is the same as the current word being searched for
            else if((game.puzzle[i][j] == theFind.word.at(0)) && (game.puzzle[i - 1][j - 1] == theFind.word.at(1)) && (game.puzzle[i - (textLen - 2)][j - (textLen - 2)] == theFind.word.at(textLen - 2))){
                theFind.row = i;
                theFind.column = j;
                indexCounter = 0;
                //if the check above works, then the rest of the row and column is checked with each index of each letter
                for(int k = 1; k < textLen; k++){
                    if(game.puzzle[theFind.row - k][theFind.column - k] == theFind.word.at(k)){
                        indexCounter++;//keeps track of how many letters of the word were found
                    }
                }
            }
        }
        //if the index counter matches the size of the word then the found, where, foundcount, foundRow/Column are set to their appropriate values
        if(indexCounter == (textLen - 1)){
            theFind.found = true;
            theFind.where = LEFT_UP;
            theFind.foundCount++;
            foundRow = theFind.row;
            foundCol = theFind.column;
            indexCounter = 0;
        }
        i--;
    }
    
    if(theFind.foundCount == 1){
        theFind.row = foundRow;
        theFind.column = foundCol;
    }
}

// read the puzzle from the input file and update the wordGame structure.
bool readPuzzle(wordGame &game, string inputFileName){
    game.version = 1;
    ifstream inFile;
    inFile.open(inputFileName);
    if(inFile.is_open()){
        inFile >> game.numberRows;
        inFile >> game.numberColumns;
        for(int i = 0; i < game.numberRows; i++){
            for(int j = 0; j < game.numberColumns; j++){
                inFile >> game.puzzle[i][j];
            }
        }
    }
    else
        return false;
    
    //bonus
    game.version = 2;
    //checks if rows and cols are within range
    if(game.numberRows < 1 || game.numberRows > MAX || game.numberColumns < 1 || game.numberColumns > MAX)
        return false;
    //checks if end of file
    if(inFile.eof())
        return false;
    //changes puzzle to all uppercase
    for(int i = 0;  i< game.numberRows; i++){
        for(int j = 0; j < game.numberColumns; j++){
            game.puzzle[i][j] = toupper(game.puzzle[i][j]);
        }
    }
    inFile.close();
    return true;
}

// display the contents of the puzzle
void displayPuzzle(wordGame &game){
    for(int i =0; i < game.numberRows; i++){
        for(int j = 0; j < game.numberColumns; j++){
            cout << game.puzzle[i][j];
        }
    cout << endl;
    }
}

int main()
{
    wordGame game1;
    wordFind word1;
    bool open = true;
    string puzzlefile;
    string wordfile;
    cin >> puzzlefile;
    cin >> wordfile;
    
    //checks to see if puzzle file was properly opened
    if(readPuzzle(game1, puzzlefile) == false){
        cout << "The puzzle file " << "\""  << puzzlefile << "\"" << " could not be opened or is invalid" << endl;
        open = false;
    }
    else{
        cout << "The puzzle from file " << "\"" << puzzlefile << "\"" << endl;
        displayPuzzle(game1);
    }
    
    ifstream inFile;
    string line;
    inFile.open(wordfile);
    //checks to see if word file was properly opened
    if(!(inFile.is_open() == true) && open == true){
        cout << "The puzzle file " << "\""  << wordfile << "\"" << " could not be opened or is invalid" << endl;
    }
    //loops through puzzle file to see where the words are in puzzle
    while(inFile >> word1.word && open == true){
        cin.clear();
        //bonus - changes word in word file to upper case
        if(game1.version == 2)
            transform(word1.word.begin(), word1.word.end(), word1.word.begin(), ::toupper);
        else
            game1.version = 1;
        findWord(game1, word1);
        //outputs a different string depending on the direction of where the word was found
        if(word1.found == true && word1.foundCount == 1){
            if(word1.where == LEFT_RIGHT)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "right"<< endl;
            if(word1.where == RIGHT_LEFT)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "left"<< endl;
            if(word1.where == DOWN)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "down"<< endl;
            if(word1.where == UP)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "up"<< endl;
            if(word1.where == RIGHT_DOWN)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "right/down"<< endl;
            if(word1.where == RIGHT_UP)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "right/up"<< endl;
            if(word1.where == LEFT_DOWN)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "left/down"<< endl;
            if(word1.where == LEFT_UP)
                cout << "The word " << word1.word << " was found at (" << (word1.row + 1) << ", " << (word1.column + 1) << ") - " << "left/up"<< endl;
        }
        //prints if more than one instance of word was found
        else if(word1.foundCount > 1)
            cout << "The word " << word1.word << " was found " << word1.foundCount << " times" << endl;
        else
            cout << "The word " << word1.word << " was not found" << endl;
        
    }
    inFile.close();
}
