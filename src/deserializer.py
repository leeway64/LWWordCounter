# Deserializes either a BSON or UBJSON object

import ubjson
import bson

file_name = input("Enter file name: ")
serial_format = input("Enter serialization format: ")

if serial_format == "UBJSON":
    with open(r"../bin/serialized_file_summary.ubj", "rb") as file:
        encoded = file.read()

    decoded = ubjson.loadb(encoded)
elif serial_format == "BSON":
    with open(r"../bin/serialized_file_summary.bson", "rb") as file:
        encoded = file.read()

    decoded = bson.loads(encoded)
    print(decoded)
else:
    print("Unknown serialization format. Enter either \"UBJSON\" or \"BSON\"")
