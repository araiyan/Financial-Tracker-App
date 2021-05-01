#include "financialAppHeader.h"
#include <iostream>
#include <string>
#include <fstream>

#define NUM_CATEGORY 4
#define FILE_NAME "data.txt"
#define HISTORY_FILE_NAME "history.txt"

void getSubcategories(std::ifstream& inputFile, Category& category);
void getTransactions(std::ifstream& inputFile, Subcategory& subcategory);
void searchInFile(std::ifstream& inputFile, std::string searchName);
std::string trim(const std::string& string);
void skipEndLine(std::ifstream& inputFile, std::string& name);


void defineAllCategories(std::ifstream& inputFile, Category categories[])
{
    inputFile.seekg(0);
    std::string inputCategoryName;
    for (int i = 0; i < NUM_CATEGORY; i++)
    {
        skipEndLine(inputFile, inputCategoryName);
        inputCategoryName = trim(inputCategoryName);

        if (inputCategoryName != categories[2].categoryName)
            getSubcategories(inputFile, categories[i]);
        else 
            searchInFile(inputFile, categories[3].categoryName);
    }
}

void saveDataFile(std::ofstream& outputFile, Category categories[])
{
    for (int i = 0; i < NUM_CATEGORY; i++)
    {
        outputFile << categories[i].categoryName << std::endl;

        for (Subcategory subcategory : categories[i].subcategories)
        {
            outputFile << "    " << subcategory.subcategoryName << std::endl;
            outputFile << "        " << subcategory.transactionsSize;
            outputFile << std::endl;

            for (int z = 0; z < subcategory.transactionsSize; z++)
            {
                outputFile << "        " << subcategory.transactions[z]
                    << std::endl << "          " << subcategory.amounts[z]
                    << std::endl;
            }
        }

        outputFile << std::endl;
    }
}

//
// An input module to get the information on every subcategory for a category
//
void getSubcategories(std::ifstream& inputFile, Category& category)
{
    std::string inputSubcategoryName;

    for (int i = 0; i < category.subcategorySize; i++)
    {
        skipEndLine(inputFile, inputSubcategoryName);
        inputSubcategoryName = trim(inputSubcategoryName);

        if (inputSubcategoryName == category.subcategories[i].subcategoryName)
            getTransactions(inputFile, category.subcategories[i]);
    }
}

//
// An input module to get each transaction for a subcategory
//
void getTransactions(std::ifstream& inputFile, Subcategory& subcategory)
{
    std::string inputTransaction;
    float amount;

    inputFile >> subcategory.transactionsSize;

    for (int i = 0; i < subcategory.transactionsSize; i++)
    {
        skipEndLine(inputFile, inputTransaction);
        inputTransaction = trim(inputTransaction);
        inputFile >> amount;
        subcategory.transactions.push_back(inputTransaction);
        subcategory.amounts.push_back(amount);
    }
}

//
// An input file that finds a specific name inside the file
//
void searchInFile(std::ifstream& inputFile, std::string searchName)
{
    std::string foundName = "";
    std::streamoff nameSize;

    while ((foundName != searchName) || (inputFile.eof()))
    {
        skipEndLine(inputFile, foundName);
        foundName = trim(foundName);
    }

    nameSize = foundName.size() + 2;

    inputFile.seekg(inputFile.tellg() - nameSize);
}

//
// A processing module that truncates a string to remove leading and following
// white spaces
//
std::string trim(const std::string& string)
{
    auto start = string.begin();
    while (start != string.end() && std::isspace(*start))
        start++;

    auto end = string.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

//
// An input module that takes in the end of a line and throws it away
//
void skipEndLine(std::ifstream& inputFile, std::string& name)
{
    do {
        std::getline(inputFile, name);
    } while (name == "");
}

void saveFileOnMenuChoice(int menuChoice, std::ofstream& outputFile,
    std::ofstream& historyFile, Category categories[])
{
    if (menuChoice == 1)
    {
        outputFile.open(FILE_NAME, std::ios::trunc);
        historyFile.open(HISTORY_FILE_NAME, std::ios::trunc);
    }
    else if (menuChoice == 2)
    {
        outputFile.open(FILE_NAME, std::ios::trunc);
        historyFile.open(HISTORY_FILE_NAME, std::ios::app);
    }

    if (menuChoice == 1 || menuChoice == 2)
    {
        saveDataFile(outputFile, categories);
        saveDataFile(historyFile, categories);
        outputFile.close();
        historyFile.close();
    }
}