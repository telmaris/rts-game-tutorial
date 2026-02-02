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
        virtual ~Building() = default;

        virtual void Update(double) = 0;

    Player* owner;
    Tile* placement;
    int id;
    std::string name;
};

// todo: jak zaplanować rozkaz wydawania surowców: priorytet ma producent czy odbiorca?

class ProductionBuilding : public Building
{
    public:
        ProductionBuilding() = default;
        virtual ~ProductionBuilding() = default;

        void Update(double) override;
        
        //protected:
        virtual void Produce(double);

        ResourceType type;
        std::map<ResourceType, int> ingredients;
        std::map<ResourceType, int> products;

        double productionTime = 0.0, elapsedTime = 0.0;
        bool productionStarted = false;

        std::map<ResourceType, ResourceBuffer> inputBuffers;   // 1 resource buffer per 1 resource type
        std::map<ResourceType, ResourceBuffer> outputBuffers;
};

class LumberMill : public ProductionBuilding
{
    public:
        LumberMill();


};

#endif