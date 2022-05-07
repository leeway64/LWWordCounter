#ifndef LWWORDCOUNTER_WORDCOUNTER_HELPERS_H
#define LWWORDCOUNTER_WORDCOUNTER_HELPERS_H

#include <unordered_map>
#include <map>
#include <string>
#include <deque>
#include <optional>

#include <nlohmann/json.hpp>

namespace CounterHelpers
{
    // A union can only hold one of its members at a time
    union info
    {
        int num_words = 0;
        // A byte is a separate data type that implements a byte
        std::byte bits;
        // A pointer that can hold a pointer to void
        std::uintptr_t ptr;
    };

    /// Create the JSON file that the user will enter the input into.
    /// @param input_file_name is the name of the JSON file to be created
    void createInputJSON(const std::string& input_file_name);

    /// Parse the input JSON file.
    /// @param file_name is the
    /// @param JSONVariable is the
    void getJSON(const std::string& file_name, nlohmann::json& JSONVariable);

    /// Get the word counts of the file. i.e., find how many times word x appears in the file.
    /// @param input_file_name is the name of the text file to analyze.
    /// @return An unordered_map containing the word and frequency of the word as a key-value pair.
    std::unordered_map<std::string, int> getWordCounts(const std::string& input_file_name);

    /// @param wordCounts is the unordered_map containing the frequency of each word in the text file.
    /// @return The total number of words in the text file.
    int getTotalWords(std::unordered_map<std::string, int> wordCounts);

    /// @param wordCounts is the unordered_map containing the frequency of each word in the text file.
    /// @return A pair containing the most common word and the corresponding number of occurrences.
    std::pair<std::string, int> getMostPopularWord(const std::unordered_map<std::string, int>& wordCounts);

    /// @param wordCounts is the unordered_map containing the frequency of each word in the text file.
    /// @param k is the top "k" most popular words to find.
    /// @return A map containing the top "k" most popular words and their corresponding frequencies.
    std::map<std::string, int> getTopKWords(const std::unordered_map<std::string, int>& wordCounts, int k);

    /// @param wordCounts is the unordered_map containing the frequency of each word in the text file.
    /// @return A deque (doubled-ended queue) containing the longest and shortest words, in that order.
    std::deque<std::string> get_longest_shortest_words(const std::unordered_map<std::string, int> &wordCounts);

    /// @param wordCounts is the unordered_map containing the frequency of each word in the text file.
    /// @param
    /// @return An info union, with its num_words field holding the number of words that have lengths equal to target.
    std::optional<info> get_certain_length_words_frequency(
                                const std::unordered_map<std::string, int> &wordCounts, const int word_length_to_find);
}

#endif //LWWORDCOUNTER_WORDCOUNTER_HELPERS_H
