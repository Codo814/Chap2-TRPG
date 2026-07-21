#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

struct PotionRecipe
{
    std::string PotionName;
    std::string Potioningredient1;
    int ingredient1Count;
    std::string Potioningredient2;
    int ingredient2Count;
};

class AlchemyWorkshop
{
private:
    std::vector<PotionRecipe> recipes;
    std::map<std::string, int> potionStock_;
    static const int MAX_STOCK = 3;

public:
    AlchemyWorkshop();

    void ShowAllRecipes();
    void SearchByName(std::string name);
    void SearchByIngredient(std::string ingredient);
    int GetStock(std::string name);
    void DispensePotion(std::string name);
    void ReturnPotion(std::string name);
    void RunMenu();
};
