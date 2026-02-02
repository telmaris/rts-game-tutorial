#ifndef RESOURCE_H
#define RESOURCE_H

#include "Utils.h"

enum class ResourceType
{
    WOOD = 1,
    IRON_ORE = 2,
    COAL = 3,
    IRON = 4
};

struct Resource
{
    Resource(ResourceType rtype) : type(rtype) {}

    ResourceType type;
    double transportTime = 0.0, elapsedTime = 0.0;
    
    void BeginTransport();
};

class ResourceBuffer
{
    public:
        ResourceBuffer(ResourceType t, int size) : type(t), bufferSize(size) {}
        ResourceBuffer() = default;
        
        int bufferSize;
        ResourceType type;  // buffer can allocate 1 type of resources

        void AddResource(Resource& res);
        Resource GetResource();

        std::vector<Resource> buffer;
};

#endif