#include "financialAppHeader.h"
#include <string>
#include <vector>
#include <fstream>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <cstdlib>
#include <ctime>

//
// Struct for storing information about different texts -
// potential texts to display for each unique balance/event.
//
struct Texts
{
    std::vector<std::string> textsToDisplay;
    int textsSize = 0;
};

//
// Struct for storing information about different cases -
// outcomes from calculating each unique balance (income - expenses).
//
struct Cases
{
    std::vector<Texts> texts;
    int casesSize = 0;
};

int calculateEvent(Category categories[], Category minimumExpenses,
    Category& amountToSave, float totalTransactions[]);
std::string randomlyGenerateStringToPrint(std::vector<std::string> 
    displayTexts, int arraySize);
Cases initializeCasesAndTexts();

void processing(Category categories[], Category minimumExpenses,
    Category& amountToSave, int& outcome, float totalTransactions[],
    std::string& scenario)
{
    static Cases uniEvent = initializeCasesAndTexts();
    float* totalForCategory = calculateTotalForCategory(categories);

    for (int i = 0; i < 4; i++)
    {
        totalTransactions[i] = totalForCategory[i];
    }
    delete[] totalForCategory;

    outcome = calculateEvent(categories, minimumExpenses, amountToSave,
        totalTransactions);
    scenario =
        randomlyGenerateStringToPrint(uniEvent.texts[outcome].textsToDisplay,
        uniEvent.texts[outcome].textsSize);
}

void displayUniqueEvents(int outcome, std::string scenario)
{
    float wrapWidth = 500.0f;
    ImColor wrapColor = {0, 0, 0, 0};

    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(wrapWidth, 2.0f),
        ImVec2(20.0f + wrapWidth, 20.0f + ImGui::GetTextLineHeight()),
        wrapColor);
    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrapWidth);
    ImGui::Text(scenario.c_str());
    ImGui::PopTextWrapPos();
}

//
// A function that returns a Case for each Unique Event then fills each
// Texts with the a selection of potential strings to display to the user
// based on calculations from their income, expenses, and goals.
//
Cases initializeCasesAndTexts()
{
    Cases uniqueEvent;

    Texts uniqueEvent0;
    Texts uniqueEvent1;
    Texts uniqueEvent2;
    Texts uniqueEvent3;
    Texts uniqueEvent4;
    Texts uniqueEvent5;
    Texts uniqueEvent6;

    std::string TextName;

    // Case 0 - In debt
    TextName = "Unfortunately your fixed expenses exceed your income. Start";
    TextName += " acting quick to prioritize which payments you want to make ";
    TextName += " first if you can. Afterwards, let's see if we can increase";
    TextName += " our income or decrease our fixed expenses. Don't give up,";
    TextName += " you can do this. :)";
    uniqueEvent0.textsToDisplay.push_back(TextName);
    
    TextName = "Looks like your income is not high enough to cover your most";
    TextName += " fixed costs (i.e. rent, insurance, utilities, etc.). Let's";
    TextName += " find a way to complete our essential payments and evaluate";
    TextName += " where we can increase our income or decrease the cost of";
    TextName += " our fixed expenses. One step at a time, you got this. :)";
    uniqueEvent0.textsToDisplay.push_back(TextName);

    TextName = "Your fixed costs are higher than your total income. See if";
    TextName += " there are any fixed costs that can be re-negotiated, or if";
    TextName += " there are cheaper alternatives. From there, prioritize";
    TextName += " paying your most essential fixed costs first. Also start";
    TextName += " exploring where you can increase your income. You can do";
    TextName += " this! Baby steps. :)";
    uniqueEvent0.textsToDisplay.push_back(TextName);

    uniqueEvent0.textsSize = 3;

    // Case 1 - Only enough for fixed costs
    TextName = "You have *just* enough for rent, insurance, utilities (fixed";
    TextName += " costs)! Awesome! However, you do not have any money left";
    TextName += " over for any other expenses. Consider increasing your";
    TextName += " income. Are you due for a raise? Are there any bills that";
    TextName += " can be more affordable? ";
    uniqueEvent1.textsToDisplay.push_back(TextName);
    
    TextName = "Looks like you only have enough for your fixed expenses.";
    TextName += " Let's start strategizing to see where we can start meeting";
    TextName += " your non-fixed expenses. This can be done by increasing";
    TextName += " your income source(s) or decreasing the cost of fixed bills";
    TextName += " by re-negotiating or finding a cheaper option.";
    uniqueEvent1.textsToDisplay.push_back(TextName);
    
    TextName = "You only have enough for your fixed expenses and that's";
    TextName += " great! But, let's see if you can make room in your budget";
    TextName += " to account for your non-fixed expenses (perhaps by";
    TextName += " increasing your income or decreasing your fixed bills).";
    uniqueEvent1.textsToDisplay.push_back(TextName);

    uniqueEvent1.textsSize = 3;

    // Case 2 - Enough for fixed costs but not essential non-fixed costs
    TextName = "Congratulations, you have enough for all your rent,";
    TextName += " utilities, insurance (fixed costs) with a little extra!";
    TextName += " Good job, this is a great financial milestone! However, you";
    TextName += " do not have quite enough to save up for your essential";
    TextName += " non-fixed costs.";
    uniqueEvent2.textsToDisplay.push_back(TextName);
    
    TextName = "Looks like you have enough to meet our fixed needs with some";
    TextName += " money to spare.Great!But let's see if there is a way to";
    TextName += " increase your income or decrease the cost of some bills to";
    TextName += " meet your essential non-fixed cost needs.";
    uniqueEvent2.textsToDisplay.push_back(TextName);
    
    TextName = "You have enough to meet your fixed cost needs with a little";
    TextName += " extra as well. Meeting these needs is awesome but look into";
    TextName += " increasing our income or decreasing our living expenses to";
    TextName += " start putting money towards your essential non-fixed costs.";
    uniqueEvent2.textsToDisplay.push_back(TextName);
    
    uniqueEvent2.textsSize = 3;
    
    // Case 3 - Enough for fixed and essential non-fixed costs
    TextName = "Congratulations, you have enough for all your rent, other";
    TextName += " fixed bills, and essential non-fixed purchases! Good job,";
    TextName += " this is a great financial milestone! However, you do not";
    TextName += " have enough to save up for any additional financial goals.";
    uniqueEvent3.textsToDisplay.push_back(TextName);
    
    TextName = "Looks like you have just enough to meet your survival needs";
    TextName += " (fixed and essential non-fixed costs). Great! But start";
    TextName += " increasing your income or saving more if you want to build";
    TextName += " on your financial goals.";
    uniqueEvent3.textsToDisplay.push_back(TextName);
    
    TextName = "You have enough to meet your survival (fixed and essential";
    TextName += " non-fixed costs). Meeting these needs is awesome but there";
    TextName += " is no room left for anything else. Let's look into";
    TextName += " increasing your income or decreasing your living expenses";
    TextName += " to start putting money towards other financial goals.";
    uniqueEvent3.textsToDisplay.push_back(TextName);
    
    uniqueEvent3.textsSize = 3;
    
    // Case 4 - Enough for fixed and essential non-fixed costs
    //              but not enough for savings goals
    TextName = "Congratulations, you have enough for all your rent, payments,";
    TextName += " and essential lifestyle purchases! This is great! Although";
    TextName += " you do have a little extra after paying all of your bills,";
    TextName += " it is not enough to meet your savings goals.";
    uniqueEvent4.textsToDisplay.push_back(TextName);
    
    TextName = "You're doing great. You have enough to pay all of your bills";
    TextName += " and meet your essential needs while having a little more to";
    TextName += " put away.However, you do not have enough to for your";
    TextName += " savings goals without going into debt.";
    uniqueEvent4.textsToDisplay.push_back(TextName);
    
    TextName = "Good job, you are able to meet your essential financial needs";
    TextName += " and your essential monthly expenditures while have some";
    TextName += " money left over at the end of the month. This is a great";
    TextName += " achievement! However, let's look at ways to increase your";
    TextName += " income or decrease your living costs to start saving more";
    TextName += " to build on your financial savings goals.";
    uniqueEvent4.textsToDisplay.push_back(TextName);
    
    uniqueEvent4.textsSize = 3;

    // Case 5 - Have enough for costs and goals
    TextName = "Congratulations! You are meeting all your rent, payments, and ";
    TextName += "daily lifestyle needs and purchases! On top of that, you have";
    TextName += " just enough money to put towards your financial goals! :D";
    uniqueEvent5.textsToDisplay.push_back(TextName);
    
    TextName = "This is awesome! Your budget looks amazing! You're meeting"; 
    TextName += " all of your financial needs, lifestyle costs AND goals!:)";
    uniqueEvent5.textsToDisplay.push_back(TextName);

    TextName = "Good job! You are covering all your essential needs and";
    TextName += " lifestyle expenses WHILE ALSO meeting your savings goals!!";
    TextName += " It's never a bad idea to think of saving extra in the";
    TextName += " future though. ;)";
    uniqueEvent5.textsToDisplay.push_back(TextName);

    uniqueEvent5.textsSize = 3;

    // Case 6 - Have enough for everything + extra
    TextName = "Congratulations!!! You have enough in your budget to reach";
    TextName += " your goals and put extra away!!!";
    uniqueEvent6.textsToDisplay.push_back(TextName);
    
    TextName = "Great job!!! You're meeting all of your financial needs,";
    TextName += " lifestyle expenses, and savings goals! AND with money to";
    TextName += " spare!";
    uniqueEvent6.textsToDisplay.push_back(TextName);

    TextName = "Keep it up!!! You're covering all your financial needs,";
    TextName += " lifestyle purchases, and financial goals!!! WITH extra to";
    TextName += " put away or invest elsewhere)!";
    uniqueEvent6.textsToDisplay.push_back(TextName);

    uniqueEvent6.textsSize = 3;

    uniqueEvent.texts.push_back(uniqueEvent0);
    uniqueEvent.texts.push_back(uniqueEvent1);
    uniqueEvent.texts.push_back(uniqueEvent2);
    uniqueEvent.texts.push_back(uniqueEvent3);
    uniqueEvent.texts.push_back(uniqueEvent4);
    uniqueEvent.texts.push_back(uniqueEvent5);
    uniqueEvent.texts.push_back(uniqueEvent6);
    uniqueEvent.casesSize = 7;

    return uniqueEvent;
}

// 
// Function that takes in pre-calculated total amounts of each category, and
// returns an integer based on various budget calculations (income minus
// different combinations of fixed and non-fixed expenses and goals). This
// function also calls onto another function to display the amount that can be
// saved in each category when appropriate.
// 
int calculateEvent(Category categories[], Category minimumExpenses,
    Category& amountToSave, float totalTransactions[])
{
    // Contents in totalTransactions
    // totalTransactions[0]=income
    // totalTransactions[1]=totalExpensesFixed
    // totalTransactions[2]=totalExpensesNonFixed // User input amount
    // totalTransactions[3]=totalGoals

    srand(time(0));
    int outcome;
    float sumPotentialSavings = calTotalAmountToSave(categories,
        minimumExpenses);
    float postFixedCosts = totalTransactions[0] - totalTransactions[1];
    float absMinNonFixedExpenses = totalTransactions[2] - sumPotentialSavings;
        // takes into acct when user spends less than designated min
    float AmtForGoals = postFixedCosts - absMinNonFixedExpenses;

    if (postFixedCosts < 0)
    {
        outcome = 0; // in debt
    }
    else if (postFixedCosts == 0)
    {
        outcome = 1; // only enough for fixed costs
    }
    else if (postFixedCosts < absMinNonFixedExpenses)
    {
        // enough for fixed costs but not essential non-fixed costs
        outcome = 2;
    }
    else if (postFixedCosts == absMinNonFixedExpenses)
    {
        // enough for fixed and essential non-fixed costs
        outcome = 3;
    }
    else if (AmtForGoals < totalTransactions[3])
    {
        // enough for fixed and essential non-fixed costs but
        //     not enough for savings goals
        outcome = 4;
    }
    else if (postFixedCosts - totalTransactions[2] - totalTransactions[3] > 0)
    {
        outcome = 6; // have enough for everything + extra
    }
    else if (postFixedCosts - totalTransactions[2] >= 0)
    {
        outcome = 5; // They are already saving a little but its not enough
                     // for their goals
        calculateAmountToSave(categories, minimumExpenses, amountToSave,
            totalTransactions[3] - (postFixedCosts - totalTransactions[2]));
    }
    else if (postFixedCosts < totalTransactions[2])
    {
        outcome = 5; // have enough for costs and goals
        calculateAmountToSave(categories, minimumExpenses, amountToSave,
            (totalTransactions[2] - postFixedCosts) + totalTransactions[3]);
    }
    else
    {
        outcome = 5; // have enough for costs and goals
        calculateAmountToSave(categories, minimumExpenses, amountToSave,
            totalTransactions[3]);
    }
    

    return outcome;
}

//
// Function that generates a random integer outcome, returning a string vector.
//
std::string randomlyGenerateStringToPrint(std::vector<std::string>
    displayTexts, int arraySize)
{
    int randomNum = rand() % arraySize;

    return displayTexts[randomNum];
}

