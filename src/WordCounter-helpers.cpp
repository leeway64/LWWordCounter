#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <regex>

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
    // Split word based on space
    while(input >> next)
    {
        // Convert each word to lowercase
        std::transform(next.begin(), next.end(), next.begin(), tolower);

        // Split word based on regular expression
        /// TODO:
        ///   - select the correct regular expression. Regular expression should match
        ///   - everything that is not a word character.
        std::regex rgx("\\s+");
        std::sregex_token_iterator iter(next.begin(), next.end(), rgx, -1);
        std::sregex_token_iterator end;

        for (iter; iter != end; ++iter) {
            if (!wordCounts.contains(*iter)) {
                wordCounts[next] = 1;
            } else {
                wordCounts[next]++;
            }
        }
    }
    input.close();
    return wordCounts;
}


int CounterHelpers::getTotalWords(std::unordered_map<std::string, int> wordCounts)
{
    int wordsSum = 0;
    for (const auto& keyValue : wordCounts)
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
    for(const auto& keyValue : wordCounts) {
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

std::map<std::string, int> CounterHelpers::getTopKWords(const std::unordered_map<std::string, int> &wordCounts, const int k){
    std::map<std::string, int> topKWords{};

    if (k < 0)
    {
        throw std::invalid_argument("\"k\" must be a positive integer");
    }
    else if (k > wordCounts.size())
    {
        throw std::invalid_argument("\"k\" must be less than or equal to the number of unique words in the text file");
    }
    else if (k == 0)
    {
        return topKWords;
    }

    std::vector<std::pair<std::string, int>> topWordsHeap{};
    topWordsHeap.reserve(k);  // Create vector k elements large

    auto iter = wordCounts.begin();
    for (int i = 0; i < k; ++i, iter++)  // Add k elements from the unordered map to the vector
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
    for (iter; iter != wordCounts.end(); ++iter)
    {
        if (iter->second > topWordsHeap.front().second)
        {
            std::pop_heap(topWordsHeap.begin(), topWordsHeap.end(), larger);
            topWordsHeap.pop_back();

            std::pair<std::string, int> key_val_pair{iter->first, iter->second};
            topWordsHeap.push_back(key_val_pair);
            push_heap(topWordsHeap.begin(), topWordsHeap.end(), larger);
        }
    }

    auto smaller = [](std::pair<std::string, int> a, std::pair<std::string, int> b)
    {
        return a.first > b.first;
    };
    // Sort the vector/heap in descending frequency order. i.e., most common word appears first.
    std::sort(topWordsHeap.begin(), topWordsHeap.end(), smaller);

    // Put the vector's/heap's elements into a map to preserve the sorted order. An unordered map
    // would not preserve this order.
    for (const auto& pair: topWordsHeap)
    {
        topKWords[pair.first] = pair.second;
    }

    return topKWords;
}
