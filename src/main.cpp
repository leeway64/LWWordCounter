#include <iostream>
#include <filesystem>
#include <fstream>
#include <exception>

#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "WordCounter-helpers.hpp"

using nlohmann::json_schema::json_validator;

void successful_exit_message()
{
    std::cout << "\nFile has been analyzed and a summary has been serialized successfully" << std::endl;
}

int main()
{
    const std::string input_schema_name = "../schema/user_input_schema.json";
    const std::string input_file_name = "input_file.json";

    const std::filesystem::path input_file{ input_file_name };
    if (!std::filesystem::exists(input_file))
    {
        std::cout << "No input JSON file found" << std::endl;
        std::cout << "Creating a new JSON file" << std::endl;
        CounterHelpers::createInputJSON(input_file_name);
    }
    else
    {
        // Get the input JSON file
        nlohmann::json input_file_json;
        CounterHelpers::getJSON(input_file_name, input_file_json);

        // Get the schema for the input JSON file
        nlohmann::json input_schema_json;
        CounterHelpers::getJSON(input_schema_name, input_schema_json);


        json_validator validator;
        validator.set_root_schema(input_schema_json);
        try {
            validator.validate(input_file_json);
        }
        catch (const std::exception& e) {
            std::cerr << "Validation failed: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }


        const std::string input_text_file = input_file_json["input_file_name"];
        // Use JSON pointers to access values
        const int minOccurs = input_file_json["/statistics/minimum_occurrences"_json_pointer];
        const int kMostFrequent = input_file_json["/statistics/k_most_frequent_words"_json_pointer];
        const int word_length_to_find = input_file_json["/statistics/word_length_to_find"_json_pointer];

        // Get the frequency of each word in the text file. i.e., word x appears y times in the
        // file.
        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(input_text_file);


        std::unordered_map<std::string, std::string> fileSummary;
        fileSummary["unique_words"] = std::to_string(wordCounts.size());
        fileSummary["total_words"] = std::to_string(CounterHelpers::getTotalWords(wordCounts));


        const std::pair<std::string, int> mostPopularWord = CounterHelpers::getMostPopularWord(wordCounts);

        std::map<std::string, int> kMostFrequentWordsMap;
        try
        {
            kMostFrequentWordsMap = CounterHelpers::getTopKWords(wordCounts, kMostFrequent);
        }
        // In the JSON file, the user might have set k to be greater than the number of unique
        // words in the text file, or they might have set it to a negative integer.
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }

        fileSummary["highest_frequency"] = std::to_string(mostPopularWord.second);


        std::cout << "Text file selected: " << input_text_file << std::endl;
        std::cout << "Minimum number of occurrences for printing: " << minOccurs << std::endl;
        std::cout << std::endl;

        std::cout << "File summary:" << std::endl;
        std::cout << "    Most popular word: " << mostPopularWord.first << std::endl;

        for(auto keyValue : fileSummary) {
            std::cout << fmt::format("    {}\t{}", keyValue.first, keyValue.second) << std::endl;
        }

        std::cout << fmt::format("    Top {} words:", kMostFrequent) << std::endl;
        for (const auto& [key, value]: kMostFrequentWordsMap){
            std::cout << "\t" << fmt::format("{}\t{}", key, value) << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Word frequencies:" << std::endl;
        // Print out the word and the corresponding frequency, assuming the frequency is above the
        // minOccurs threshold.
        for(auto keyValue : wordCounts) {
            if(keyValue.second >= minOccurs)
            {
                std::cout << fmt::format("    {}\t{}", keyValue.second, keyValue.first) << std::endl;
            }
        }


        nlohmann::json fileSummaryJSON(fileSummary);
        std::string serialization_format = input_file_json["serialization_format"];
        std::vector<std::uint8_t> serializedData;

        // Get the name (without the extension) of the input text file.
        std::string output_file_name{std::filesystem::path(input_text_file).stem().string()};
        output_file_name += "_serialized_summary";
        std::ofstream output;
        // Serialize the file summary into either BSON or UBJSON.
        if (serialization_format == "BSON")
        {
            serializedData = nlohmann::json::to_bson(fileSummaryJSON);
            output_file_name += ".bson";
            output.open(output_file_name);
        } else if (serialization_format == "UBJSON")
        {
            serializedData = nlohmann::json::to_ubjson(fileSummaryJSON);
            output_file_name += ".ubj";
            output.open(output_file_name);
        }
        else
        {
            std::cerr << "\nSerialization format must be either BSON or UBJSON" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        // Send the binary data into the .bson or .ubj file.
        for (const auto& element : serializedData)
        {
            output << element;
        }
        std::cout << fmt::format("\nA summary of this text file has been serialized into {}", output_file_name) << std::endl;
        output.close();
    }

    // std::atexit runs the successful_exit_message function when the program terminates (AKA exits)
    std::atexit(successful_exit_message);
	std::exit(EXIT_SUCCESS);
}
