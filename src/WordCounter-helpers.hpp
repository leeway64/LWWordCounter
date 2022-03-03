#ifndef LWWORDCOUNTER_WORDCOUNTER_HELPERS_H
#define LWWORDCOUNTER_WORDCOUNTER_HELPERS_H

#include <unordered_map>
#include <string>

#include <nlohmann/json.hpp>


namespace CounterHelpers
{
    void createInputJSON(const std::string& input_file_name);

    void getJSON(const std::string& file_name, nlohmann::json& JSONVariable);

    std::unordered_map<std::string, int> getWordCounts(const std::string& input_file_name);

    int getTotalWords(std::unordered_map<std::string, int> wordCounts);

    std::pair<std::string, int> getMostPopularWord(const std::unordered_map<std::string, int>& wordCounts);
}

#endif //LWWORDCOUNTER_WORDCOUNTER_HELPERS_H
