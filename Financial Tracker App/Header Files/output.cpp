#include "financialAppHeader.h"
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>

void table(std::string name, float amount);
void selectionSort(Category& amountToSave, bool header_clicker_flag);

void output(int outcome, float totalTransactions[], Category& amountToSave,
    int& nextOrPrevious, ImVec2 windowSize, std::string scenario)
{
    ImGuiWindowFlags windowFlags = 0;

    windowFlags |= ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoCollapse;

    ImGui::SetNextWindowSize(ImVec2{ 600.0f, 600.0f }, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2{ ((windowSize.x / 2.0f) - 300),
        (windowSize.y / 2.0f) - 175.0f - (225.0f * (windowSize.y / 1080)) },
        ImGuiCond_Always);
    ImGui::Begin("Display data", NULL, windowFlags);

    displayTotalTransactions(totalTransactions);
    ImGui::Text("");
    displayUniqueEvents(outcome, scenario);
    ImGui::Text("");
    if (outcome == 5)
        ImGui::Text("Here is a list of subcategories to save money on");
    else
    {
        ImGui::Text("Since you don't meet the requirements for saving,");
        ImGui::Text("the table below is empty");
    }
    displayAmountToSave(amountToSave);

    makeMultipleLines(3);
    ImGui::Spacing();
    ImGui::SameLine(ImGui::GetWindowSize().x * 0.8f);
    backNextButton(nextOrPrevious, "Back", 1);
    ImGui::SameLine();
    backNextButton(nextOrPrevious, "Exit", 2);

    ImGui::End();
}

void displayTotalTransactions(float totalTransactions[])
{
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
    static std::string categoryNames[] = { "Income", "Fixed Expenses",
        "Non Fixed Expenses", "Goals" };

    if (ImGui::BeginTable("Total Transactions", 2, flags))
    {
        ImGui::TableSetupColumn("Total Transactions");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableHeadersRow();

        for (int i = 0; i < 4; i++)
            table(categoryNames[i], totalTransactions[i]);
        
        ImGui::EndTable();
    }
    
}

void displayAmountToSave(Category& amountToSave)
{
    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Sortable;

    static bool ascending = true;
    
    if (ImGui::BeginTable("", 2, flags))
    {
        ImGui::TableSetupColumn("Subtransactions");
        ImGui::TableSetupColumn("savable amount");
        ImGui::TableHeadersRow();

        ///////////////// selection sort ///////////////////
        ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs();
        if (sorts_specs->SpecsDirty)
        {
            ascending = !ascending;
            selectionSort(amountToSave, ascending);
            sorts_specs->SpecsDirty = false;
        }

        for (int i = 0; i < amountToSave.subcategorySize; i++)
        {
            table(amountToSave.subcategories[i].subcategoryName,
                amountToSave.subcategories[i].amounts[0]);
        }
        ImGui::EndTable();
    }
}

//
// this processing module takes the amountToSave and reorders it depending
// user's choice using selection sort
// 
void selectionSort(Category& amountToSave, bool ascending)
{
    int min_index, pass = 0;
    Subcategory min_value;
    for (int start_index = 0; start_index < (amountToSave.subcategorySize);
        start_index++)
    {
        min_index = start_index;
        min_value = amountToSave.subcategories[start_index];
        for (int index = start_index + 1; index < amountToSave.subcategorySize;
            index++)
        {
            if (ascending)
            {
                if (amountToSave.subcategories[index].amounts[0] <
                min_value.amounts[0])
                {
                    min_index = index;
                    min_value = amountToSave.subcategories[index];
                }
            }
            else if (!ascending)
            {
                if (amountToSave.subcategories[index].amounts[0] >
                min_value.amounts[0])
                {
                    min_index = index;
                    min_value = amountToSave.subcategories[index];
                }
            }
        }
        amountToSave.subcategories[min_index] = 
            amountToSave.subcategories[start_index];
        amountToSave.subcategories[start_index] = min_value;
    }
}

//
// this output module prints out the name of the string that is given on the
// table and also take the amount and puts it in the front column.
// 
void table(std::string name, float amount)
{
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text(name.c_str());

    ImGui::TableSetColumnIndex(1);
    ImGui::Text("%0.2f", amount);
}
