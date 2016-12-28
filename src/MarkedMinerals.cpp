#include "MarkedMinerals.h"
#include "MineralManager.h"
#include "RandomNumberGenerator.h"
#include <vector>

GameObjectID MarkedMinerals::getRandomUnmarkedMineral(bool& success, const MineralManager& mineralManager) {
    const std::vector<GameObjectID>& all = mineralManager.getMinerals();
    std::unordered_set<GameObjectID> markedMinerals;
    std::vector<GameObjectID> unmarkedMinerals;
    unmarkedMinerals.reserve(all.size());

    for (size_t i=0; i<all.size(); ++i) {
        const auto& id = all[i];
        if (minerals.find(id) == minerals.end()) {
            unmarkedMinerals.push_back(id);
        } else {
            markedMinerals.insert(id);
        }
    }

    minerals.swap(markedMinerals);
    if (unmarkedMinerals.size() == 0) {
        success = false;
        return 0;
    }
    success = true;
    size_t randomIndex = global_rng.index(unmarkedMinerals.size());
    return unmarkedMinerals[randomIndex];
}