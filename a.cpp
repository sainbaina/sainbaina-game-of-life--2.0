#include <iostream>
#include <list>
#include <chrono>
#include <vector>
#include <memory>
#include <string>
#include <conio.h>
#include <stdio.h>
#include <thread>
using namespace std;

class BaseCell
{
protected:
    int health;
    int speed;
    int attack;
    int hunger;
    //int direction[2];
public:
    BaseCell();
    ~BaseCell();

    void ChangeHealth(int ammount);
    void ChangeSpeed(int ammount);
    void ChangeAttack(int ammount);
    void ChangeHunger(int ammount);

    int position[2];
    char symbol;
};

BaseCell::BaseCell()
{
}

BaseCell::~BaseCell()
{
}

void BaseCell::ChangeHealth(int ammount)
{
    this->health += ammount;
};

void BaseCell::ChangeSpeed(int ammount)
{
    this->speed += ammount;
};

void BaseCell::ChangeAttack(int ammount)
{
    this->attack += ammount;
};

void BaseCell::ChangeHunger(int ammount)
{
    this->hunger += ammount;
};

class EnergyCell : public BaseCell
{
public:
    EnergyCell();
};

EnergyCell::EnergyCell()
{
    health = 5;
    // speed = 10;
    // attack = 10;
    hunger = 20;
    symbol = 'E';
}

class BreedCell : public BaseCell
{
public:
    BreedCell();
};

BreedCell::BreedCell()
{
    health = 10;
    // speed = 10;
    // attack = 10;
    hunger = 10;
    symbol = 'B';
}

class PreditorCell : public BaseCell
{
public:
    PreditorCell();
};

PreditorCell::PreditorCell()
{
    health = 5;
    speed = 1;
    attack = 5;
    hunger = 15;
    symbol = 'P';
}

class MoveCell : public BaseCell
{
public:
    MoveCell();
};

MoveCell::MoveCell()
{
    health = 10;
    speed = 1;
    // attack = 10;
    hunger = 10;
    symbol = 'M';
}

class FieldManager
{
public:
    const int fieldWidth = 50;
    const int fieldHeight = 24;
    char** fieldArray;
    FieldManager();
};

FieldManager::FieldManager()
{
    fieldArray = new char*[fieldHeight];
    for (int i = 0; i < fieldHeight; ++i) 
    {
        fieldArray[i] = new char[fieldWidth];
        
        for (int j = 0; j < fieldWidth; ++j) 
        {
            fieldArray[i][j] = 'o';
        }
    }
}

class Program
{
public:
    void SetRandomPosition(BaseCell *bc, int height, int width);
};

void Program::SetRandomPosition(BaseCell *bc, int height, int width)
{
    (*bc).position[0] = rand() % height;
    (*bc).position[1] = rand() % width;
}

int main()
{
    std::srand(time(nullptr));
    FieldManager fieldManager;
    list<BaseCell> field;
    Program program;

    std::vector<std::unique_ptr<BaseCell>> cellTypes;
    cellTypes.push_back(std::make_unique<MoveCell>());
    cellTypes.push_back(std::make_unique<PreditorCell>());
    cellTypes.push_back(std::make_unique<BreedCell>());
    cellTypes.push_back(std::make_unique<EnergyCell>());

    int cellsNum[4] = { 5,5,5,5 };

    for (int i = 0; i < 5; ++i) {
        for (const auto& type : cellTypes) {
            std::unique_ptr<BaseCell> cell = std::make_unique<BaseCell>(*type);
            program.SetRandomPosition(cell.get(), fieldManager.fieldHeight, fieldManager.fieldWidth);  
        }
    }

    int iterations = 10;
    std::chrono::milliseconds duration(600);
    do
    {
        for (int i = 0; i < fieldManager.fieldHeight; i++)
        {
            for (int j = 0; j < fieldManager.fieldWidth; j++)
            {
                cout << fieldManager.fieldArray[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;

        std::this_thread::sleep_for(duration);

        iterations--;
    } 
    while (0 < iterations);
}