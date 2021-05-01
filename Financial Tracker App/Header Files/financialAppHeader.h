#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <future>
#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include <SFML/Graphics.hpp>

//
// Struct for storing information about different subcategories
//
struct Subcategory
{
    std::string subcategoryName;
    std::vector<std::string> transactions;
    std::vector<float> amounts;
    int transactionsSize = 0;
};

//
// Struct for storing information about different categories
//
struct Category
{
    std::string categoryName;
    std::vector<Subcategory> subcategories;
    int subcategorySize = 0;
};

//
// A function that creates a pointer to an array of Category then defines
// each Category name and pushes back subcategory vectors for each subcategory
// for that category and names each subcategory. Then, it returns the pointer
// to that array of Category
//
Category* initializeAllCategories();

//
// A function that returns a Category for Non Fixed Expenses then fills each
// Subcategory with the minimum amount of money average person needs to spend
// in order to survive.
//
Category initializeMinimumNonFixedExpenses();

//
// An input module that prompts the user with a menu which have 4 different 
// choices where they can make a new financial advising session, continue an 
// old financial advising session, ask for help on how to use the program or 
// exit the program.
//
void menu(std::ifstream& inputFile, Category categories[], int& menuChoice,
    ImVec2 windowSize);

//
// An output module that creates new lines inside a tab
//
void makeMultipleLines(int lineCount);

//
// An input module that takes in an array of Category and an input file,
// then carefully places each of the transactions the user did in the past
// month from the input file to each of the subcategory for every Category in
// the array except for the Non Fixed Expenses Category
//
void defineAllCategories(std::ifstream& inputFile, Category categories[]);

//
// A display module to display text wrapped in a rectangle
//
void showWrappedText(std::string descriptionText, float wrapWidth,
    ImColor wrapColor, ImVec2 buttonSize, int lineSpace);

//
// An input module that takes in different transaction and places them
// on each Category and Subcategory accordingly. Depending on menuChoice
// the input module will either take input for all the categories or
// input for only the non fixed expenses Category
//
void input(Category categories[], int menuChoice, int& nextOrPrevious,
    ImVec2 windowSize);

//
// An input module that makes input boxes for all the transactions 
// for each Subcategory. 
//
void inputSubcategory(Subcategory& subcategory);

//
// An input that sets a button to switch between windows
// 
void backNextButton(int& userChoice, std::string buttonName, int outcome);

//
// A processing module that takes in an array of Category for the user inputs
// then compares it with the minimumExpenses Category to see how much money
// the user could potentially save and fingures out if the user can meet their
// goals. If they can't meet their goals the program will calculate how much
// money the user has to save on each Subcategory to meet their goals. The
// module also calculates the total amount of money spent on each Category
// and saves the information in totalTransactions. The module will then
// place an integer value to outcome depending on different scenarios. Ex:
// the outcome will be 0 if the user goes into debt each month OR outcome will
// be 1 if the user doesn't have enough money left to met their goals even
// if they spend the minimum amount of money for their non fixed expenses.
//
void processing(Category categories[], Category minimumExpenses,
    Category& amountToSave, int& outcome, float totalTransactions[],
    std::string& scenario);

//
// A processing module that makes a pointer to an array then calculates
// the total amount of transactions for each subcategory thats inside
// each category and places the total amount for each category on each 
// subscript of the array. Then returns the address of the array.
//
float* calculateTotalForCategory(Category categories[]);

//
// A processing module that calculates how much the user should be
// saving from each subcategory to meet their monthy goals
//
void calculateAmountToSave(Category categories[], Category minimumExpenses,
    Category& amountToSave, float totalGoals);

//
// This is a processing function that calculates the total potential
// amount to save for all of the subcategories.
//
float calTotalAmountToSave(Category categories[], Category minimumExpenses);

//
// An output module that will choose a scenario based on the outcome variable
// and the totalTransactions array will pass all the 5 different type of
// calculated Transaction. The amountToSave Category will be used to
// show how much the user could've saved.
//
void output(int outcome, float totalTransactions[], Category& amountToSave,
    int& nextOrPrevious, ImVec2 windowSize, std::string scenario);

//
// An output module that displays the total amount of income the user has
// and the total amount of money the user spends for fixed expenses and non
// fixed expenses and also the total amount of money they want to have for
// their goals.
//
void displayTotalTransactions(float totalTransactions[]);

//
// An output module that takes in an integer outcome then decides what senario
// to display to the user. It will use a random number generator to pick
// a sentence from a string to display to the user depending on the outcome
//
void displayUniqueEvents(int outcome, std::string scenario);

//
// An output module that displays the an amount the user should be saving each
// month from each subcategory to meet their goals
//
void displayAmountToSave(Category& amountToSave);

//
// An output module that saves the information in a text file by the using
// fstream outputfile and the categories array will hold the information about
// the different categories.
//
void saveDataFile(std::ofstream& outputFile, Category categories[]);

//
// An output module that saves files depending on the program outcome
//
void saveFileOnMenuChoice(int menuChoice, std::ofstream& outputFile,
    std::ofstream& historyFile, Category categories[]);
//
// A output module that shows the user how the program works and how
// they can use it. the showHelp module uses background pictures to
// explain everything.
//
void showHelp(sf::RenderWindow& window,
    std::future<std::vector<sf::Texture>>& futr, int& nextOrPrevious,
    ImVec2 windowSize);

//
// An input module to get all the textures
//
void loadTextures(std::promise<std::vector<sf::Texture>>&& prms);