#ifndef ROAD_NETWORK_H
#define ROAD_NETWORK_H

#include "Building.h"

class RoadNetwork
{
    public:

    void Update(double);
    void BeginTransport(Building* src, Building* dest, Resource res);

    const std::string tag{"[Road Network]"};
    std::vector<Resource> resources;

    private: 

        double CalculateTransportTime(Building* src, Building* dest);
};

#endif