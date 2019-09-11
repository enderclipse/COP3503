//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#include "Board.h"

//Initialize the board to have a length and height and set number of mines to 0
Board::Board(int _length, int _height){
    number_of_mines_ = 0;
    height_ = _height;
    length_ = _length;
}

Board::Board() {
    height_ = 0;
    length_ = 0;
    number_of_mines_ = 0;
}

//Get a board from a file path
void Board::LoadFromFile(string path) {
    ifstream board_reader(path);
    string value;
    vector<string> lines;

    //If the filepath exists
    if(board_reader.is_open()){

        //While the board file has lines to give, read the lines and add them to a vector to parse
        while(board_reader >> value){
            lines.push_back(value);
        }
    }

    //Get the length and set height to 0 for now.
    length_ = lines.at(0).length();
    height_ = 0;

    //Parse the lines
    StoreLines(lines);

}

void Board::StoreLines(const vector<string>& lines){

    //For each line in lines vector
    for(string line : lines){
        vector<Tile> tile_lines;

        //Substring each piece of the line.  If 1 set to a bomb, otherwise set to not a bomb
        for(int j = 0; j < length_; j++){
            if(line.substr(j, 1) == "1"){
                number_of_mines_++;
                Tile current_tile = Tile(true);
                tile_lines.push_back(current_tile);
            }
            else{
                Tile current_tile = Tile();
                tile_lines.push_back(current_tile);
            }
        }

        //Add tile to board and increment height after each line
        board_tiles_.push_back(tile_lines);
        height_++;
    }
}

//Generate a random board
void Board::RandomBoard() {

    //Set number of mines to be 50
    number_of_mines_ = 50;

    //Generate an empty board
    for(int i = 0; i < height_; i++){
        vector<Tile> tile_lines;
        for(int j = 0; j < length_; j++){
            Tile current_tile = Tile(false);
            tile_lines.push_back(current_tile);
        }
        board_tiles_.push_back(tile_lines);
    }

    //Set mines at random positions x,y throughout the board
    for(int i = 0; i < number_of_mines_; i++){
        int x = rand() % 16;
        int y = rand() % 25;

        //If mine is already set at this position, try until an empty position is found
        while(board_tiles_.at(x).at(y).CheckMine()){
            x = rand() % 16;
            y = rand() % 25;
        }

        //Set the mine
        board_tiles_.at(x).at(y).SetMine();
    }
}

//Used to increment the number of mines on the board based on flags
void Board::SetNumberMines(int shift) {
    number_of_mines_ += shift;
}

//Helper method for debugging the board if needed
void Board::PrintBoard(){
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < length_; j++){
            cout << board_tiles_.at(i).at(j).CheckMine() << " ";
        }
        cout << endl;
    }
}

//Getters
int Board::GetHeight() {
    return height_;
}

int Board::GetLength() {
    return length_;
}

bool Board::IsMine(int row, int column) {
    if(row > board_tiles_.size()-1 || row < 0 || column > board_tiles_.at(0).size()-1 || column < 0)
        return false;
    return board_tiles_.at(row).at(column).CheckMine();
}

int Board::GetNumberMines() {
    return number_of_mines_;
}

int* Board::GetNumberMinesPtr() {
    int* ptr = &number_of_mines_;
    return ptr;
}




