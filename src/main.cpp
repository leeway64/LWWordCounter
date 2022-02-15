#include <iostream>
#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>
#include <toml.hpp>

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

        std::ofstream output(input_file_name);
        // Write brackets so that the file can be correctly read as a JSON file
        output << "{\n}\n";
        output.close();
    }
    else
    {
        // Get the input JSON file
        std::ifstream input1(input_file_name);
        nlohmann::json input_file_json;
        input1 >> input_file_json;
        input1.close();

        // Get the schema for the input JSON file
        std::ifstream input2(input_schema_name);
        nlohmann::json input_schema_json;
        input2 >> input_schema_json;
        input2.close();

        json_validator validator;
        validator.set_root_schema(input_schema_json);
        try {
            validator.validate(input_file_json);
            //std::cout << "Validation succeeded\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Validation failed, here is why: " << e.what() << std::endl;
        }
    }

    const toml::value summary_data;

	return 0;
}
