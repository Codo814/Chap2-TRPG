#include "AlchemyWorkshop.h"

#include <iostream>

using namespace std;

AlchemyWorkshop::AlchemyWorkshop()
{
    PotionRecipe HPpotion;
    HPpotion.PotionName = "HP 포션";
    HPpotion.Potioningredient1 = "허브";
    HPpotion.ingredient1Count = 1;
    HPpotion.Potioningredient2 = "맑은 물";
    HPpotion.ingredient2Count = 1;

    PotionRecipe STMpotion;
    STMpotion.PotionName = "스테미나 포션";
    STMpotion.Potioningredient1 = "허브";
    STMpotion.Potioningredient2 = "베리";
    STMpotion.ingredient1Count = 1;
    STMpotion.ingredient2Count = 1;

    recipes.push_back(HPpotion);
    recipes.push_back(STMpotion);
}

void AlchemyWorkshop::ShowAllRecipes()
{
    cout << "=== 전체 포션 레시피 ===" << endl;

    for (const PotionRecipe& recipe : recipes)
    {
        cout << "-> " << recipe.PotionName << ": " << recipe.Potioningredient1 << " x"
            << recipe.ingredient1Count << ", " << recipe.Potioningredient2 << " x" << recipe.ingredient2Count << endl;
    }
}

void AlchemyWorkshop::SearchByName(string name)
{
    bool found = false;

    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.PotionName == name)
        {
            cout << "-> " << recipe.PotionName << ": " << recipe.Potioningredient1 << " x" << recipe.ingredient1Count << ", " << recipe.Potioningredient2 << " x" << recipe.ingredient2Count << endl;
            found = true;
        }
    }

    if (found == false)
    {
        cout << "찾을 수 없습니다." << endl;
    }
}

void AlchemyWorkshop::SearchByIngredient(string ingredient)
{
    int foundCount = 0;

    for (const PotionRecipe& recipe : recipes)
    {
        if (recipe.Potioningredient1 == ingredient ||
            recipe.Potioningredient2 == ingredient)
        {
            cout << "-> " << recipe.PotionName << " (" << recipe.Potioningredient1 << " x" << recipe.ingredient1Count << ", " << recipe.Potioningredient2 << " x" << recipe.ingredient2Count << ")" << endl;
            foundCount++;
        }
    }

    if (foundCount == 0)
    {
        cout << "찾을 수 없습니다." << endl;
    }
    else
    {
        cout << "총 " << foundCount << "개의 레시피를 찾았습니다." << endl;
    }
}

void AlchemyWorkshop::RunMenu()
{
    while (true)
    {
        int choice;

        cout << endl;
        cout << "=== 포션 제작소 ===" << endl;
        cout << "1. 전체 레시피 보기" << endl;
        cout << "2. 포션 이름으로 검색" << endl;
        cout << "3. 재료로 검색" << endl;
        cout << "0. 돌아가기" << endl;
        cout << endl;
        cout << "선택: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            ShowAllRecipes();
            break;

        case 2:
        {
            string searchName;

            cout << "검색할 포션 이름: ";
            getline(cin >> ws, searchName);

            SearchByName(searchName);
            break;
        }

        case 3:
        {
            string searchingredient;

            cout << "검색할 재료 이름: ";
            cin >> searchingredient;

            SearchByIngredient(searchingredient);
            break;
        }

        case 0:
            return;

        default:
            cout << "잘못된 선택입니다." << endl;
            break;
        }
    }
}
