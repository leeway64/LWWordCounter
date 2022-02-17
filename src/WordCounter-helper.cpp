#include <string>
#include <fstream>

#include "WordCounter-helper.hpp"

void CounterHelpers::createInputJSON(std::string input_file_name)
{
    std::ofstream output(input_file_name);
    // Write brackets so that the file can be correctly read as a JSON file
    output << "{\n}\n";
    output.close();
}

void CounterHelpers::getJSON(const std::string& file_name, nlohmann::json& JSONVariable)
{
    std::ifstream input(file_name);
    input >> JSONVariable;
    input.close();
}

std::unordered_map<std::string, int> CounterHelpers::getWordCounts(std::string input_file_name)
{
    std::unordered_map<std::string, int> wordCounts;
    std::string next;
    std::ifstream input3(input_file_name);
    while(input3 >> next)
    {
        if(!wordCounts.contains(next))
        {
            wordCounts[next] = 1;
        }
        else
        {
            wordCounts[next]++;
        }
    }
    input3.close();
    return wordCounts;
}

int CounterHelpers::getTotalWords(std::unordered_map<std::string, int> wordCounts)
{
    int wordsSum = 0;
//    for (auto keyValue : wordCounts)
//    {
//        wordsSum += keyValue.second
//    }
    return wordsSum;
}
