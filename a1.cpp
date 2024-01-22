#include <iostream>
#include <list>
#include <chrono>
#include <vector>
#include <memory>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <map>
#include <cmath>
#include <algorithm>
#include "Creature.h"
#include "FieldManager.h"
using namespace std;

bool Creature::Walk()
{
    vector<pair<int,int>> possibleMoves;

    int currX = this->position[1];
    int currY = this->position[0];

    vector<Position> movePositions = _fieldManager->CorrectMoves(Position(currX,currY));

    for (Position pos : movePositions)
    {
        if((*_fieldManager).fieldArray[pos.Y][pos.X] != '_' || !isdigit((*_fieldManager).fieldArray[pos.Y][pos.X])) continue;

        possibleMoves.push_back(pair(pos.X,pos.Y));
    }

    if(possibleMoves.size() != 0)
    {
        pair<int,int> move = possibleMoves[rand()%possibleMoves.size()];

        char letter = (*_fieldManager).fieldArray[currY][currX];
        (*_fieldManager).fieldArray[move.first][move.second] = letter;
        (*_fieldManager).fieldArray[currY][currX] = '_';
        this->position[0] = move.first;
        this->position[1] = move.second;

        return true;
    }

    return false;
}

bool Creature::Attack()
{
    // cout << "attack" << '\t';
    vector<Creature*> possibleVictims;
    vector<pair<int,int>> possibleFoodMoves;

    int currX = this->position[1];
    int currY = this->position[0];

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            int nextY = currY + y;
            int nextX = currX + x;
            
            if (x == 0 && y == 0) continue;

            if(currY + y == _fieldManager->fieldHeight)
            {
                nextY = 0;
            }
            else if(currY + y == -1)
            {
                nextY = _fieldManager->fieldHeight - 1;
            } 
            if(currX + x == _fieldManager->fieldWidth)
            {
                nextX = 0;
            }
            else if(currX + x == -1)
            {
                nextX = _fieldManager->fieldWidth - 1;
            }

            if((*_fieldManager).fieldArray[nextY][nextX] == '_') continue; // possibleFoodMoves.push_back(pair(nextY,nextX));

            for ( Creature* creature : _fieldManager->creaturesOnField )
            {
                if (creature->position[0] == nextY && creature->position[1] == nextX)
                {
                    possibleVictims.push_back(creature);
                }
            }
        }
    }

    if(possibleVictims.size() != 0)
    {
        Creature* victim = possibleVictims[rand()%possibleVictims.size()];

        victim->stats[Stat::Health] -= ( this->stats[Stat::Attack]); //* this->stats[Stat::Health] / this->MaxHealth);

        if (victim->stats[Stat::Health] <= 0)
        {
            int foodAmmount = victim->stats[Stat::Energy];
            _fieldManager->fieldArray[victim->position[0]][victim->position[1]] = int(victim->stats[Stat::Energy]) % 10 + '0';
            // foodAmmount -= foodAmmount % 10;

            // while(foodAmmount > 0)
            // {
            //     if (possibleFoodMoves.size() != 0)
            //     {
            //         pair<int,int> move = possibleFoodMoves[rand()%possibleFoodMoves.size()];
            //         _fieldManager->fieldArray[move.first][move.second] = (foodAmmount % 10 + '0');
            //         foodAmmount -= foodAmmount % 10;
            //     }
            //     else
            //     {
            //         break;
            //     }
            // }

            _fieldManager->Kill(victim);
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool Creature::Eat()
{
    // cout << "eat" << '\t';
    vector<pair<int,int>> possibleFood;

    int currX = this->position[1];
    int currY = this->position[0];

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            int nextY = currY + y;
            int nextX = currX + x;
            
            if (x == 0 && y == 0) continue;

            if(currY + y == _fieldManager->fieldHeight)
            {
                nextY = 0;
            }
            else if(currY + y == -1)
            {
                nextY = _fieldManager->fieldHeight - 1;
            } 
            if(currX + x == _fieldManager->fieldWidth)
            {
                nextX = 0;
            }
            else if(currX + x == -1)
            {
                nextX = _fieldManager->fieldWidth - 1;
            }

            if(isdigit((*_fieldManager).fieldArray[nextY][nextX]))
            {
                possibleFood.push_back(pair(nextY,nextX));
            }
        }
    }

    if(possibleFood.size() != 0)
    {
        pair<int,int> food = possibleFood[rand()%possibleFood.size()];

        this->stats[Stat::Energy] += (*_fieldManager).fieldArray[food.first][food.second] - '0' % int(MaxEnergy);

        if((*_fieldManager).fieldArray[food.first][food.second] <= 0)
        {
            (*_fieldManager).fieldArray[food.first][food.second] = '_';
        }

        return true;
    }
    else
    {
       return false;
    }
}

vector<Position> FieldManager::CorrectMoves(Position currPos)
{
    vector<Position> correctedMoves;

    for (Position deltaPos : tilesArround)
    {
        int nextY = currPos.Y + deltaPos.Y;
        int nextX = currPos.X + deltaPos.X;

        int newNextY = (nextY == fieldHeight) ? 0 : 
                       (nextY == -1) ? fieldHeight - 1 : nextY;

        int newNextX = (nextX == fieldWidth) ? 0 : 
                       (nextX == -1) ? fieldWidth - 1 : nextX;
        
        correctedMoves.push_back(Position(nextX, nextY));
    }
    
    return correctedMoves;
}

bool Creature::Breed()
{
    // cout << "breed" << '\t';
    vector<pair<int,int>> possibleBreed;

    int currX = this->position[1];
    int currY = this->position[0];

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {


            // if ((*_fieldManager).fieldArray[nextY][nextX] == '_') // || isdigit((*_fieldManager).fieldArray[nextY][nextX]))
            // {
            //     possibleBreed.push_back(pair(nextY,nextX));
            // }
        }
    }
    
    if(possibleBreed.size() != 0)
    {
        pair<int,int> breedPlace = possibleBreed[rand()%possibleBreed.size()];

        (*_fieldManager).fieldArray[breedPlace.first][breedPlace.second] = this->symbol;

        Creature* child = new Creature(
            _fieldManager, this->MaxHealth, 
            this->stats[Stat::Speed], this->stats[Stat::Attack], 
            this->MaxEnergy, this->stats[Stat::EnergyRegen]);
        
        child->MaxHealth = this->MaxHealth;
        child->MaxEnergy = this->MaxEnergy;
        child->symbol = this->symbol;
        child->position[0] = breedPlace.first;
        child->position[1] = breedPlace.second;
        child->IdentifyYourself();

        (*_fieldManager).creaturesOnField.push_back(child);

        return true;
    }
    else
    {
       return false;
    }
}

bool Creature::Regen()
{
    // cout << "regen" << '\t';
    this->stats[Stat::Energy] = int(this->MaxEnergy) % (int(this->stats[Stat::EnergyRegen] + this->stats[Stat::Energy]));
    return false;
}

void Creature::Execute()
{
    // for (int j = 0; j < int(stats[Stat::Speed]); j++)
    // {
        Actions currAction = vectorActions[getRandomNumberAndIndex(vectorValues).second];
        bool isExecutedOnce = false;
        for (int i = 0; i < actions.size(); i++)
        {
            isExecutedOnce = CallAction(currAction);
            if (!isExecutedOnce)
            {
                currAction = static_cast<Actions>((static_cast<int>(currAction) + 1) % 5);
            }   
            else
            {
                break;
            }
        }
        if (isExecutedOnce)
        {
            stats[Stat::Energy]--;
            if (stats[Stat::Energy] == 0)
            {
                (*_fieldManager).Kill(this);
            }
        }
    //}
}

bool Creature::CallAction(Actions action)
{
    bool isExecuted = false;
    switch (action)
    {
    case Actions::Attack:
        isExecuted = Attack();
        break;
    case Actions::Breed:
        isExecuted = Breed();
        break;
    case Actions::Walk:
        isExecuted = Walk();
        break;
    case Actions::Eat:
        isExecuted = Eat();
        break;
    case Actions::Regen:
        isExecuted = Regen();
        break;
    }
    return isExecuted;
}

void FieldManager::Kill(Creature *creature)
{
    // cout << "kill" << '\t';
    for (auto it = creaturesOnField.begin(); it != creaturesOnField.end(); )
    {
        if (*it == creature)
        {
            // fieldArray[creature->position[0]][creature->position[1]] = '_';
            it = creaturesOnField.erase(it);  
        }
        else
        {
            ++it;  
        }
    }
}

pair<int, int> Creature::getRandomNumberAndIndex(vector<int>& arr) {
    int sum = 0;
    for (int num : arr) {
        sum += num;
    }

    int randomValue = rand()%sum;

    int currentIndex = 0;
    while (randomValue >= arr[currentIndex]) {
        randomValue -= arr[currentIndex];
        currentIndex++;
    }

    return make_pair(arr[currentIndex], currentIndex);
}

void Creature::IdentifyYourself()
{
    int maxVal = stats.begin()->second;
    Stat maxKey = Stat::Health;

    for (const auto& pair : stats) {
        if (pair.second > maxVal) {
            maxVal = pair.second;
            maxKey = pair.first;
        }
    }

    switch (maxKey)
    {
    case Stat::Health:
        symbol = 'H';
        color = "\033[1;32m";
        break;
    case Stat::Speed:
        symbol = 'S';
        color = "\033[1;34m";
        break;
    case Stat::Attack:
        symbol = 'A';
        color = "\033[1;31m";
        break;
    case Stat::Energy:
        symbol = 'E';
        color = "\033[1;33m";
        break;
    case Stat::EnergyRegen:
        symbol = 'R';
        color = "\033[1;38;2;255;165;0m";
        break;
    }
}

Creature::Creature(FieldManager* fieldManager, float health, float speed, float attack, float energy, float energyRegen)
{
    _fieldManager = fieldManager;

    stats[Stat::Health] = health;
    MaxHealth = stats[Stat::Health];
    stats[Stat::Speed] = speed;
    stats[Stat::Attack] = attack;
    stats[Stat::Energy] = energy;
    MaxEnergy = stats[Stat::Energy];
    stats[Stat::EnergyRegen] = energyRegen;

    pair<Stat,int> statsArr[5];//<pair<Stat,int>> statsList[5];

    int k = 0;
    for (const auto& pair : stats) {
        statsArr[k].first = pair.first;
        statsArr[k].second = pair.second;
        k++;
    }

    for (int i = 0; i < evolutionPoints; i++)
    {
        int num = rand()%5;
        stats[statsArr[num].first]++;
    }
    
    actions.insert(pair(Actions::Regen,0));
    actions.insert(pair(Actions::Breed,0));
    actions.insert(pair(Actions::Walk,0));
    actions.insert(pair(Actions::Attack,0));
    actions.insert(pair(Actions::Eat,0));

    for (int i = 0; i < 100; i+=10)
    {
        switch(rand()%5)
        {
            case 0:
                actions[Actions::Regen] += 10;
                break;
            case 1:
                actions[Actions::Breed] += 10;
                break;
            case 2:
                actions[Actions::Walk] += 10;
                break;
            case 3:
                actions[Actions::Attack] += 10;
                break;
            case 4:
                actions[Actions::Eat] += 10;
                break;
        }
    }

    for (auto action : actions)
    {
        vectorActions.push_back(action.first);
        vectorValues.push_back(action.second);
    }
}

FieldManager::FieldManager()
{
    fieldArray = new char*[fieldHeight];
    for (int i = 0; i < fieldHeight; ++i) 
    {
        fieldArray[i] = new char[fieldWidth];
        
        for (int j = 0; j < fieldWidth; ++j) 
        {
            fieldArray[i][j] = '_';
        }
    }
}

void FieldManager::SetRandomPosition(Creature *creature, int height, int width)
{
    int posY = rand() % height;
    int posX = rand() % width;
    (*creature).position[0] = posY;
    (*creature).position[1] = posX;
    fieldArray[posY][posX] = creature->symbol;
}

void FieldManager::DrawField()
{
    for (int i = 0; i < fieldHeight; i++)
    {
        for (int j = 0; j < fieldWidth; j++)
        {
            bool found = false;
            for (Creature* creature : creaturesOnField)
            {
                if (creature->position[0] == i && creature->position[1] == j)
                {
                    found = true;
                    cout << creature->color << fieldArray[i][j] << ' ' << "\033[0m";
                }
            }
            if (!found)
            {
                cout << fieldArray[i][j] << ' ';
            }
        }
        cout << endl;
    }
    // cout << endl;
}


int main()
{
    // start
    std::srand(time(0));
    FieldManager fieldManager;

    int creaturesNum = 10;

    for (int i = 0; i < creaturesNum; i++)
    {
        Creature* creature = new Creature(&fieldManager,5,0,5,5,5);
        creature->IdentifyYourself();
        fieldManager.SetRandomPosition(creature, fieldManager.fieldHeight, fieldManager.fieldWidth);
        fieldManager.creaturesOnField.push_back(creature);
    }

    // loop
    int iterations = 100;
    std::chrono::milliseconds duration(600);
    do
    {
        int delta = 5;
        for (int i = 0; i < delta; i++)
        {
            cout << endl;
        }

        // int maxAge = 0;
        // Creature* coolestCreature = fieldManager.creaturesOnField[0];
        // cout << "coolest creature:" << "\n"
        //         << "age:" << coolestCreature->age << "\n"
        //         << "health:" << coolestCreature->stats[Stat::Health] << "\n"
        //         << "speed:" << coolestCreature->stats[Stat::Speed] << "\n"
        //         << "attack:" << coolestCreature->stats[Stat::Attack] << "\n"
        //         << "energy:" << coolestCreature->stats[Stat::Energy] << "\n"
        //         << "energy regen:" << coolestCreature->stats[Stat::EnergyRegen] << "\n";

        // cout << fieldManager.creaturesOnField.size() << endl;
        for (auto creature : fieldManager.creaturesOnField)
        {
            creature->Execute();
            // if (creature->age > maxAge)
            // {
            //     maxAge = creature->age;
            //     coolestCreature = creature;
            // }
            creature->age++;
        }

        for (int i = 0; i < fieldManager.fieldHeight; i++)
        {
            for (int j = 0; j < fieldManager.fieldWidth; j++)
            {
                if(isdigit(fieldManager.fieldArray[i][j]))
                {
                    fieldManager.fieldArray[i][j] = (fieldManager.fieldArray[i][j] - '0') - 1 + '0';
                    if (fieldManager.fieldArray[i][j] == '/')
                    {
                        fieldManager.fieldArray[i][j] = '_';
                    }
                }
            }
        }
        

        fieldManager.DrawField();
        std::this_thread::sleep_for(duration);

        iterations--;
    } 
    while (0 < iterations);
}
