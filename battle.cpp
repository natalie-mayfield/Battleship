#include "battleship.h"
#include "memory.h"                                                   
#include "memory_functions_mayfiel.h"                                      
int main() {
   Board          humanBoard, computerBoard;
        ComputerMemory memory;                                              

   bool           done = false;
   string         humanMove, computerMove, message;
   int            numHumanShipsSunk = 0, numComputerShipsSunk = 0;
   int            humanRow, humanColumn, computerRow, computerColumn;
   int            checkValue, humanResult, computerResult;

   // Welcome the player to the game
   welcome(true);

   // Initialize the game boards
   initializeBoard(humanBoard);
   initializeBoard(computerBoard);
        initMemorymayfiel(memory);                                             

   // Play the game until one player has sunk the other's ships
   while (!done) {

      // blank the screen to show the game situation
      clearTheScreen();

      // Display the game situation
      displayBoard(1,  5, HUMAN, humanBoard);
      displayBoard(1, 40, COMPUTER, computerBoard);

      // get the player's move
//      humanMove  = getResponse(15, 0, "Please enter your move:  ");
        humanMove = randomMove();
      checkValue = checkMove(humanMove, computerBoard, humanRow, humanColumn);

                // validate the move
      while (checkValue != VALID_MOVE) {
         if (checkValue== ILLEGAL_FORMAT) {
            writeMessage(18, 0, "The move "+humanMove+" has an illegal format");
         } else if (checkValue == REUSED_MOVE) {
            writeMessage(18, 0, "The move "+humanMove+" has already been used");
         }

                        // if necessary, get another move
   //      humanMove  = getResponse(15, 0, "Please enter your move:  ");
           humanMove = randomMove();
      checkValue = checkMove(humanMove, computerBoard, humanRow, humanColumn);

                // validate the move
      while (checkValue != VALID_MOVE) {
         if (checkValue== ILLEGAL_FORMAT) {
            writeMessage(18, 0, "The move "+humanMove+" has an illegal format");
         } else if (checkValue == REUSED_MOVE) {
            writeMessage(18, 0, "The move "+humanMove+" has already been used");
         }

                        // if necessary, get another move
   //      humanMove  = getResponse(15, 0, "Please enter your move:  ");
           humanMove = randomMove();

           checkValue = checkMove(humanMove, computerBoard, humanRow,humanColumn);
      }

      // get the computer's move
      computerMove = smartMovemayfiel(memory);                          
      while (checkMove(computerMove, humanBoard, computerRow, computerColumn)
             != VALID_MOVE) {
         computerMove = randomMove();
      }

      // execute the moves on the respective boards
      humanResult    = playMove(humanRow, humanColumn, computerBoard);
      computerResult = playMove(computerRow, computerColumn, humanBoard);
        updateMemorymayfiel(computerRow,    computerColumn,                
                       computerResult, memory);                      

      // blank the screen to show the new game situation
      clearTheScreen();

      // Display the game situation
      displayBoard(1,  5, HUMAN, humanBoard);
      displayBoard(1, 40, COMPUTER, computerBoard);

      // Display the move choices
      writeMessage(15, 0, "You chose:  " + humanMove);
      writeMessage(16, 0, "The computer chooses:  " + computerMove);

      // Show the results of the moves
      writeResult(18, 0, humanResult, HUMAN);
      writeResult(19, 0, computerResult, COMPUTER);

      // record any sunken ships
      if (isASunk(humanResult)) { numHumanShipsSunk++; }
      if (isASunk(computerResult)) { numComputerShipsSunk++; }

      // determine if we have a winner
      if (numHumanShipsSunk == 5 || numComputerShipsSunk == 5) {
     done = true;
      } else {
         // pause to let the user assess the situation
         pauseForEnter();
      }
   }

   // Display the game situation once more, showing where each player's ships
   // are located
   displayBoard(1,  5, HUMAN, humanBoard);
   displayBoard(1, 40, HUMAN, computerBoard);

   // Announce the winner
   if (numHumanShipsSunk == 5 && numComputerShipsSunk == 5) {
      writeMessage(21, 1, "The game is a tie");
   } else if (numHumanShipsSunk == 5) {
      writeMessage(21, 1, "Congratulations, you won");
   } else {
      writeMessage(21, 1, "Awwwwh, you lost");
   }

   // pause to let the result of the game sink in
   pauseForEnter();
   clearTheScreen();

   return 0;
}

