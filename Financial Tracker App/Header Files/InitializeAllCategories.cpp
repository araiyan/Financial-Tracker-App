#include "financialAppHeader.h"
#include <string>

void initializeSubcategory(Category& category, std::string subcategoryName);

Category* initializeAllCategories()
{
    Category* categories = new Category[4];

    std::string incomeSubcategories[] = { "Jobs" };
    std::string fixedExpensesSubcategories[] = { "Housing", "Utilities",
        "insurance", "Retirement", "Debt", "Income Tax" };
    std::string nonFixedExpensesSubcategories[] = {"Food", "Personal Care",
        "Household Items", "Fitness", "Entertainment", "Transportation"};
    std::string goals[] = { "Saving Goals", "Individual Retirement Goals",
        "Vacation/Travel Goals", "Items Saving For" };

    categories[0].categoryName = "Income";
    categories[1].categoryName = "Expenses (Fixed)";
    categories[2].categoryName = "Expenses (Non Fixed)";
    categories[3].categoryName = "Goals";

    for (int i = 0; i < 1; i++)
        initializeSubcategory(categories[0], incomeSubcategories[i]);
    for (int i = 0; i < 6; i++)
        initializeSubcategory(categories[1], fixedExpensesSubcategories[i]);
    for (int i = 0; i < 6; i++)
        initializeSubcategory(categories[2], nonFixedExpensesSubcategories[i]);
    for (int i = 0; i < 4; i++)
        initializeSubcategory(categories[3], goals[i]);

    return categories;
}

//
// An input module that pushes back a Subcategory to a Category then names that
// Subcategory
//
void initializeSubcategory(Category& category, std::string subcategoryName)
{
    Subcategory subcategory;
    subcategory.subcategoryName = subcategoryName;
    category.subcategories.push_back(subcategory);
    category.subcategorySize++;
}