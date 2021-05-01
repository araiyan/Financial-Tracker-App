/******************************************************************************
// Course# CISP 360 
// Team# 11
// Names: Ahmed Sazid Raiyan, Victoria To, Mohammad Ayub Hanif Saleh,
//        Minh Huynh, Thuy Anh Huynh, Rayana Huq
// Student IDs: 1824324, 1928280, 1790101, 1463724, 1767364, 1743599

******************************************************************************/
// Assignment Final Project - Financial Tracker App
// Program file name: financialTrackerApp.cpp
// Program description: A program that tracks a user's financial status for
//                      every month


#include "Header Files\financialAppHeader.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "libs/imgui.h"
#include "libs/imgui-SFML.h"
#include "libs/imgui_stdlib.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#define FILE_NAME "data.txt"
#define HISTORY_FILE_NAME "history.txt"

int main()
{
    std::ifstream inputFile;
    std::ofstream outputFile;
    std::ofstream historyFile;

    Category* categories;
    Category minimumNonFixedExpenses;
    Category amountsToSave;

    sf::Texture backgroundPic;
    sf::Sprite backgroundSprite;

    // Tries to open the background image
    try
    {
        if (backgroundPic.loadFromFile("background.jpg"))
        {
            backgroundSprite.setTexture(backgroundPic);
        }
        else
        {
            throw backgroundPic;
        }
    }
    catch (...)
    {
        std::cout << "Image not found" << std::endl;
        std::cout << "Please make sure you have an image with the name "
            << "\"background.jpg\" on the same folder as your "
            << "'Financial Advisor App.cpp'" << std::endl;
    }

    std::string scenario;
    int eventWindow = 0;
    int menuChoice = 0;
    int nextOrPrevious = 0;
    int outcome;
    float totalTransactions[4];
    bool saveFile = false;

    ////////////////// Preprocessing ////////////////// 
    categories = initializeAllCategories();
    minimumNonFixedExpenses = initializeMinimumNonFixedExpenses();

    inputFile.open(FILE_NAME);
    if (!inputFile)
    {
        std::cout << "Cannot open input file. Making a new input file"
            << std::endl;
        inputFile.close();
        outputFile.open(FILE_NAME);
        outputFile.close();
        inputFile.open(FILE_NAME);
    }

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Financial Advisor");
    ImVec2 windowSize;
    window.setFramerateLimit(30);
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        windowSize = ImVec2 { static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y) };
        
        window.clear();
        window.draw(backgroundSprite);
        
        switch (eventWindow)
        {
            case 0:
                menu(inputFile, categories, menuChoice, windowSize);
                if (menuChoice == 1 || menuChoice == 2)
                    eventWindow += 1;
                else if (menuChoice == 3)
                    eventWindow += 2;
                break;

            case 1:
                input(categories, menuChoice, nextOrPrevious, windowSize);
                if (nextOrPrevious == 1)
                {
                    nextOrPrevious = 0;
                    menuChoice = 0;
                    eventWindow--;
                }
                if (nextOrPrevious == 2)
                {
                    nextOrPrevious = 0;
                    eventWindow += 2;
                }
                else if (nextOrPrevious == 3)
                {
                    nextOrPrevious = 0;
                    categories = initializeAllCategories();
                }
                break;

            case 2:
                showHelp(window, nextOrPrevious, windowSize);
                if (nextOrPrevious == 1)
                {
                    nextOrPrevious = 0;
                    eventWindow -= 2;
                    menuChoice = 0;
                }
                break;

            case 3:
                processing(categories, minimumNonFixedExpenses, amountsToSave,
                    outcome, totalTransactions, scenario);
                eventWindow++;
                saveFile = true;
                break;

            case 4:
                output(outcome, totalTransactions, amountsToSave,
                    nextOrPrevious, windowSize, scenario);
                if (nextOrPrevious == 1)
                {
                    nextOrPrevious = 0;
                    eventWindow -= 3;
                    saveFile = false;
                    amountsToSave.subcategories.clear();
                    amountsToSave.subcategorySize = 0;
                }
                else if (nextOrPrevious == 2)
                {
                    nextOrPrevious = 0;
                    eventWindow += 1;
                }
                break;

            case 5:
                window.close();
                break;
            default:
                std::cout << "ERROR!!!" << std::endl;
                window.close();
                break;

        }
        
        ImGui::SFML::Render(window);
        window.display();
    }

    ////////////////////// Postprocessing ////////////////////////////
    inputFile.close(); 
    if (saveFile)
    {
        saveFileOnMenuChoice(menuChoice, outputFile, historyFile, categories);
    }
    ImGui::SFML::Shutdown();
}
