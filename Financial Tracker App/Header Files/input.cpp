#include "financialAppHeader.h"
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "../libs/imgui_stdlib.h"
#include <iostream>

void showCategoryTab(Category& category);
void tabSwitch(Category categories[], int menuChoice);
void addNewTransaction(Subcategory& subcategory);

void input(Category categories[], int menuChoice, int& nextOrPrevious,
    ImVec2 windowSize)
{
    ImGuiWindowFlags windowFlags = 0;

    windowFlags |= ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoCollapse;

    ImGui::SetNextWindowSize(ImVec2{ 550.0f, 600.0f }, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2{ ((windowSize.x / 2.0f) - 275),
        (windowSize.y / 2.0f) - 175.0f - (225.0f * (windowSize.y / 1080)) },
        ImGuiCond_Always);
    ImGui::Begin("Financial Input:", NULL, windowFlags);

    tabSwitch(categories, menuChoice);

    makeMultipleLines(3);
    ImGui::Spacing();
    ImGui::SameLine(ImGui::GetWindowSize().x * 0.65f);
    backNextButton(nextOrPrevious, "Menu", 1);
    ImGui::SameLine();
    backNextButton(nextOrPrevious, "Clear All", 3);
    ImGui::SameLine();
    backNextButton(nextOrPrevious, "Next", 2);

    ImGui::End();
}

//
// An input module that switches between each tab to take in input for 
// different Category
//
void tabSwitch(Category categories[], int menuChoice)
{
    static int switchTabs = 0;

    if (menuChoice == 1)
    {
        if (ImGui::Button(categories[0].categoryName.c_str(),
            ImVec2{ 100.0f, 0.0f }))
            switchTabs = 0;
        ImGui::SameLine(0.0f, 2.0f);
        if (ImGui::Button(categories[1].categoryName.c_str(),
            ImVec2{ 150.0f, 0.0f }))
            switchTabs = 1;
        ImGui::SameLine(0.0f, 2.0f);
        if (ImGui::Button(categories[2].categoryName.c_str(),
            ImVec2{ 150.0f, 0.0f }))
            switchTabs = 2;
        ImGui::SameLine(0.0f, 2.0f);
        if (ImGui::Button(categories[3].categoryName.c_str(),
            ImVec2{ 100.0f, 0.0f }))
            switchTabs = 3;

        switch (switchTabs)
        {
        case 0:
            showCategoryTab(categories[0]);
            break;

        case 1:
            showCategoryTab(categories[1]);
            break;

        case 2:
            showCategoryTab(categories[2]);
            break;

        case 3:
            showCategoryTab(categories[3]);
            break;
        }
    }
    else if (menuChoice == 2)
    {
        if (ImGui::Button(categories[2].categoryName.c_str(),
            ImVec2{ 150.0f, 0.0f }))
            switchTabs = 0;
        showCategoryTab(categories[2]);
    }
}

//
// A control module that shows different inputs for each subcategory
//
void showCategoryTab(Category& category)
{
    for (int i = 0; i < category.subcategorySize; i++)
    {
        if (ImGui::TreeNode(category.subcategories[i].subcategoryName.c_str()))
        {
            inputSubcategory(category.subcategories[i]);
            addNewTransaction(category.subcategories[i]);
            ImGui::TreePop();
        }
    }
}

//
// An input module that takes in input from the user for each subcategory
//
void inputSubcategory(Subcategory& subcategory)
{    
    for (int i = 0; i < subcategory.transactionsSize; i++)
    {
        std::string nameIdentifier = "##Transaction name" + std::to_string(i);
        std::string amountIdentifier = "##Amount" + std::to_string(i);

        ImGui::PushItemWidth(100);
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Transaction");
        ImGui::SameLine();
        ImGui::InputText(nameIdentifier.c_str(), &subcategory.transactions[i]);
        ImGui::SameLine();
        ImGui::Text("Amount");
        ImGui::AlignTextToFramePadding();
        ImGui::SameLine();
        ImGui::InputScalar(amountIdentifier.c_str(), ImGuiDataType_Float,
            &subcategory.amounts[i]);
        if (subcategory.amounts[i] < 0)
        {
            subcategory.amounts[i] = 0;
        }
    }
}

//
// An input module that places an empty vector and increments values for 
// each subcategory and vise varsa
//
void addNewTransaction(Subcategory& subcategory)
{
    if (ImGui::Button("+"))
    {
        subcategory.transactions.push_back("");
        subcategory.amounts.push_back(0);
        subcategory.transactionsSize++;
    }
    ImGui::SameLine();
    if (ImGui::Button("-"))
    {
        if (subcategory.transactionsSize > 0)
        {
            subcategory.transactions.pop_back();
            subcategory.amounts.pop_back();
            subcategory.transactionsSize--;
        }
    }
}

void backNextButton(int& userChoice, std::string buttonName, int outcome)
{
    if (ImGui::Button(buttonName.c_str()))
    {
        userChoice = outcome;
    }
}