#include "financialAppHeader.h"
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>

void makeMultipleLines(int lineCount);
bool isFileEmpty(std::ifstream& inputFile);

void menu(std::ifstream& inputFile, Category categories[], int& menuChoice,
    ImVec2 windowSize)
{
    static bool emptyFile = isFileEmpty(inputFile);
    ImVec2 buttonSize = { 400, 50 };
    ImGuiWindowFlags windowFlags = 0;
    ImGuiStyle& style = ImGui::GetStyle();

    // Makes all the buttons nice and curvy :3
    style.FrameRounding = 15.0f;

    windowFlags |= ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    windowFlags |= ImGuiWindowFlags_NoBackground;

    //////////// Menu Window ////////////
    ImGui::SetNextWindowSize(ImVec2{ 600.0f, 800.0f }, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2{ ((windowSize.x/2.0f) - 300),
        (windowSize.y/2.0f) - 200.0f - (200.0f * (windowSize.y/1080)) },
        ImGuiCond_Always);
    ImGui::Begin("Menu", NULL, windowFlags);

    ImGui::SetWindowFontScale(1.2f);

    makeMultipleLines(4);
    ImGui::Spacing();
    ImGui::SameLine(ImGui::GetWindowSize().x * 0.5f - (buttonSize.x / 2.0f));
    if (ImGui::Button("New Session", buttonSize))
    {
        if (emptyFile)
        {
            menuChoice = 1;
        }
        else
        {
            ImGui::OpenPopup("New Session Confirmation");
        }
    }

    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing,
        ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("New Session Confirmation", NULL,
        ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::SetWindowFontScale(0.8f);
        ImGui::Text("Your previous transactions will be deleted if you");
        ImGui::Text("start a new session");
        ImGui::Text("Are you sure?");
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(120, 0)))
        {
            menuChoice = 1;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetWindowFontScale(1.2f);
        ImGui::EndPopup();
    }

    if (!emptyFile)
    {
        makeMultipleLines(4);
        ImGui::Spacing();
        ImGui::SameLine(ImGui::GetWindowSize().x * 0.5f - (buttonSize.x / 2.0f));
        if (ImGui::Button("Continue Session", buttonSize))
        {
            defineAllCategories(inputFile, categories);
            menuChoice = 2;
        }
    }

    makeMultipleLines(4);
    ImGui::Spacing();
    ImGui::SameLine(ImGui::GetWindowSize().x * 0.5f - (buttonSize.x / 2.0f));
    if (ImGui::Button("Exit", buttonSize))
    {
        exit(EXIT_SUCCESS);
    }

    ImGui::End();

    style.FrameRounding = 1.0f;

}

//
// Display module that makes multiple new lines
//
void makeMultipleLines(int lineCount)
{
    for (int i = 0; i < lineCount; i++)
    {
        ImGui::NewLine();
    }
}

//
// A display module to show a wrapped text
// ended up not using this but can be used on future programs
//
void showWrappedText(std::string descriptionText, float wrapWidth,
    ImColor wrapColor, ImVec2 buttonSize, int lineSpace)
{
    makeMultipleLines(lineSpace);
    ImGui::Spacing();
    ImGui::SameLine(ImGui::GetWindowSize().x * 0.5f - (buttonSize.x / 2.0f)
        + 20.0f);
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(wrapWidth, 2.0f),
        ImVec2(20.0f + wrapWidth, 20.0f + ImGui::GetTextLineHeight()),
        wrapColor);
    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrapWidth);
    ImGui::Text(descriptionText.c_str());
    ImGui::GetWindowDrawList()->AddRect(ImVec2(ImGui::GetItemRectMin().x - 2,
        ImGui::GetItemRectMin().y - 2), ImVec2(ImGui::GetItemRectMax().x + 4,
        ImGui::GetItemRectMax().y + 4), wrapColor);
    ImGui::PopTextWrapPos();
}

//
// A processing module that checks to see if a file is empty
//
bool isFileEmpty(std::ifstream& inputFile)
{
    return inputFile.peek() == std::ifstream::traits_type::eof();
}