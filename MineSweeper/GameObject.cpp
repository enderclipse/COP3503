//
// Created by JOSHUA HADDAD on 2019-04-02.
//

#include "GameObject.h"
GameObject::GameObject() {
    win_ = false;
    lose_ = false;
    board_revealed_ = false;

}

//Loads all textures provided
void GameObject::LoadTextures() {
    Texture texture;
    string imagePaths[] = {"./images/debug.png", "./images/digits.png", "./images/face_happy.png","./images/face_lose.png",
                           "./images/face_win.png", "./images/flag.png", "./images/mine.png", "./images/number_1.png",
                           "./images/number_2.png","./images/number_3.png","./images/number_4.png","./images/number_5.png",
                           "./images/number_5.png","./images/number_6.png", "./images/number_7.png","./images/number_8.png",
                           "./images/test_1.png","./images/test_2.png","./images/Test_3.png", "./images/tile_hidden.png","./images/tile_revealed.png"};

    //For each path in the imagePaths array, name the texture everything after / and before .png, and place in map
    for(string paths : imagePaths){
        Texture texture;
        texture.loadFromFile(paths);
        texture.setSmooth(true);

        long begin = paths.find("s/")+2;
        long end = paths.find(".png",2);

        string name = paths.substr(begin, end-begin);
        textures_.emplace(name, texture);
    }
}

//Loads all test boards into a map with name everything after / and before .brd
void GameObject::LoadBoards(vector<string> paths){
    map<string, Board> boards;
    for(int i = 0; i < paths.size(); i++){
        Board currentBoard;
        currentBoard.LoadFromFile(paths.at(i));
        string path = paths.at(i);

        long begin = path.find("s/")+2;
        long end = path.find(".brd",2);

        string name = path.substr(begin, end-begin);
        all_levels_.emplace(name, currentBoard);
    }

}

//Getters
Texture* GameObject::GetTexture(string key){
    return &textures_[key];
}

Board GameObject::RetrieveBoard(string key) {
    return all_levels_[key];
}

//Method takes a vector and sets the three elements to either: the number needed, nothing, or -
void GameObject::GetDigitCodes(vector<int> &in_data) {
    bool negative = false;

    //The first number of the array is the number of mines. If negative, take note and convert to positive.
    if(in_data.at(0) < 0){
        negative = true;
        in_data.at(0) *= -1;
    }

    //Get a string of the number of mines
    string number = to_string(in_data.at(0));

    //Depending on the length of the string, set the digits accordingly by converting the characters in number string to an int
    if(number.length() == 1){
        in_data.at(1) = stoi(number);
        in_data.at(2) = 0;

        //If the number is negative, set the closest empty digit to a negative
        negative ?  in_data.at(3) = 10 : in_data.at(3) = 0;
    }
    if(number.length() == 2){
        in_data.at(1) = stoi(number.substr(1,1));
        in_data.at(2) = stoi(number.substr(0,1));
        negative ?  in_data.at(3) = 10 : in_data.at(3) = 0;
    }
    if(number.length() == 3){
        in_data.at(1) = stoi(number.substr(2,1));
        in_data.at(2) = stoi(number.substr(1,1));
        in_data.at(3) = stoi(number.substr(0,1));
    }

}

Board* GameObject::GetCurrentBoard() {
    Board* ptr = &current_board_;
    return ptr;
}

void GameObject::CheckWin() {
    win_ = true;
    for(int i = 0; i < game_interactables_.size(); i++){
        for(int j = 0; j < game_interactables_.at(0).size(); j++){
            if(game_interactables_.at(i).at(j)->CheckForMine())
                continue;
            if(!game_interactables_.at(i).at(j)->CheckForReveal())
                win_ = false;
        }
    }
}

bool GameObject::GetLoss() {
    return lose_;
}

bool GameObject::Win() {
    return win_;
}

bool GameObject::IsRevealed() {
    return board_revealed_;
}

//Setters
void GameObject::SetBoard(Board board) {
    current_board_ = board;
}

void GameObject::SetLoss() {
    lose_ = true;
}

void GameObject::RevealMines() {
    board_revealed_ = !board_revealed_;
}

//Game functionality

//From the current board, generate the interactables for the board
void GameObject::GenerateBoard(Interactable &game_status) {

    //Set the face to be the happy face, set loss to false, win to false, and reveal to false.
    game_status.SetTexture(GetTexture("face_happy"));
    lose_ = false;
    win_ = false;
    board_revealed_ = false;

    //Clear all the interactables from the previous game
    game_interactables_.clear();

    //Loop across the board setting the tiles
    for(int i = 0; i < current_board_.GetHeight(); i ++){

        //One vector of interactables for the foreground, one for the background
        vector<Interactable*> row;
        vector<Interactable*> background_row;


        for(int j = 0; j < current_board_.GetLength(); j ++){

            //Set background as tile_revealed, and foreground as hidden
            Interactable* background_piece = new Interactable(*GetTexture("tile_revealed"));
            Interactable* piece = new Interactable(*GetTexture("tile_hidden"));

            //If the piece at r,c is a mine, set the interactable to a mine, else set it to not a mine
            if(current_board_.IsMine(i,j))
                piece->SetMine(true);

            if(!current_board_.IsMine(i,j))
                piece->SetMine(false);

            //Set the position of the background and foreground spaced 32 spaces apart
            background_piece -> SetPosition(j*32,i*32);
            piece -> SetPosition(j*32,i*32);

            //Add the pieces to their corresponding vector
            row.push_back(piece);
            background_row.push_back(background_piece);
        }

        //Once each row is generated, push the background to the board_tiles and the foreground to the interactables field
        game_interactables_.push_back(row);
        board_tiles_.push_back(background_row);
    }

    //Get pointers to each of the surrounding tiles for each tile
    SetSurroundings();
}


//Generate a new random board
void GameObject::ResetGame() {

    //Generate new board
    current_board_ = Board(25,16);

    //Populate board with random stuff!
    current_board_.RandomBoard();

}

//Takes each tile and gets pointers to the surrounding tiles, setting to nullptr if needed
void GameObject::SetSurroundings() {

    //For each row and column
    for(unsigned int c = 0; c < game_interactables_.size(); c++) {
        for (unsigned int r = 0; r < game_interactables_.at(0).size(); r++) {

            //Get the current tile at row r and column c
            Interactable *current_inspected_interactable = game_interactables_.at(c).at(r);

            //Loop through getting the piece to the upper left, above, upper right, left, right, etc
            for (int row = -1; row <= 1; row++) {
                for (int column = -1; column <= 1; column++) {

                    //Try to set a pointer to the interactable, if out of bounds of the array, set as an edge
                    try {
                        Interactable* adjacent_tile = game_interactables_.at(c + column).at(r + row);

                        //If the adjacent tile is a mine, increment the mine count of the tile being inspected
                        if (adjacent_tile->CheckForMine()) {
                            current_inspected_interactable->IncrementMineCount();
                        }

                        //Set the current tile to have a pointer to the adjacent tile
                        current_inspected_interactable->SetAdjacent(adjacent_tile);
                    }
                    catch (const out_of_range &edge) {
                        current_inspected_interactable->SetAdjacent(nullptr);
                    }
                }
            }
        }
    }
}








