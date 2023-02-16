#include <string>
#include "memory.h"

using namespace std;

void   initMemorymayfiel(ComputerMemory &memory);
void   updateMemorymayfiel(int row, int col, int result, ComputerMemory &memory);
string smartMovemayfiel(const ComputerMemory &memory);
