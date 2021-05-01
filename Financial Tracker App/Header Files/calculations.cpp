#include "financialappheader.h"
#include <vector>
#include <iostream>

float calculateTotal(Category category);
float* calPotentialAmountToSave(Category categories[], 
    Category minimumExpenses);
float calculatePercentageSpent(Category categories[], 
    Category minimumExpenses, float totalGoals);
void addAmount(std::string subcategoryName, 
    Category &amountToSave, float amount);
float roundNumberPrecision(float number, int precision);

float* calculateTotalForCategory(Category categories[])
{
    float* transactions = new float[4];

    for (int i = 0; i < 4; i++)
    {
        transactions[i] = calculateTotal(categories[i]);
    }
    return transactions;
}

void calculateAmountToSave(Category categories[], Category minimumExpenses,
    Category& amountToSave, float totalGoals)
{
    float percentageToSave = calculatePercentageSpent
    (categories, minimumExpenses, totalGoals);
    float* potentialAmountToSave = calPotentialAmountToSave
    (categories, minimumExpenses);
    for (int i = 0; i < categories[2].subcategorySize; i++)
    {
        addAmount(categories[2].subcategories[i].subcategoryName, amountToSave,
            potentialAmountToSave[i] * percentageToSave);
    }
    delete[] potentialAmountToSave;
}

//
//This is a processing module that calculate the total for a single category.
//
float calculateTotal(Category category) 
{
    float total = 0.00;
    
    for (int i = 0; i < category.subcategorySize; i++) 
    {
        for (int z = 0; z < category.subcategories[i].transactionsSize; z++) 
        {
            total += category.subcategories[i].amounts[z];
        }
       
    }
    return total;
}

//
// This is a processing module that calculates the potential amount to save
// for each of the subcategory. 
//
float* calPotentialAmountToSave(Category categories[],
    Category minimumExpenses)
{
    float* potentialAmountToSave = new float[categories[2].subcategorySize];
    for (int i = 0; i < categories[2].subcategorySize; i++)
    {
        float total = 0.00;

        for (int z = 0; z < categories[2].subcategories[i].transactionsSize;
            z++)
        {
            total += categories[2].subcategories[i].amounts[z];
        }
        if (total > minimumExpenses.subcategories[i].amounts[0])
        {
            potentialAmountToSave[i] =
                total - minimumExpenses.subcategories[i].amounts[0];
        }
        else
            potentialAmountToSave[i] = 0;
    }
    return potentialAmountToSave;
}

//
// A processing moule to calculate the total amount the user can
// potentially save
//
float calTotalAmountToSave(Category categories[], Category minimumExpenses) 
{
    float totalPotentialAmountToSave = 0.00;
    float* potentialAmountToSave;
    potentialAmountToSave = calPotentialAmountToSave
    (categories, minimumExpenses);
    for (int i = 0; i < categories[2].subcategorySize; i++)
    {
        totalPotentialAmountToSave += potentialAmountToSave[i];
    }
    delete[] potentialAmountToSave;
    return totalPotentialAmountToSave;
}

//
// This is a processing module that calculates percentage needs to save.
//
float calculatePercentageSpent(Category categories[], Category minimumExpenses,
    float totalGoals) 
{
    float totalPotentialAmountToSave = calTotalAmountToSave(categories,
        minimumExpenses);
    return totalGoals / totalPotentialAmountToSave;
}
 
//
// An input module for pushing back an amount and a name into a category
//
void addAmount(std::string subcategoryName, Category &amountToSave,
    float amount)
{
    Subcategory subcategory;
   
    amount = roundNumberPrecision(amount, 2);

    subcategory.subcategoryName = subcategoryName; 
    subcategory.amounts.push_back(amount);
    subcategory.transactionsSize++;
    amountToSave.subcategories.push_back(subcategory);
    amountToSave.subcategorySize++;
}

//
// A processing module to round a number
//
float roundNumberPrecision(float number, int precision)
{
    float preciseNumber;

    for (int i = 0; i < precision; i++)
    {
        number *= 10;
    }
    // Purposefully lost data to make it round to a number
    preciseNumber = (float) static_cast<int>(number);
    if (static_cast<int>(number + 0.5) == (preciseNumber + 1))
    {
        preciseNumber++;
        for (int i = 0; i < precision; i++)
        {
            preciseNumber /= 10;
        }
        return preciseNumber;
    }

    for (int i = 0; i < precision; i++)
    {
        preciseNumber /= 10;
    }
    return preciseNumber;
}