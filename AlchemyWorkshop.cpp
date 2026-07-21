#include "AlchemyWorkshop.h"
#include <map>
#include <iostream>
#include <string>
#include <vector>


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
    potionStock_[HPpotion.PotionName] = 3;
    recipes.push_back(STMpotion);
    potionStock_[STMpotion.PotionName] = 3;
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

int AlchemyWorkshop::GetStock(string name) {
    return potionStock_[name];
}

void AlchemyWorkshop::DispensePotion(string name) {
    if (potionStock_[name] == 0) {
        cout << "-> " << name << " 지급 실패: 재고 없음!" << endl;
        return;
    }
    potionStock_[name]--;
    cout << "-> " << name << " 지급  (재고: "
        << potionStock_[name] << ")" << endl;
}

void AlchemyWorkshop::ReturnPotion(string name) {
    if (potionStock_[name] >= MAX_STOCK) {
        cout << "-> 공병 반환 실패: 재고가 가득 찼습니다!" << endl;
        return;
    }
    potionStock_[name]++;
    cout << "-> 공병 반환   (재고:" << potionStock_[name]<< ")" << endl;
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
        cout << "4. 포션 재고 확인" << endl;
        cout << "5. 포션 지급" << endl;
        cout << "6. 공병 반환" << endl;
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
        case 4: {
            string potionName;
            cout << "재고를 확인할 포션 이름:";
            getline(cin >> ws, potionName);

            cout << potionName << "재고 :" << GetStock(potionName) << endl;
            break;
        }
        case 5: {
            string potionName;
            cout << "지급할 포션 이름:";
            getline(cin >> ws, potionName);
            DispensePotion(potionName);
            break;
        }
        case 6:
        {
            string potionName;
            cout << "공병을 반환할 포션 이름:";
            getline(cin >> ws, potionName);
            ReturnPotion(potionName);
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
