#include "../inc/Building.h"

void ProductionBuilding::Update(double dt)
{
    Produce(dt);
}

void ProductionBuilding::Produce(double dt)
{
    if (productionStarted)
    {
        // handle ongoing production
        if (elapsedTime >= productionTime)
        {
            // handle finished production
            for (auto &[resource, amount] : products)
            {
                for(int i = 0; i < amount; i++)
                {
                    outputBuffers[resource].buffer.emplace_back(Resource{resource});
                    Log::Msg("[production building]", "Created a resource: ");
                }
            }

            productionStarted = false;
            elapsedTime = 0.0;
        }
        else
        {
            // handle ongoing production
            elapsedTime += dt;
        }
    }
    else
    {
        // check if production start is possible
        // assumption: ingredients vector is set, and inputBuffers is also properly configured

        // first, check if output buffers have space
        for (auto &[resource, buffer] : outputBuffers)
        {
            if(buffer.buffer.size() >= buffer.bufferSize) 
            {
                // Log::Msg("[production building]", "Cannot start due to the full output buffer!");
                return;
            }
        }

        bool canStart = true;

        // check if all resources are available
        for (auto &[resource, amount] : ingredients)
        {
            if (inputBuffers[resource].buffer.size() < amount)
            {
                canStart = false;
                return;
            }
        }

        // if yes, delete resources in buffers and start production
        if (canStart)
        {
            for (auto &[resource, amount] : ingredients)
            {
                for(int i = 0; i < amount; i++)
                {
                    inputBuffers[resource].buffer.pop_back();
                }
            }

            productionStarted = true;
        }
    }
}
ResourceType insertType(ResourceType type)
{
    return type;
}


// ===== BUILDINGS =====

Woodcutter::Woodcutter()
{
    type = ResourceType::WOOD;
    products.insert({ResourceType::WOOD, 1});
    productionTime = 5;
    ResourceBuffer output{ResourceType::WOOD, 3};
    outputBuffers.insert({ResourceType::WOOD, output});     // to jest stworzenie pojedynczego outputu
}
LumberMill::LumberMill()
{

    type = ResourceType::PLANKS;
    products.insert({ResourceType::PLANKS, 2});
    productionTime = 10;
    ResourceBuffer output{ResourceType::PLANKS, 16};
    ResourceBuffer input{ResourceType::WOOD, 8};
    inputBuffers.insert({ResourceType::WOOD, input});
    outputBuffers.insert({ResourceType::WOOD, output});
    
}
Mine::Mine()
{
    type = ResourceType::Null;
    if(type == ResourceType::IRON_ORE)
    {
        products.insert({ResourceType::IRON_ORE, 2});
        productionTime = 1;
        outputBuffers.insert({ResourceType::IRON_ORE, ResourceBuffer{ResourceType::IRON_ORE, 2}});
    }
    if(type == ResourceType::COAL_ORE)
    {
        products.insert({ResourceType::COAL_ORE, 6});
        productionTime = 40;
        outputBuffers.insert({ResourceType::COAL_ORE, ResourceBuffer{ResourceType::COAL_ORE, 6}});
    }
}
Foundry::Foundry()
{
    type = ResourceType::Null;
    ResourceType inputType = ResourceType::Null;
    bool allow = false;
    switch (inputType)
    {
    case ResourceType::Null:
        break;
    case ResourceType::WOOD:
        allow = true;
        productionTime = 30;
        inputBuffers.insert({ResourceType::WOOD, ResourceBuffer{ResourceType::WOOD, 2}});
        break;
    case ResourceType::COAL_ORE:
        allow = true;
        productionTime = 20;
        inputBuffers.insert({ResourceType::COAL_ORE, ResourceBuffer{ResourceType::COAL_ORE, 2}});
        break;
    default:
        break;
    }
    switch (type)
    {
    case ResourceType::Null:
        break;
    case ResourceType::IRON:
        products.insert({ResourceType::IRON, 1});
        inputBuffers.insert({ResourceType::IRON_ORE, ResourceBuffer{ResourceType::IRON_ORE, 1}});
        outputBuffers.insert({ResourceType::IRON, ResourceBuffer{ResourceType::IRON_ORE, 1}});
        break;
    default:
        break;
    }
}



