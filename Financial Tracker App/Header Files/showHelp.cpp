#include "financialAppHeader.h"
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

void showHelp(sf::RenderWindow& window,
    int& nextOrPrevious, ImVec2 windowSize)
{
    static sf::Texture showhelpPic;
    static sf::Sprite showhelpSprite;

    static sf::Texture showhelpPic_2;
    static sf::Sprite showhelpSprite_2;

    static sf::Texture showhelpPic_3;
    static sf::Sprite showhelpSprite_3;

    static sf::Texture showhelpPic_4;
    static sf::Sprite showhelpSprite_4;

    showhelpPic.loadFromFile("showHelp pics.jpg");
    showhelpSprite.setOrigin(-300, -180);
    showhelpSprite.setTexture(showhelpPic);

    showhelpPic_2.loadFromFile("showHelp pics #2.jpg");
    showhelpSprite_2.setOrigin(-300, -180);
    showhelpSprite_2.setTexture(showhelpPic_2);

    showhelpPic_3.loadFromFile("showHelp pics #3.jpg");
    showhelpSprite_3.setOrigin(-300, -180);
    showhelpSprite_3.setTexture(showhelpPic_3);

    showhelpPic_4.loadFromFile("showHelp pics #4.jpg");
    showhelpSprite_4.setOrigin(-300, -180);
    showhelpSprite_4.setTexture(showhelpPic_4);

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

    switch (showHelpTab)
    {
        case 0:
            window.draw(showhelpSprite);
            break;
        case 1:
            window.draw(showhelpSprite_2);
            break;
        case 2:
            window.draw(showhelpSprite_3);
            break;
        case 3:
            window.draw(showhelpSprite_4);
            break;
    }
}