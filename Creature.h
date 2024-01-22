#include <map>
#include <vector>
using namespace std;

enum class Stat {Health, Speed, Attack, Energy, EnergyRegen};
enum class Actions {Regen, Breed, Walk, Attack, Eat};

class FieldManager;

class Creature
{
public:
    int evolutionPoints = 10; 

    map<Stat, float> stats;
    map<Actions,int> actions;

    vector<int> vectorValues;
    vector<Actions> vectorActions;

    int position[2];
    char symbol;
    FieldManager* _fieldManager;
    float MaxHealth = 0;
    float MaxEnergy = 0;

    int age = 0;
    string color = "\033[0m";   // base color

    Creature(FieldManager* fieldManager, float health, float speed, float attack, float energy, float energyRegen);
    void IdentifyYourself();
    bool CallAction(Actions action);
    pair<int, int> getRandomNumberAndIndex(vector<int>& arr);

    bool Regen();
    bool Breed();
    bool Walk();
    bool Attack();
    bool Eat();
    void Execute();
};