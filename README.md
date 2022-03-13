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
  "input_file_name": "..\\src\\tests\\test_text_files\\moby_dick.txt",
  "minimum_occurrences": 800,
  "serialization_format": "BSON"
}
```

Then after running the program, the console output will be:

```
Text file selected: ..\src\tests\test_text_files\moby_dick.txt
Minimum number of occurrences for printing: 800

File summary:
    Most popular word: the
    215864      total_words
    14512       highest_frequency
    31820       unique_words

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

To run the C++ unit tests, 

To run the Python unit tests, run `pytest` in the terminal in the root directory of this repository.


## Third-Party Tools
- [CMake](https://cmake.org/) (BSD-3-Clause): Build system generator.

- [Conan](https://conan.io/) (MIT License): Package manager.

- [Catch2](https://github.com/catchorg/Catch2/tree/v2.x) (MIT License): Unit testing framework.

- [json](https://github.com/nlohmann/json) (MIT License): json is a C++ JSON library.

- [{fmt}](https://github.com/fmtlib/fmt) (MIT License): Formatting library.

- [json-schema-validator](https://github.com/pboettch/json-schema-validator) (MIT License): library for JSON schema validation.
