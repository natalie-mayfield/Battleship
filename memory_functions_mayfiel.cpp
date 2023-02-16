 #include "memory_functions_mayfiel.h"

using namespace std;

void initMemorymayfiel(ComputerMemory &memory) {
   memory.mode        =  RANDOM;
   memory.hitRow      = 0;
   memory.hitCol      = 0;
   memory.hitShip     =  NONE;
   memory.fireDir     =  NONE;
   memory.fireDist    =  1;
   memory.lastResult  =  NONE;

   for (int i = 0; i < BOARDSIZE; i++) {
      for (int j = 0; j < BOARDSIZE; j++) {
         memory.grid[i][j] = EMPTY_MARKER;
      }
   }
}

bool checkMove(int, int, const ComputerMemory&);

string smartMovemayfiel(const ComputerMemory &memory) {
   // fill in the code here to make a smart move based on what information
   // appears in the computer's memory
   string move;
   string alphaRow = "ABCDEFGHIJ";
   string rowMove;
   string col = "123456789";
   string colMove;
   int prevRow = memory.hitRow;
   int prevCol = memory.hitCol;
   int dist = memory.fireDist;
   int lastResult = memory.lastResult;


   if(memory.hitRow < 10 && memory.hitRow >= 0){
        rowMove = alphaRow.at(memory.hitRow);
        }

   if(memory.hitCol < 10 && memory.hitCol >= 0){
        colMove = to_string(memory.hitCol + 1);
        }

        debug("memory.fireDir: " + to_string(memory.fireDir));

        if(memory.mode == RANDOM){


                 while(!checkMove(prevRow, prevCol, memory)) {
                        prevCol += 2;
                                 if(prevCol == 11){
                                        prevCol = 0;
                                  }
                                else if(prevCol == 10){
                                        prevCol = 1;
                                }
                        if(prevCol == 0 || prevCol == 1){
                                prevRow += 1;
                        }
                }


                colMove = to_string(prevCol + 1);
                rowMove = alphaRow.at(prevRow);

                move = rowMove + colMove;

//              debug("Enter random mode");
        }

        else if(memory.mode == SEARCH){
//              debug("Enter search mode");
//              debug(to_string(memory.fireDir));

                if(memory.fireDir == NORTH){
                        if(memory.grid[memory.hitRow - 1][memory.hitCol] == EMPTY_MARKER){      //if memory.fireDir is north and the move has not already been made, go>
                                prevRow = memory.hitRow - 1;
                        }
                        else if(memory.grid[memory.hitRow + 1][memory.hitCol] == EMPTY_MARKER){ //if going north isn't an option, go south
                                prevRow = memory.hitRow + 1;
                        }
                        else if(memory.grid[memory.hitRow][memory.hitCol + 1] == EMPTY_MARKER){ //if going south isn't an option, go east
                                prevCol = memory.hitCol + 1;
                        }
                        else{
                                prevCol = memory.hitCol - 1;                                    //if all other options are previously made moves, go west
                        }
                }
                else if(memory.fireDir == SOUTH){
                        if(memory.grid[memory.hitRow + 1][memory.hitCol] == EMPTY_MARKER){      //if memory.fireDir is south and the move hasn't already been made, go >
                                prevRow = memory.hitRow + 1;
                        }
                        else if(memory.grid[memory.hitRow][memory.hitCol + 1] == EMPTY_MARKER){ //if you can't go south, go east
                                prevCol = memory.hitCol + 1;
                        }
                        else if(memory.grid[memory.hitRow][memory.hitCol - 1] == EMPTY_MARKER){ //if you can't go east, go west
                                prevCol = memory.hitCol - 1;
                        }
                        else{
                                prevRow = memory.hitRow - 1;                                    //if you can't go east, go north
                        }
                }
                else if(memory.fireDir == EAST){
                        if(memory.grid[memory.hitRow][memory.hitCol + 1] == EMPTY_MARKER){      //if memory.fireDir is east and the move hasn't been previously made, g>
                                prevCol = prevCol + 1;
                        }
                        else if(memory.grid[memory.hitRow][memory.hitCol - 1] == EMPTY_MARKER){ //if you've already gone east, go west
                                prevCol = memory.hitCol - 1;
                        }
                        else if(memory.grid[memory.hitRow - 1][memory.hitCol] == EMPTY_MARKER){ //if you've already gone west, go north
                                prevRow = memory.hitRow - 1;
                        }
                        else{
                                prevRow = memory.hitRow + 1;                                    //if you've already went north, go south
                        }
                }
                else if(memory.fireDir == WEST){
                        if(memory.grid[memory.hitRow][memory.hitCol - 1] == EMPTY_MARKER){      //if memory.firedir is west and you haven't already done so with a prev>
                                prevCol = prevCol - 1;
                        }
                        else if(memory.grid[memory.hitRow - 1][memory.hitCol] == EMPTY_MARKER){ //if you've already gone west, go north
                                prevRow = memory.hitRow - 1;
                        }
                        else if(memory.grid[memory.hitRow + 1][memory.hitCol] == EMPTY_MARKER){ //if you've already gone north, go south
                                prevRow = memory.hitRow + 1;
                        }
                        else{
                                prevCol = memory.hitCol + 1;                                    //if you've already gone south, go east
                        }

                }
                else{
                        debug("This search direction shouldn't happen");
                }

                colMove = to_string(prevCol + 1);
                rowMove = alphaRow.at(prevRow);
        //      debug("move: " + move);
                move = rowMove + colMove;
                debug("move: " + move);

        }

        else if(memory.mode == DESTROY){
                debug("Enter destroy mode");
                if(memory.fireDir == NORTH){
                        if(memory.fireDist == 1 && memory.grid[memory.hitRow - 1][memory.hitCol] == EMPTY_MARKER){                                              //if fi>
                                prevRow = memory.hitRow - 1;
                        }
                        else if(memory.fireDist == 2 && memory.grid[memory.hitRow - 2][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow - 2;
                        }
                        else if(memory.fireDist == 3 && memory.grid[memory.hitRow - 3][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow - 3;
                        }
                        else if(memory.fireDist == 4 && memory.grid[memory.hitRow - 4][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow - 4;
                        }
                }

                else if(memory.fireDir == SOUTH){
                        if(memory.fireDist == 1 && memory.grid[memory.hitRow + 1][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow + 1;
                        }
                        else if(memory.fireDist == 2 && memory.grid[memory.hitRow + 2][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow + 2;
                        }
                        else if(memory.fireDist == 3 && memory.grid[memory.hitRow + 3][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow + 3;
                        }
                        else if(memory.fireDist == 4 && memory.grid[memory.hitRow + 4][memory.hitCol] == EMPTY_MARKER){
                                prevRow = memory.hitRow + 4;
                        }
                }

                else if (memory.fireDir == EAST){                                                       //if the ship is horizontal
                        if(memory.fireDist == 1 && memory.grid[memory.hitRow][memory.hitCol + 1] == EMPTY_MARKER){                                              //if fi>
                                prevCol = memory.hitCol + 1;
                        }
                        else if(memory.fireDist == 2 && memory.grid[memory.hitRow][memory.hitCol + 2] == EMPTY_MARKER){                                                >
                                prevCol = memory.hitCol + 2;
                        }
                        else if(memory.fireDist == 3 && memory.grid[memory.hitRow][memory.hitCol + 3] == EMPTY_MARKER){
                                prevCol = memory.hitCol + 3;
                        }
                        else if(memory.fireDist == 4 && memory.grid[memory.hitRow][memory.hitCol + 4] == EMPTY_MARKER){
                                prevCol = memory.hitCol + 4;
                        }
                }

                else if(memory.fireDir == WEST){
                        if(memory.fireDist == 1 && memory.grid[memory.hitRow][memory.hitCol - 1] == EMPTY_MARKER){
                                prevCol = memory.hitCol - 1;
                        }
                        else if(memory.fireDist == 2 && memory.grid[memory.hitRow][memory.hitCol - 2] == EMPTY_MARKER){
                                prevCol = memory.hitCol - 2;
                        }
                        else if(memory.fireDist == 3 && memory.grid[memory.hitRow][memory.hitCol - 3] == EMPTY_MARKER){
                                prevCol = memory.hitCol - 3;
                        }
                        else if(memory.fireDist == 4 && memory.grid[memory.hitRow][memory.hitCol - 4] == EMPTY_MARKER){
                                prevCol == memory.hitCol - 4;
                        }
                }
        }


