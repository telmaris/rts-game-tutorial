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
        Building(int i) : id(i) {}
        virtual ~Building() = default;

        virtual void Update(double) = 0;
        virtual void InitBuilding(ResourceType) = 0;

        virtual void AddResource(Resource) = 0;
        virtual Resource GetResource(ResourceType) = 0;

        virtual void SetSupplier(ResourceType, Building*) = 0;
        virtual void SetReceiver(ResourceType, Building*) = 0;

    Player* owner;
    Tile* placement;
    int id;
    std::string name{"Building - Generic"};
    std::string tag;
};

class Road : public Building
{
    public:
        Road() = default;

        void Update(double);

        void SetSupplier(ResourceType, Building*) {}
        void SetReceiver(ResourceType, Building*) {}

        std::string tag{"[Road]"};
        int upgradeLevel;
        int maxCapacity = 5;
        double speedModifier = 1.0;
        std::vector<Resource> resources;
};

// todo: jak zaplanować rozkaz wydawania surowców: priorytet ma producent czy odbiorca?

class ProductionBuilding : public Building
{
    public:
        ProductionBuilding() = default;
        
        virtual ~ProductionBuilding() = default;

        void Update(double) override;
        virtual void InitBuilding(ResourceType t) override { type = t;}

        void AddResource(Resource) override;
        Resource GetResource(ResourceType) override;

        void SetSupplier(ResourceType, Building*);
        void SetReceiver(ResourceType, Building*);
        
        //protected:
        virtual void Produce(double);
        void HandleTransport();

        ResourceType type;
        std::map<ResourceType, int> ingredients;    // to budynek pochłania do produkcji (1 para <resourcetype, int> per składnik)
        std::map<ResourceType, int> products;       // to budynek produkuje (analogicznie do ingredients - 1 para per surowiec)

        double productionTime = 0.0, elapsedTime = 0.0;
        bool productionStarted = false;
        
        // 1 resource buffer per 1 resource type
        std::map<ResourceType, ResourceBuffer> inputBuffers;   // analogicznie do ingredients, para <resourcetype, resourcebuffer> per składnik
        std::map<ResourceType, ResourceBuffer> outputBuffers;

        std::map<ResourceType, Building*> suppliersMap;
        std::map<ResourceType, Building*> receiversMap;
};



#endif