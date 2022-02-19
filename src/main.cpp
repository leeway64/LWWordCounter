#include <iostream>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "WordCounter-helper.hpp"

using nlohmann::json_schema::json_validator;

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
            //std::cout << "Validation succeeded\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Validation failed: " << e.what() << std::endl;
            return 1;
        }
        std::string name = input_file_json["input_file_name"];
        int minOccurs = input_file_json["minimum_occurrences"];
        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(name);


        std::unordered_map<std::string, int> fileSummary;
        fileSummary["unique_words"] = wordCounts.size();
        fileSummary["total_words"] = CounterHelpers::getTotalWords(wordCounts);

        std::pair<std::string, int> mostPopularStats = CounterHelpers::getMostPopularStats(wordCounts);

        fileSummary["highest_frequency"] = mostPopularStats.second;

        std::cout << "Text file selected: " << name << std::endl;
        std::cout << "Minimum number of occurrences for printing: " << minOccurs << std::endl;
        std::cout << std::endl;

        std::cout << "Most popular word: " << mostPopularStats.first << std::endl;

        for(auto keyValue : wordCounts) {
            if(keyValue.second >= minOccurs)
            {
                std::cout << keyValue.second << "\t" << keyValue.first << std::endl;
            }
        }
        std::cout << std::endl;

        for(auto keyValue : fileSummary) {
            std::cout << keyValue.second << "\t" << keyValue.first << std::endl;
        }

        nlohmann::json fileSummaryJSON(fileSummary);

        std::string serialization_format = input_file_json["serialization_format"];

        std::vector<std::uint8_t> serializedData;
        std::ofstream output;
        if (serialization_format == "BSON")
        {
            serializedData = nlohmann::json::to_bson(fileSummaryJSON);
            output.open("serialized_file_summary.bson");
        } else if (serialization_format == "UBJSON")
        {
            serializedData = nlohmann::json::to_ubjson(fileSummaryJSON);
            output.open("serialized_file_summary.ubj");
        }
        else
        {
            return 1;
        }

        for (const auto& element : serializedData)
        {
            output << element;
        }

        output.close();

    }

	return 0;
}
