cmake_minimum_required (VERSION 3.8)

project (
	"LWWordCounter"
	LANGUAGES CXX
	VERSION "0.0.1"
	)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")

# Put the exe into the bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# conan_cmake_configures accepts the same arguments as conanfile.txt
conan_cmake_configure(REQUIRES	catch2/2.13.8
								nlohmann_json/3.10.5
								json-schema-validator/2.1.0
                                fmt/8.1.1
		    					ctre/3.5
					  GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

# I can pass conan_cmake_install all the arguments that conan install supports
conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

find_package(Catch2)
find_package(nlohmann_json)
find_package(nlohmann_json_schema_validator)
find_package(fmt)

add_executable ("LWWordCounter"
				"src/main.cpp"
                "src/WordCounter-helpers.hpp"
                "src/WordCounter-helpers.cpp")

target_link_libraries(
        "LWWordCounter"
        PRIVATE
        Catch2::Catch2
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator::nlohmann_json_schema_validator
        fmt::fmt
)



option(BuildTests "Build the unit tests" ON)

if (BuildTests)
    add_executable("WordCounter_Tests"
                   "src/WordCounter-helpers.hpp"
                   "src/WordCounter-helpers.cpp"
                   "src/tests/catch2_main.cpp"
                   "src/tests/test_suite.cpp")

    target_link_libraries(
            "WordCounter_Tests"
            PRIVATE
            Catch2::Catch2
            nlohmann_json::nlohmann_json
            nlohmann_json_schema_validator::nlohmann_json_schema_validator
            fmt::fmt
    )
endif()
