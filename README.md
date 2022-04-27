# LWWordCounter

LWWordCounter is an application that displays the frequency of words from a text file. It also
summarizes several statistics for that file, such as the most popular word and the total number of
words. Finally, LWWordCounter serializes this summary into either [UBJSON](https://ubjson.org/) or
[BSON](https://bsonspec.org/).

The `Deserializer` Python class is provided to deserialize this summary data.

## Installation

The simplest way to use LWWordCounter is to clone this repository, then build using CMake; I used
[CLion](https://www.jetbrains.com/clion/) as the primary development environment.


| :memo: Note                                                                                                                                                                            |
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| if the CMake output says that a certain package is `locked by another concurrent conan process, wait...`, then run `conan remove -f <package_name>/<package_version>` in the terminal. |


## Example

Input is entered using a JSON file. Let's assume that the JSON file looks like this:

```json
{
  "input_file_name": "../src/tests/test_files/moby_dick.txt",
  "minimum_occurrences": 800,
    "k_most_frequent_words": 5,
  "serialization_format": "UBJSON"
}
```

This JSON file is provided as an example in the `bin` folder.

After running the program, the console output will be:

```text
Text file selected: ../src/tests/test_files/moby_dick.txt
Minimum number of occurrences for printing: 800

File summary:
    Most popular word: the
    total_words 215864
    highest_frequency   14512
    unique_words        31820
    Top 5 words:
        a       4663
        and     6322
        of      6683
        the     14512
        to      4599

Word frequencies:
    14512       the
    1555        for
    1714        as
    4599        to
    1671        but
    1100        from
    961 on
    1750        with
    4663        a
    1279        this
    1578        was
    1777        it
    4126        in
    1723        i
    1683        he
    843 you
    6683        of
    1093        not
    878 so
    6322        and
    1005        be
    2748        that
    1360        all
    2485        his
    1177        by
    1310        at
    1601        is
```

A summary of the file will also be serialized; the serialized file will be called
`[input text file]_serialized_summary.[serialization format]`.


## Running Tests

### C++ Tests

To run the C++ unit tests, make sure that the `BuildTests` option in `CMakeLists.txt` is set to
`ON`. Then, run the `WordCounter_tests` executable.


### Python Tests

In the root directory of this project, if using Linux, run:

```
    $ python3 -m venv .venv
    $ source .venv/bin/activate
    $ pip install -r requirements.txt
    $ pytest
```

If using Windows, run:

```
    $ py -3 -m venv .venv
    $ .venv/Scripts/activate
    $ pip install -r requirements.txt
    $ pytest
```

## Third-Party Tools
- [CMake](https://cmake.org/) (BSD-3-Clause): Build system generator.
- [Conan](https://conan.io/) (MIT License): Package manager.
- [Catch2](https://github.com/catchorg/Catch2/tree/v2.x) (MIT License): Unit testing framework.
- [json](https://github.com/nlohmann/json) (MIT License): json is a C++ JSON library.
- [{fmt}](https://github.com/fmtlib/fmt) (MIT License): Formatting library.
- [json-schema-validator](https://github.com/pboettch/json-schema-validator) (MIT License): library for JSON schema validation.
