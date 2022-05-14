#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <regex>
#include <optional>

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

        // Split word based on regular expression. Regular expression matches everything that is
        // not a through z, A through Z, 0 through 9, or an apostrophe.
        std::regex rgx("[^a-zA-Z0-9']");

        std::sregex_token_iterator iter(next.begin(), next.end(), rgx, -1);
        std::sregex_token_iterator end;

        for (iter; iter != end; ++iter)
        {
            std::string word = *iter;
            // To handle the case where the string is a back slash or forward slash character.
            if (word != "")
            {
                if (!wordCounts.contains(word))
                {
                    wordCounts[word] = 1;
                }
                else
                {
                    wordCounts[word]++;
                }
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

std::deque<std::string> CounterHelpers::get_longest_shortest_words(const std::unordered_map<std::string, int> &wordCounts)
{
    std::string shortest_word{};
    if (wordCounts.size() > 0)
    {
        shortest_word = wordCounts.begin()->first;
    }

    // decltype, in this case, sets longest_word to the same data type as shortest_word
    decltype(shortest_word) longest_word{};

    for (const auto& [key, value]: wordCounts)
    {
        if (key.length() > longest_word.length())
        {
            longest_word = key;
        }
        if (key.length() < shortest_word.length())
        {
            shortest_word = key;
        }
    }

    // A deque is a double-ended queue
    std::deque<std::string> longest_shortest_words{};
    longest_shortest_words.push_front(longest_word);
    longest_shortest_words.push_back(shortest_word);
    return longest_shortest_words;
}

std::optional<CounterHelpers::info> CounterHelpers::get_certain_length_words_frequency
                                (const std::unordered_map<std::string, int> &wordCounts, const int word_length_to_find)
{
    std::unordered_set<int> lengths_set;
    std::vector<std::string> key_vector{};
    for (const auto& [key, value]: wordCounts)
    {
        lengths_set.insert(key.length());
        key_vector.push_back(key);
    }
    // Find if the target word length exists in the unordered set
    const auto contains_length = std::find(std::begin(lengths_set), std::end(lengths_set), word_length_to_find);
    if (contains_length == std::end(lengths_set))
    {
        return {};
    }
    // Count how many words of the target length exist in the wordCounts map
    CounterHelpers::info num_items;
    // count_if counts the number of elements for which the function (last argument) returns true.
    // The "[]" in a lambda is its capture clause. It can access variables from its current scope.
    // The "()" in a lambda is kind of like a parameter list for a function.
    num_items.num_words = std::count_if(key_vector.begin(), key_vector.end(),
                                [word_length_to_find](std::string word){return word.length() == word_length_to_find;});

    return num_items;
}
