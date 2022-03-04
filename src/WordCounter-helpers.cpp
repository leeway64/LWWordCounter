#include <string>
#include <fstream>
#include <algorithm>

#include "WordCounter-helpers.hpp"


void CounterHelpers::createInputJSON(const std::string& input_file_name)
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


std::unordered_map<std::string, int> CounterHelpers::getWordCounts(const std::string& input_file_name)
{
    std::unordered_map<std::string, int> wordCounts;
    std::string next;
    std::ifstream input(input_file_name);
    while(input >> next)
    {
        std::transform(next.begin(), next.end(), next.begin(), tolower);
        if(!wordCounts.contains(next))
        {
            wordCounts[next] = 1;
        }
        else
        {
            wordCounts[next]++;
        }
    }
    input.close();
    return wordCounts;
}


int CounterHelpers::getTotalWords(std::unordered_map<std::string, int> wordCounts)
{
    int wordsSum = 0;
    for (auto keyValue : wordCounts)
    {
        wordsSum += keyValue.second;
    }
    return wordsSum;
}


std::pair<std::string, int> CounterHelpers::getMostPopularWord(const std::unordered_map<std::string, int>& wordCounts)
{
    std::pair<std::string, int> popularStats;
    std::string mostPopularWord;
    int highestFrequency = 0;
    for(auto keyValue : wordCounts) {
        if (keyValue.second >= highestFrequency)
        {
            highestFrequency = keyValue.second;
            mostPopularWord = keyValue.first;
        }
    }
    popularStats.first = mostPopularWord;
    popularStats.second = highestFrequency;
    return popularStats;
}
