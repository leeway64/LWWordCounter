# LWWordCounter

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/leeway64/LWWordCounter)


LWWordCounter is an application that displays the frequency of words from a text file. It also
summarizes several statistics for that file, such as the most popular word and the total number of
words. Finally, LWWordCounter serializes this summary into either [UBJSON](https://ubjson.org/) or
[BSON](https://bsonspec.org/).

The `Deserializer` Python class is provided to deserialize this summary data.

## Installation

```shell
git clone https://github.com/leeway64/LWWordCounter.git
cd LWWordCounter
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B ./cmake-build-release
cmake --build ./cmake-build-release --target LWWordCounter
```


| :memo: Note                                                                                                                                                                            |
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| if the CMake output says that a certain package is `locked by another concurrent conan process, wait...`, then run `conan remove -f <package_name>/<package_version>` in the terminal. |


## Example

Input is entered using a JSON file. Let's assume that the JSON file looks like this:

```json
{
    "input_file_name": "../src/tests/test_files/moby_dick.txt",
    "statistics":
    {
        "minimum_occurrences": 900,
        "k_most_frequent_words": 5,
        "word_length_to_find": 4
    },
    "serialization_format": "UBJSON"
}
```

This version of Moby Dick (by Herman Melville) was found on
[Project Gutenberg](https://www.gutenberg.org/ebooks/2701).

This JSON file is provided as an example in the [`bin`](bin) folder.

Next, run LWWordCounter:

```shell
cd bin
LWWordCounter
```

After running the program, the console output will be:

```text
Text file selected: ../src/tests/test_files/moby_dick.txt

File summary:
    Most popular word: the

    Longest word: uninterpenetratingly
    Shortest word: 0

    Number of words with length 4:      1359

    highest_frequency   14727
    unique_words        17342
    total_words 222673

    Top 5 words:
        a       4805
        and     6515
        of      6747
        the     14727
        to      4709

Minimum number of occurrences for printing: 900
Word frequencies:
    14727       the
    1069        him
    1770        with
    1644        for
    1545        all
    1066        so
    1822        s
    3100        that
    2532        his
    1064        be
    1443        this
    1333        at
    969 you
    6747        of
    6515        and
    1747        is
    4245        in
    1244        whale
    1105        from
    4805        a
    4709        to
    1752        as
    1180        not
    1822        but
    1232        by
    925 one
    2537        it
    1900        he
    2127        i
    1647        was
    1073        on

A summary of this text file has been serialized into moby_dick_serialized_summary.ubj

File has been analyzed and a summary has been serialized successfully
```

A summary of the file will also be serialized; the serialized file will be called
`[input text file]_serialized_summary.[serialization format]`.


## Running Tests
### C++ Tests
To run the C++ unit tests, make sure that the `BuildTests` option in [`CMakeLists.txt`](CMakeLists.txt)
is set to `ON`. 

Then, run the following commands:

```shell
cmake --build ./cmake-build-release --target WordCounter_Tests
bin/WordCounter_Tests
```


### Python Tests
Run the following commands in the root directory of this project.

#### Linux
```sh
    python3 -m venv .venv
    source .venv/bin/activate
    pip install -r requirements.txt
    pytest
```


#### Windows
```sh
    py -3 -m venv .venv
    .venv/Scripts/activate
    pip install -r requirements.txt
    pytest
```


## Third-Party Tools
- [CMake](https://cmake.org/) (BSD-3-Clause): Build system generator.
- [Conan](https://conan.io/) (MIT License): Package manager.
- [Catch2](https://github.com/catchorg/Catch2/tree/v2.x) (MIT License): Unit testing framework.
- [json](https://github.com/nlohmann/json) (MIT License): json is a C++ JSON library.
- [{fmt}](https://github.com/fmtlib/fmt) (MIT License): Formatting library.
- [json-schema-validator](https://github.com/pboettch/json-schema-validator) (MIT License): library for JSON schema validation.
