#include <string>
#include <fstream>
#include <algorithm>
#include <map>

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

std::map<std::string, int> CounterHelpers::getTopKWords(const std::unordered_map<std::string, int> &wordCounts, int k){
// create vector k elements large
// Add k elements from the unordered map to it
// Turn that into min heap
// iterate through every element in unordered map. if any word has a count greater than the first
// count of the vector, replace the first count with that
// Sort this final vector. Put elements into ordered map.
    std::map<std::string, int> topKWords{};

    std::vector<std::pair<std::string, int>> topWordsHeap{};
    topWordsHeap.reserve(k);

    auto iter = wordCounts.begin();
    for (int i = 0; i < k; ++i, iter++)
    {
        std::pair<std::string, int> wordCount{iter->first, iter->second};
        topWordsHeap.push_back(wordCount);
    }

    auto larger = [](std::pair<std::string, int> a, std::pair<std::string, int> b)
            {
                return a.second > b.second;
            };
    // Create heap using lambda expression
    std::make_heap(topWordsHeap.begin(), topWordsHeap.end(), larger);

    // Insert the k most frequently appearing words into the heap
    for (auto const& [key, val]: wordCounts)
    {
        if (val > topWordsHeap.front().second)
        {
            std::pop_heap(topWordsHeap.begin(), topWordsHeap.end(), larger);
            topWordsHeap.pop_back();
        }
    }

    // Sort the vector/heap in descending frequency order. i.e., most common word appears first.
    std::sort(topWordsHeap.begin(), topWordsHeap.end(), larger);

    // Put the vector's/heap's elements into a map to preserve the sorted order. An unordered map
    // would not preserve this order.
    for (const auto& pair: topWordsHeap)
    {
        topKWords[pair.first] = pair.second;
    }

    return topKWords;
}

