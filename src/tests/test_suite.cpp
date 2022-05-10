#include <string>
#include <catch2/catch.hpp>

#include "../WordCounter-helpers.hpp"

std::pair<std::unordered_map<std::string, int>, std::string> getSummaryAndMostPopularWord(const std::unordered_map<std::string, int>& wordCounts)
{
    std::pair<std::unordered_map<std::string, int>, std::string> result;

    std::unordered_map<std::string, int> fileSummary;
    fileSummary["unique_words"] = wordCounts.size();
    fileSummary["total_words"] = CounterHelpers::getTotalWords(wordCounts);
    const std::pair<std::string, int> mostPopularWord = CounterHelpers::getMostPopularWord(wordCounts);
    fileSummary["highest_frequency"] = mostPopularWord.second;

    result.first = fileSummary;
    result.second = mostPopularWord.first;

    return result;
}

TEST_CASE("Test LWWordCounter", "[LWWordCounter]")
{
    SECTION("Empty file")
    {
        std::string file1 = "../src/tests/test_files/test1.txt";

        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(file1);
        auto summaryPopularWord = getSummaryAndMostPopularWord(wordCounts);

        REQUIRE(summaryPopularWord.second == "");

        REQUIRE(summaryPopularWord.first["total_words"] == 0);
        REQUIRE(summaryPopularWord.first["highest_frequency"] == 0);
        REQUIRE(summaryPopularWord.first["unique_words"] == 0);
    }

    SECTION("File with 1 word")
    {
        std::string file2 = "../src/tests/test_files/test2.txt";

        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(file2);
        auto summaryPopularWord = getSummaryAndMostPopularWord(wordCounts);
        auto kCommonWords = CounterHelpers::getTopKWords(wordCounts, 1);
        auto longest_shortest = CounterHelpers::get_longest_shortest_words(wordCounts);
        auto certain_length_frequency = CounterHelpers::get_certain_length_words_frequency(wordCounts, 5);

        REQUIRE(summaryPopularWord.second == "hello");

        REQUIRE(longest_shortest.front() == "hello");
        REQUIRE(longest_shortest.back() == "hello");

        REQUIRE(certain_length_frequency->num_words == 1);

        REQUIRE(summaryPopularWord.first["total_words"] == 1);
        REQUIRE(summaryPopularWord.first["highest_frequency"] == 1);
        REQUIRE(summaryPopularWord.first["unique_words"] == 1);

        REQUIRE(kCommonWords.size() == 1);
        REQUIRE(kCommonWords["hello"] == 1);

        REQUIRE(wordCounts["hello"] == 1);
    }

    SECTION("File with 4 words")
    {
        std::string file3 = "../src/tests/test_files/test3.txt";

        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(file3);
        auto summaryPopularWord = getSummaryAndMostPopularWord(wordCounts);
        auto kCommonWords = CounterHelpers::getTopKWords(wordCounts, 2);
        auto longest_shortest = CounterHelpers::get_longest_shortest_words(wordCounts);

        REQUIRE(summaryPopularWord.second == "a");

        REQUIRE(longest_shortest.front() == "c");
        REQUIRE(longest_shortest.back() == "c");

        REQUIRE(summaryPopularWord.first["total_words"] == 10);
        REQUIRE(summaryPopularWord.first["highest_frequency"] == 4);
        REQUIRE(summaryPopularWord.first["unique_words"] == 4);

        REQUIRE(kCommonWords.size() == 2);
        REQUIRE(kCommonWords["a"] == 4);
        REQUIRE(kCommonWords["d"] == 4);

        REQUIRE(wordCounts["a"] == 4);
        REQUIRE(wordCounts["b"] == 1);
        REQUIRE(wordCounts["c"] == 1);
        REQUIRE(wordCounts["d"] == 4);
    }

    SECTION("More complicated text file")
    {
        std::string file4 = "../src/tests/test_files/test4.txt";

        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(file4);
        auto summaryPopularWord = getSummaryAndMostPopularWord(wordCounts);
        auto kCommonWords = CounterHelpers::getTopKWords(wordCounts, 3);
        auto longest_shortest = CounterHelpers::get_longest_shortest_words(wordCounts);

        REQUIRE(summaryPopularWord.second == "the");

        REQUIRE(longest_shortest.front() == "makes");
        REQUIRE(longest_shortest.back() == "a");

        REQUIRE(summaryPopularWord.first["total_words"] == 106);
        REQUIRE(summaryPopularWord.first["highest_frequency"] == 16);
        REQUIRE(summaryPopularWord.first["unique_words"] == 16);

        REQUIRE(kCommonWords.size() == 3);
        REQUIRE(kCommonWords["the"] == 16);
        REQUIRE(kCommonWords["sat"] == 8);
        REQUIRE(kCommonWords["mat"] == 8);

        REQUIRE(wordCounts["jack"] == 5);
        REQUIRE(wordCounts["play"] == 5);
        REQUIRE(wordCounts["the"] == 16);
        REQUIRE(wordCounts["cat"] == 8);
    }

    SECTION("Complicated text file that includes punctuation and non-word characters")
    {
        std::string file4 = "../src/tests/test_files/test5.txt";

        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(file4);
        auto summaryPopularWord = getSummaryAndMostPopularWord(wordCounts);
        auto kCommonWords = CounterHelpers::getTopKWords(wordCounts, 4);
        auto longest_shortest = CounterHelpers::get_longest_shortest_words(wordCounts);

        REQUIRE(summaryPopularWord.second == "a");

        REQUIRE(longest_shortest.front() == "dragons");
        REQUIRE(longest_shortest.back() == "4");

        REQUIRE(summaryPopularWord.first["total_words"] == 38);
        REQUIRE(summaryPopularWord.first["highest_frequency"] == 3);
        REQUIRE(summaryPopularWord.first["unique_words"] == 33);

        REQUIRE(kCommonWords.size() == 4);
        REQUIRE(kCommonWords["the"] == 3);
        REQUIRE(kCommonWords["of"] == 2);
        REQUIRE(kCommonWords["a"] == 3);
        REQUIRE(kCommonWords["dream"] == 1);

        REQUIRE(wordCounts["dragons"] == 1);
        REQUIRE(wordCounts["swords"] == 1);
        REQUIRE(wordCounts["spring"] == 1);
        REQUIRE(wordCounts["dance"] == 1);
    }
}
