#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "GameObject.h"
#include "Interactable.h"


using namespace std;
using namespace sf;

int main()
{
    //Loading boards
    vector<string> board_paths;
    board_paths.emplace_back("./boards/testboard1.brd");
    board_paths.emplace_back("./boards/testboard2.brd");
    board_paths.emplace_back("./boards/testboard3.brd");

    //Creating window for drawing
    RenderWindow window(VideoMode(800, 600), "Minesweeper");

    //Creating the initial board.
    GameObject game = GameObject();
    game.LoadTextures();
    game.LoadBoards(board_paths);
    game.ResetGame();

    //Create all the buttons and set their position
    Interactable debug_button = Interactable(*game.GetTexture("debug"));
    Interactable test_one = Interactable(*game.GetTexture("test_1"));
    Interactable test_two = Interactable(*game.GetTexture("test_2"));
    Interactable test_three = Interactable(*game.GetTexture("Test_3"));
    Interactable game_status = Interactable(*game.GetTexture("face_happy"));
    Interactable mine_counter_digit_one = Interactable(*game.GetTexture("digits"));
    Interactable mine_counter_digit_two = Interactable(*game.GetTexture("digits"));
    Interactable mine_counter_digit_three = Interactable(*game.GetTexture("digits"));
    debug_button.SetPosition(512, 512);
    test_one.SetPosition(576, 512);
    test_two.SetPosition(640, 512);
    test_three.SetPosition(704, 512);
    game_status.SetPosition(352,512);
    mine_counter_digit_one.SetPosition(42,512);
    mine_counter_digit_two.SetPosition(21,512);
    mine_counter_digit_three.SetPosition(0,512);

    //Initialize all the stuff for the game
    game.GenerateBoard(game_status);


    Event event;

    //Cap the number of times the game refreshes per event
    int frame = 0;

    //Used to keep track of the numbers for the bomb counter
    vector<int> bomb_numbers{game.GetCurrentBoard()->GetNumberMines(),-1,-1,-1};

    //Game loop
    while(window.isOpen()){

        //Get the number of mines
        bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();

        //Get each digit and store in bomb_numbers
        game.GetDigitCodes(bomb_numbers);

        //Set the bomb counter to each of the digits
        mine_counter_digit_one.ShiftDigits(bomb_numbers.at(1));
        mine_counter_digit_two.ShiftDigits(bomb_numbers.at(2));
        mine_counter_digit_three.ShiftDigits(bomb_numbers.at(3));

        //Information for keeping track of where the user clicks
        int row = -1;
        int column = -1;
        bool right_click = false;
        bool left_click = false;

        while(window.pollEvent(event)){
            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;

                //floor(x/width) is the horizontal component floor(y/height) is the vertical component
                case Event::MouseButtonPressed:
                    column = floor(event.mouseButton.x/32);
                    row = floor(event.mouseButton.y/32);
                    frame = 0;

                    //Used to keep track of if the user flagged something or clicked something
                    if(event.mouseButton.button == sf::Mouse::Right){
                        right_click = true;
                    }
                    else{
                        left_click = true;
                    }
                    break;

                default:
                    break;
            }
        }


        //Refresh 30 times per click.  There is probably a better way to do this.
        if(frame < 30){

            //If the user clicks in a region with the buttons and not tiles.
            if(row == 16 || row == 17){

                //If user clicks the face, reset the game with a new random board. Only button that works when lost game
                if(column == 11 || column == 12) {
                    cout << "Face clicked" << endl;
                    game.ResetGame();
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }

                //If player hits debug button, reveal the mines
                if(!game.GetLoss() && (column == 16 || column == 17)){
                    game.RevealMines();
                }

                //If the player hits test one, two, or three load the corresponding board
                if(!game.GetLoss() && (column == 18 || column == 19)){
                    game.SetBoard(game.RetrieveBoard("testboard1"));
                    cout << "Test1 clicked" << endl;
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }
                if(!game.GetLoss() && (column == 20 || column == 21)){
                    cout << "Test2 clicked" << endl;
                    game.SetBoard(game.RetrieveBoard("testboard2"));
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }
                if(!game.GetLoss() && (column == 22 || column == 23)){
                    cout << "Test3 clicked" << endl;
                    game.SetBoard(game.RetrieveBoard("testboard3"));
                    game.GenerateBoard(game_status);
                    bomb_numbers.at(0) = game.GetCurrentBoard()->GetNumberMines();
                }
            }

            //If player left clicks a tile, and the game is not lost
            if(row < 16 && left_click && !game.GetLoss()){

                //Get the tile clicked
                Interactable* clicked_tile = game.game_interactables_.at(row).at(column);

                //Check for mine, if not flagged set the loss condition and reveal mines
                if(clicked_tile->CheckForMine() && !clicked_tile->IsFlagged()){
                    game.SetLoss();
                    game_status.SetTexture(game.GetTexture("face_lose"));
                    if(!game.IsRevealed())
                        game.RevealMines();
                }

                //If the clicked tile is not flagged and not a mine
                else if (!clicked_tile->IsFlagged()) {

                    //Reveal it
                    clicked_tile->SetReveal(true);

                    //If no mines around, recursive reveal
                    if(clicked_tile->GetMineCount() == 0){
                        clicked_tile->RecursiveReveal(*game.GetCurrentBoard()->GetNumberMinesPtr());
                    }
                }
            }

            //If player right clicks a tile and game is not lost
            if(row < 16 && right_click && !game.GetLoss()){

                //Get the tile
                Interactable* clicked_tile = game.game_interactables_.at(row).at(column);

                //Check if it is revealed or flagged and  flag if not revealed and not flagged
                if(!clicked_tile->CheckForReveal() && !clicked_tile->IsFlagged()){
                    game.GetCurrentBoard()->SetNumberMines(-1);
                    clicked_tile->Flag();
                }

                //If flagged, remove the flag
                else if(clicked_tile->IsFlagged()){
                    game.GetCurrentBoard()->SetNumberMines(1);
                    clicked_tile->Flag();
                }
            }

            //Clear the window and draw each sprite for buttons
            window.clear(Color(255,255,255));
            window.draw(debug_button.GetSprite());
            window.draw(test_one.GetSprite());
            window.draw(test_two.GetSprite());
            window.draw(test_three.GetSprite());
            window.draw(game_status.GetSprite());
            window.draw(mine_counter_digit_one.GetSprite());
            window.draw(mine_counter_digit_two.GetSprite());
            window.draw(mine_counter_digit_three.GetSprite());

            //Draw the board with empty tiles, mines, hidden tiles
            for(unsigned i = 0; i < game.game_interactables_.size(); i++){
                for (unsigned int j = 0; j < game.game_interactables_.at(i).size(); j++) {

                    //Get sprite for each tile and the corresponding interactable
                    window.draw(game.board_tiles_.at(i).at(j)->GetSprite());
                    Interactable* current_tile = game.game_interactables_.at(i).at(j);

                    //If it is a mine and the board is revealed draw the mine
                    if(current_tile->CheckForMine() && game.board_revealed_){
                        current_tile->SetReveal(true);
                        current_tile->SetTexture(game.GetTexture("mine"));
                    }

                    //If it is a mine and the board is not revealed, do not draw the mine
                    if(current_tile->CheckForMine() && !game.board_revealed_){
                        current_tile->SetReveal(false);
                    }

                    //If the tile is not revealed, set its texture to a hidden tile, otherwise draw the corresponding texture
                    if(!current_tile->CheckForReveal()){
                        current_tile->SetTexture(game.GetTexture("tile_hidden"));
                    } else {
                        //If not a mine and no mines around, set to revealed texture
                        if(!current_tile->CheckForMine() && current_tile->GetMineCount() == 0)
                            current_tile->SetTexture(game.GetTexture("tile_revealed"));

                        //If not a mine and mines around, set to corresponding number of mines
                        if(!current_tile->CheckForMine() && current_tile->GetMineCount() != 0){
                            int number_mines = current_tile->GetMineCount();
                            string digit_name = "number_" + to_string(number_mines);
                            current_tile->SetTexture(game.GetTexture(digit_name));
                        }
                    }

                    //Draw the sprite
                    window.draw(current_tile->GetSprite());

                    //If the tile is flagged draw a flag
                    if(current_tile->IsFlagged() && !current_tile->CheckForReveal()){
                        current_tile->SetTexture(game.GetTexture("flag"));
                        window.draw(current_tile->GetSprite());
                    }


                }
            }
        }

        //If the game is not won, check for a win
        if(!game.Win())
            game.CheckWin();

        //If the game is won, flag each bomb and set the face to win status
        if(game.Win()){
            game_status.SetTexture(game.GetTexture("face_win"));

            for(unsigned i = 0; i < game.game_interactables_.size(); i++){
                for (unsigned int j = 0; j < game.game_interactables_.at(i).size(); j++){

                    Interactable* current_tile = game.game_interactables_.at(i).at(j);

                    if(!current_tile->IsFlagged() && current_tile->CheckForMine()){
                        current_tile->Flag();
                        game.GetCurrentBoard()->SetNumberMines(-1);
                    }
                }
            }
        }

        //Display the window and increment the frame count to prevent drawing many times
        window.display();
        frame++;

    }

    return 0;
}