#include "financialAppHeader.h"
#include <string>

// Average minimal monthly costs to meet survival needs in California.
// Values subject to change.
#define DEFAULT_ENTERTAINMENT 0.00 // 213.67 // Source: Value Penguin (2013)
#define DEFAULT_FITNESS 0.00 // Some people don't work out at Gym
#define DEFAULT_FOOD 268.00 // Source: CA Budget & Policy Center (2021)
#define DEFAULT_HOUSEHOLDITEMS 132.00 // Source: ValuePenguin (2013)
#define DEFAULT_PERSONALCARE 134.00 // Source: ValuePenguin (2013)
#define DEFAULT_TRANSPORTATION 298.00 // Source: CA Budget & Policy Center (2021)

Category initializeMinimumNonFixedExpenses()
{
    Category minimumNonFixedExpenses;
    minimumNonFixedExpenses.categoryName = "Minimum Non-Fixed Expenses";
    minimumNonFixedExpenses.subcategorySize = 6;

    Subcategory entertainment;
    Subcategory fitness;    
    Subcategory food;    
    Subcategory householdItems;
    Subcategory personalCare;    
    Subcategory transportation;

    entertainment.subcategoryName = "Entertainment";
    fitness.subcategoryName = "Fitness";
    food.subcategoryName = "Food";
    householdItems.subcategoryName = "Household Items";
    personalCare.subcategoryName = "Personal Care";
    transportation.subcategoryName = "Transportation";

    entertainment.transactions.push_back("Minimum Value");
    fitness.transactions.push_back("Minimum Value");
    food.transactions.push_back("Minimum Value");
    householdItems.transactions.push_back("Minimum Value");
    personalCare.transactions.push_back("Minimum Value");
    transportation.transactions.push_back("Minimum Value");

    entertainment.amounts.push_back(DEFAULT_ENTERTAINMENT);
    fitness.amounts.push_back(DEFAULT_FITNESS);
    food.amounts.push_back(DEFAULT_FOOD);
    householdItems.amounts.push_back(DEFAULT_HOUSEHOLDITEMS);
    personalCare.amounts.push_back(DEFAULT_PERSONALCARE);
    transportation.amounts.push_back(DEFAULT_TRANSPORTATION);

    minimumNonFixedExpenses.subcategories.push_back(food);
    minimumNonFixedExpenses.subcategories.push_back(personalCare);
    minimumNonFixedExpenses.subcategories.push_back(householdItems);
    minimumNonFixedExpenses.subcategories.push_back(fitness);
    minimumNonFixedExpenses.subcategories.push_back(entertainment);
    minimumNonFixedExpenses.subcategories.push_back(transportation);

    return minimumNonFixedExpenses;
}