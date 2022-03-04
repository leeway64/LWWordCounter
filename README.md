# LWWordCounter

LWWordCounter is an application that displays the frequency of words from a text file.


## Installation

The simplest way to use LWWordCounter is to clone this repository, then build using CMake.


| :memo: Note                                                                                                                                                                            |
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| if the CMake output says that a certain package is `locked by another concurrent conan process, wait...`, then run `conan remove -f <package_name>/<package_version>` in the terminal. |


Note: if the CMake output says that a certain package is `locked by another concurrent conan
process, wait...`, then run `conan remove -f <package_name>/<package_version>` in the terminal.


## Example

Input is entered using a JSON file. Let's assume that the JSON file looks like this:

```
{
  "input_file_name": "../src/tests/test_files/test4.txt",
  "minimum_occurrences": 0,
  "serialization_format": "UBJSON"
}
```

Then after running the program, the console output will be:

```
Text file selected: ../src/tests/test_text_files/test4.txt
Minimum number of occurrences for printing: 0

File summary:
    Most popular word: the
    106 total_words
    16  highest_frequency
    16  unique_words

Word frequencies:
    8   mat
    8   on
    5   all
    5   work
    5   no
    5   dull
    8   sat
    5   play
    5   a
    5   makes
    5   jack
    5   boy
    16  the
    5   and
    8   fat
    8   cat
```

A summary of the file will also be serialized; the serialized file will be called
`[input text file]_serialized_summary.[serialization format]`.


## Third-Party Tools

- CMake: Build system generator.
- Conan: Package manager for C/C++.
- Catch2: 
- nlohmann_json: 
- 
