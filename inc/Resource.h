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
    ResourceType type;
    double transportTime = 0.0, elapsedTime = 0.0;
    
    void BeginTransport();
};

class ResourceBuffer
{
    public:

        int bufferSize;
        ResourceType type;  // buffer can allocate 1 type of resources

        void AddResource(Resource& res);
        Resource GetResource();

    private:
        std::vector<Resource> buffer;
};

#endif