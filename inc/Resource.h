#ifndef RESOURCE_H
#define RESOURCE_H

#include "Utils.h"

class Building;

enum class ResourceType : int
{
    Null = 0,
    WOOD = 1,
    IRON_ORE = 2,
    COAL = 3,
    IRON = 4,
    PLANKS = 5
};

inline std::string rt2s(ResourceType s)
{
    switch (s)
    {
        case ResourceType::Null: return "NULL";
        case ResourceType::WOOD:  return "WOOD";
        case ResourceType::IRON_ORE: return "IRON_ORE";
        case ResourceType::COAL: return "COAL";
        case ResourceType::IRON: return "IRON";
        case ResourceType::PLANKS: return "PLANKS";

        default: return "Unknown";
    }
}

struct Resource
{
    Resource() = default;
    Resource(ResourceType rtype) : type(rtype) {}

    std::string tag{"[Resource]"};
    ResourceType type{ResourceType::Null};
    double transportTime = 0.0, elapsedTime = 0.0;

    Building* targetBuilding = nullptr;
    
    bool Update(double);
    void BeginTransport(Building*, double);
};

class ResourceBuffer
{
    public:
        ResourceBuffer(ResourceType t, int size) : type(t), bufferSize(size) {}
        ResourceBuffer() = default;
        
        int bufferSize;
        ResourceType type;  // buffer can allocate 1 type of resources

        void AddResource(Resource& res);
        std::pair<bool, Resource> GetResource();    // returns bool - is resource available, Resource - obtained resource

        std::vector<Resource> buffer;
};

#endif