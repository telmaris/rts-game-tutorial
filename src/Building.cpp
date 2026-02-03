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


// ===== BUILDINGS =====

LumberMill::LumberMill()
{
    type = ResourceType::WOOD;
    products.insert({ResourceType::WOOD, 1});
    productionTime = 5;
    ResourceBuffer output{ResourceType::WOOD, 3};
    outputBuffers.insert({ResourceType::WOOD, output});     // to jest stworzenie pojedynczego outputu
}



