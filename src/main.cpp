#include <iostream>


int main()
{
    const std::string timers_file_name = "list_of_timers.json";

    const std::filesystem::path timers_file{ timers_file_name };
    if (!std::filesystem::exists(timers_file))
    {
        std::ofstream output(timers_file_name);
        // Write brackets so that the file can be correctly read as a JSON file
        output << "{\n}\n";
        output.close();
    }
	std::cout << "hello" << std::endl;
	return 0;
}