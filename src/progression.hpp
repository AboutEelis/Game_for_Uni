#pragma once

#include <algorithm>
#include <array>
#include <random>
#include <vector>

enum class UpgradeId {
    Sword, Staff, Aura,
    SpeedTome, HealthTome, AttackSpeedTome
};

struct Upgrade {
    UpgradeId id;
    const char* name;
    bool unlocked;
    int level;
    int maxLevel;
};

class Progression {
public:
    Progression()
        : upgrades_{{
            {UpgradeId::Sword,      "Меч",          true, 1, 8},
            {UpgradeId::Staff,      "Посох",        false, 0, 8},
            {UpgradeId::Aura,       "Аура",         false, 0, 8},
            {UpgradeId::SpeedTome,  "Том скорости", false, 0, 8},
            {UpgradeId::HealthTome, "Том здоровья", false, 0, 8},
            {UpgradeId::AttackSpeedTome, "Том ловкости", false, 0, 8}
        }} {}

    void gainXp(int amount) {
        xp_ += amount;

        while (xp_ >= xpRequired()) {
            xp_ -= xpRequired();
            ++playerLevel_;
            ++pendingChoices_;
        }
    }

    bool hasPendingChoice() const {
        return pendingChoices_ > 0;
    }

    int playerLevel() const { return playerLevel_; }
    int xp() const { return xp_; }
    int xpRequired() const { return 10 + (playerLevel_ - 1) * 5; }

    std::vector<UpgradeId> makeChoices() {
        std::vector<UpgradeId> available;

        for (const auto& upgrade : upgrades_) {
            if (!upgrade.unlocked || upgrade.level < upgrade.maxLevel)
                available.push_back(upgrade.id);
        }

        std::shuffle(available.begin(), available.end(), random_);
        if (available.size() > 3)
            available.resize(3);

        return available;
    }

    bool choose(UpgradeId id) {
        if (!hasPendingChoice())
            return false;

        for (auto& upgrade : upgrades_) {
            if (upgrade.id != id)
                continue;

            if (!upgrade.unlocked) {
                upgrade.unlocked = true;
                upgrade.level = 1;
            } else if (upgrade.level < upgrade.maxLevel) {
                ++upgrade.level;
            } else {
                return false;
            }

            --pendingChoices_;
            return true;
        }

        return false;
    }

    int itemLevel(UpgradeId id) const {
        for (const auto& upgrade : upgrades_) {
            if (upgrade.id == id)
                return upgrade.level;
        }
        return 0;
    }
    
private:
    std::array<Upgrade, 6> upgrades_;
    int playerLevel_ = 1;
    int xp_ = 0;
    int pendingChoices_ = 0;
    std::mt19937 random_{std::random_device{}()};
};