#include "CreatureLoader.h"
#include <filesystem>
#include <iostream>
#include "RandomGenerator.h"

namespace DespoilerEngine {

    std::pmr::vector<Creature> CreatureLoader::loadCreatures(const std::string& directory)
    {
        std::pmr::vector<Creature> Creatures;
        for (const auto& entry : std::filesystem::directory_iterator(directory))
        {
            if (entry.path().extension() == ".obj"){
                try
                {
                    Creatures.emplace_back(Creature::fromJsonFile(entry.path().string()));
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Error loading creature from file: " << entry.path().string() << std::endl;
                }
            }
        }
        return Creatures;
    }

    Creature CreatureLoader::spawnRandomCreature(const CreatureCollection& collection)
    {
        if (collection.Creatures.empty())
        {
            throw std::runtime_error("No creatures loaded.");
        }

        // Pick random Creature from collection
        const size_t index = RandomGenerator::generateRandomNumber(0, collection.Creatures.size() - 1);
        return collection.Creatures[index];
    }

    CreatureLoader::~CreatureLoader() =default;

} // DespoilerEngine