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
            std::cerr << "Validation failed, here is why: " << e.what() << std::endl;
        }
        std::string name = input_file_json["input_file_name"];
        std::unordered_map<std::string, int> wordCounts = CounterHelpers::getWordCounts(name);

        for(auto keyValue : wordCounts) {
            std::cout << keyValue.second << "\t" << keyValue.first << std::endl;
        }

        std::unordered_map<std::string, int> fileSummary;
        fileSummary["unique_words_number"] = wordCounts.size();
        fileSummary["total_words_number"] = CounterHelpers::getTotalWords(wordCounts);

        int total_words = 0;


//        fileSummary

        std::vector<std::uint8_t> v_ubjson = nlohmann::json ::to_ubjson(input_file_json);

    }

	return 0;
}
