#include "../inc/RoadNetwork.h"

void RoadNetwork::Update(double dt)
{
    for(auto it = resources.begin(); it != resources.end(); )
    {
        bool flag = it->Update(dt);
        if(flag == true)
        {
            // usunięcie resource z vectora, dodanie go do celu
            resources.erase(it);
            Log::Msg(tag, "resource deleted from transported resource vector!");
            continue;
        }
        it++;
    }
}

void RoadNetwork::BeginTransport(Building* src, Building* dest, Resource res)
{
    // calculate time to transport from src to dest (test version - simple)
    // later -> pathfinding algo through road net to find optimal road

    double transportTime = CalculateTransportTime(src, dest);
    res.BeginTransport(dest, transportTime);
    resources.push_back(res);
}

double RoadNetwork::CalculateTransportTime(Building* src, Building* dest)
{
    // todo:: obliczyć czas z src do dest
    // w przyszłości: zaplanowanie trasy

    return 3.0;
}