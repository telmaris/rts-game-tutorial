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
        Building(int i ) : id(i) {}
        virtual ~Building() = default;

        virtual void Update(double) = 0;
        virtual void InitBuilding(ResourceType) = 0;

    Player* owner;
    Tile* placement;
    int id;
    std::string name{"Building - Generic"};
    std::string tag;
};

// todo: jak zaplanować rozkaz wydawania surowców: priorytet ma producent czy odbiorca?

class ProductionBuilding : public Building
{
    public:
        ProductionBuilding() = default;
        
        virtual ~ProductionBuilding() = default;

        void Update(double) override;
        virtual void InitBuilding(ResourceType t) override { type = t;}
        
        //protected:
        virtual void Produce(double);

        ResourceType type;
        std::map<ResourceType, int> ingredients;    // to budynek pochłania do produkcji (1 para <resourcetype, int> per składnik)
        std::map<ResourceType, int> products;       // to budynek produkuje (analogicznie do ingredients - 1 para per surowiec)

        double productionTime = 0.0, elapsedTime = 0.0;
        bool productionStarted = false;
        
        // 1 resource buffer per 1 resource type
        std::map<ResourceType, ResourceBuffer> inputBuffers;   // analogicznie do ingredients, para <resourcetype, resourcebuffer> per składnik
        std::map<ResourceType, ResourceBuffer> outputBuffers;
};

class Woodcutter : public ProductionBuilding
{
    public:
        Woodcutter(int);
};
class LumberMill : public ProductionBuilding
{
    public:
        LumberMill();
};
class Mine : public ProductionBuilding
{
    public:
        Mine();
        void InitBuilding(ResourceType) override;
};
class Foundry : public ProductionBuilding
{
    public:
        Foundry();
};

#endif