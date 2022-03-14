#include <string>
#include <catch2/catch.hpp>

#include "../WordCounter-helpers.hpp"


std::pair<std::unordered_map<std::string, int>, std::string> getTestInfo(const std::string& fileName)
{
    std::pair<std::unordered_map<std::string, int>, std::string> result;

    std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(fileName);
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

        auto testInfo = getTestInfo(file1);

        REQUIRE(testInfo.first["unique_words"] == 0);
        REQUIRE(testInfo.first["total_words"] == 0);
        REQUIRE(testInfo.first["highest_frequency"] == 0);
        REQUIRE(testInfo.second == "");
    }

    SECTION("File with 1 word")
    {
        std::string file2 = "../src/tests/test_files/test2.txt";

        auto testInfo = getTestInfo(file2);

        REQUIRE(testInfo.first["unique_words"] == 1);
        REQUIRE(testInfo.first["total_words"] == 1);
        REQUIRE(testInfo.first["highest_frequency"] == 1);
        REQUIRE(testInfo.second == "hello");
    }

    SECTION("File with 4 words")
    {
        std::string file3 = "../src/tests/test_files/test3.txt";

        auto testInfo = getTestInfo(file3);

        REQUIRE(testInfo.first["unique_words"] == 4);
        REQUIRE(testInfo.first["total_words"] == 10);
        REQUIRE(testInfo.first["highest_frequency"] == 4);
        REQUIRE(testInfo.second == "a");
    }

    SECTION("More complicated text file")
    {
        std::string file4 = "../src/tests/test_files/test4.txt";

        auto testInfo = getTestInfo(file4);

        REQUIRE(testInfo.first["unique_words"] == 16);
        REQUIRE(testInfo.first["total_words"] == 106);
        REQUIRE(testInfo.first["highest_frequency"] == 16);
        REQUIRE(testInfo.second == "the");
    }
}
