#include "../inc/Building.h"
#include "../inc/ProductionBuildings.h"
#include "../inc/Player.h"
ProductionBuilding::ProductionBuilding(int ajdi)
{
    id = ajdi;
    type = ResourceType::Null;
    name = "ProductionBuilding";
    tag = "[ProductionBuilding]";
}
void ProductionBuilding::Update(double dt)
{
    Produce(dt);
    HandleTransport();
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
                for (int i = 0; i < amount; i++)
                {
                    outputBuffers[resource].buffer.emplace_back(Resource{resource});
                    Log::Msg(tag, "Created a resource: ", rt2s(resource));
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
            if (buffer.buffer.size() >= buffer.bufferSize)
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
                for (int i = 0; i < amount; i++)
                {
                    inputBuffers[resource].buffer.pop_back();
                }
            }
            for (auto &[resource, amount] : products)
            {
                Log::Msg(tag, "Production of ", rt2s(resource), " started");
            }
            
            productionStarted = true;
        }
    }
}

void ProductionBuilding::HandleTransport()
{
    for(auto& [resource, receiver] : receiversMap)
    {
        // check if given resource has been storaged in output buffer
        auto [isAvailable, res] = outputBuffers[resource].GetResource();
        if(isAvailable)
        {
            owner->BeginTransport(this, receiver, res);
            Log::Msg(tag, "ID: ", id, " ", rt2s(res.type), " transport started to ", receiver->name, " with ID ", receiver->id);
        }
    }
}

void ProductionBuilding::AddResource(Resource res)
{
    Log::Msg(tag, "resource added!");
    inputBuffers[res.type].AddResource(res);
}

Resource ProductionBuilding::GetResource(ResourceType type)
{
    inputBuffers[type].GetResource();
}

void ProductionBuilding::SetSupplier(ResourceType type, Building* supplier)
{
    auto [it, ok] = suppliersMap.insert({type, supplier});
    if(!ok)
    {
        suppliersMap[type] = supplier;
    }
}

void ProductionBuilding::SetReceiver(ResourceType type, Building* receiver)
{
    auto [it, ok] = receiversMap.insert({type, receiver});
    if(!ok)
    {
        receiversMap[type] = receiver;
    }
    receiver->SetSupplier(type, this);
}



// ===== BUILDINGS =====

Woodcutter::Woodcutter(int i)
{
    id = i;
    name = "Woodcutter";
    tag = "[Woodcutter]";
    type = ResourceType::WOOD;
    products.insert({ResourceType::WOOD, 1});
    productionTime = 5;
    ResourceBuffer output{ResourceType::WOOD, 3};
    outputBuffers.insert({ResourceType::WOOD, output}); // to jest stworzenie pojedynczego outputu
}
LumberMill::LumberMill(int i)
{
    id = i;
    name = "Lumber Mill";
    tag = "[Lumber Mill]";

    type = ResourceType::PLANKS;
    products.insert({ResourceType::PLANKS, 2});
    productionTime = 10;

    ingredients.insert({ResourceType::WOOD, 1});

    ResourceBuffer output{ResourceType::PLANKS, 16};
    ResourceBuffer input{ResourceType::WOOD, 8};

    inputBuffers.insert({ResourceType::WOOD, input});
    outputBuffers.insert({ResourceType::PLANKS, output});
}

Mine::Mine(int i)
{
    type = ResourceType::Null;
    id = i;
    name = "Mine";
    tag = "[Mine]";
}

void Mine::InitBuilding(ResourceType tile)
{
    type = tile;
    if (type == ResourceType::IRON_ORE)
    {
        products.insert({ResourceType::IRON_ORE, 2});
        productionTime = 2;
        outputBuffers.insert({ResourceType::IRON_ORE, ResourceBuffer{ResourceType::IRON_ORE, 10}});
    }
    if (type == ResourceType::COAL)
    {
        products.insert({ResourceType::COAL, 2});
        productionTime = 2;
        outputBuffers.insert({ResourceType::COAL, ResourceBuffer{ResourceType::COAL, 10}});
    }
}

Foundry::Foundry(int ajdi)
{
    id = ajdi;
    type = ResourceType::Null;
    name = "Foundry";
    tag = "[Foundry]";
}
void Foundry::SetSupplier(ResourceType type, Building* supplier)
{
    // 1) foundry nic nie produkuje - czyli jest absolutnie nowy supplier
    // czyli: ustawiamy suppliera, ustawiamy produkcje danego surowca
    // 2) foundry coś produkuje i zmienia się supplier (tego samego surowca) ✅
    // czyli: musimy po prostu zmienić pointer na dostawce ✅
    // 3) foundry coś produkuje i zmienia się supplier i typ surowca
    // czyli: musimy wszystko wyczyścić (mapy ingredients, products, suppliers, receivers itd) i ustawić na nowo
    if(type != type && type != ResourceType::COAL) 
    {
        suppliersMap.clear();
        ingredients.clear();
        inputBuffers.clear();
        outputBuffers.clear();
        products.clear();
        receiversMap.clear();
    }
    auto [it, ok] = suppliersMap.insert({type, supplier});
    if(!ok)
    {
        suppliersMap[type] = supplier;
        return;
    }
    switch (type)
    {
    case ResourceType::IRON_ORE:
    {
    type = ResourceType::IRON;
    products.insert({ResourceType::IRON, 2});
    productionTime = 2;

    ingredients.insert({ResourceType::IRON_ORE, 1});
    ingredients.insert({ResourceType::COAL, 1});

    ResourceBuffer output{ResourceType::IRON, 16};
    ResourceBuffer input{ResourceType::IRON_ORE, 8};
    ResourceBuffer input2{ResourceType::COAL, 8};


    inputBuffers.insert({ResourceType::IRON_ORE, input});
    inputBuffers.insert({ResourceType::COAL, input2});
    outputBuffers.insert({ResourceType::IRON, output});
    break;
    }
    
    default:
        break;
    }    

}
    void Foundry::SetReceiver(ResourceType, Building*)
    {

    }



