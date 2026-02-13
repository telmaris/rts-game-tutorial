#include "../inc/Resource.h"
#include "../inc/Building.h"

bool Resource::Update(double dt)
{
    elapsedTime += dt;
    if(elapsedTime >= transportTime)
    {
        // obsługa dostarczenia surowca do celu
        Log::Msg(tag, "resource transport finished!");
        targetBuilding->AddResource(Resource{type});
        return true;
    }
    return false;
}

void Resource::BeginTransport(Building* target, double time)
{
    Log::Msg(tag, "beginning the transport...");
    targetBuilding = target;
    // ustawić transport/elapsed time
    transportTime = time;
    elapsedTime = 0;
}

void ResourceBuffer::AddResource(Resource& res)
{
    if(buffer.size() < bufferSize)
    {
        buffer.push_back(res);
    }
}

std::pair<bool, Resource> ResourceBuffer::GetResource()
{
    if(buffer.size() > 0)
    {
        auto res = buffer.back();
        buffer.pop_back();
        return {true, res};
    }
    return {false, Resource{}};
}