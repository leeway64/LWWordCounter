# Deserializes either a BSON or UBJSON object

import ubjson
import bson

z = []
with open(r"../bin/serialized_file_summary.ubj", "rb") as file:
    z = file.read()

decoded = ubjson.loadb(z)
print(decoded["highest_frequency"])
