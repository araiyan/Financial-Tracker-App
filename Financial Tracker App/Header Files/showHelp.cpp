#include "financialAppHeader.h"
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>
#include <vector>
#include <future>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

void loadTexture(std::string fileName, sf::Texture& showHelpSprite);

void showHelp(sf::RenderWindow& window,
    std::future<std::vector<sf::Texture>>& futr, int& nextOrPrevious,
    ImVec2 windowSize)
{
    static std::vector<sf::Texture> textures = futr.get();
    static sf::Sprite showHelpSprite;
    ImGuiWindowFlags windowFlags = 0;
    static int showHelpTab = 0;
    ImVec2 buttonSize = { 400, 50 };

    windowFlags |= ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoResize;
    windowFlags |= ImGuiWindowFlags_NoCollapse;
    windowFlags |= ImGuiWindowFlags_NoBackground;
    windowFlags |= ImGuiWindowFlags_NoScrollbar;

    ImGui::SetNextWindowSize(ImVec2{ 1330.0f, 800.0f }, ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2{ ((windowSize.x / 2.0f) -663),
        (windowSize.y / 2.0f) - 155.0f - (225.0f * (windowSize.y / 1080)) },
        ImGuiCond_Always);

    ImGui::Begin("Show Help:", NULL, windowFlags);

    makeMultipleLines(42);
    backNextButton(showHelpTab, "Previous", showHelpTab - 1);

    ImGui::SameLine(ImGui::GetWindowSize().x * 0.96f);
    backNextButton(showHelpTab, "Next", showHelpTab + 1);
    
    ImGui::End();

    if (showHelpTab > 3 || showHelpTab < 0)
    {
        nextOrPrevious = 1;
        showHelpTab = 0;
    }

    showHelpSprite.setOrigin(-300, -180);
    showHelpSprite.setTexture(textures[showHelpTab]);
    window.draw(showHelpSprite);
}

void loadTextures(std::promise<std::vector<sf::Texture>>&& prms)
{
    std::vector<sf::Texture> sprites;
    std::string fileNames[4] = 
    {
        "showHelp pics #1.jpg",
        "showHelp pics #2.jpg",
        "showHelp pics #3.jpg",
        "showHelp pics #4.jpg"
    };
    for (int i = 0; i < 4; i++)
    {
        sf::Texture showHelpTexture;
        loadTexture(fileNames[i], showHelpTexture);
        sprites.push_back(std::move(showHelpTexture));
    }

    prms.set_value(sprites);
}

//
// An input module to load in a sprite
//
void loadTexture(std::string fileName, sf::Texture& showHelpPic)
{
    showHelpPic.loadFromFile(fileName);
}