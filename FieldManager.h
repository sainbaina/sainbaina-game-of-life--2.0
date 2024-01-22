#include <map>
#include <vector>
#include "Position.h"
using namespace std;

class Creature;

class FieldManager
{
public:
    #pragma region tilesArround
    const Position tilesArround[8]
    {
        Position(-1,-1),
        Position(-1,0),
        Position(-1,1),
        Position(0,-1),
        Position(0,1),
        Position(1,-1),
        Position(1,0),
        Position(1,1)
    };
    #pragma endregion

    const int fieldWidth = 10; //50;
    const int fieldHeight = 10; //24;
    char** fieldArray;
    vector<Creature*> creaturesOnField;

    FieldManager();
    void SetRandomPosition(Creature *creature, int height, int width);
    void Kill(Creature* creature);
    void DrawField();
    vector<Position> CorrectMoves(Position currPos);
};