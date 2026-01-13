#ifndef BUILDING_H
#define BUILDING_H

#include "Utils.h"
#include "Resource.h"

class Player;
class Tile;

class Building
{
    public:
        Building() = default;

    Player* owner;
    Tile* placement;
    int id;
    std::string name;
};

class ProductionBuilding : public Building
{
    public:
        ProductionBuilding() = default;

        virtual void Produce(double);

    protected:

        double productionTime = 0.0, elapsedTime = 0.0;
        std::vector<ResourceBuffer> inputBuffers;
        std::vector<ResourceBuffer> outputBuffers;
};

class LumberMill : public ProductionBuilding
{
    public:
        LumberMill();


};

#endif