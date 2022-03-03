import ubjson
import bson


# Deserializes either a BSON or UBJSON object
class Deserializer:
    def __init__(self, serialized_file_name, serialization_format):
        self._serialized_file_name = serialized_file_name
        self._deserialized_data = None
        self._serialization_format = serialization_format

    @property
    def serialized_file_name(self):
        return self._serialized_file_name

    @serialized_file_name.setter
    def serialized_file_name(self, new_file_name):
        self._serialized_file_name = new_file_name

    @property
    def serialization_format(self):
        return self._serialization_format

    @serialization_format.setter
    def serialization_format(self, new_format_name):
        self._serialization_format = new_format_name

    @property
    def deserialized_data(self):
        # Lazily load the deserialized data
        if not self._deserialized_data:
            self._deserialized_data = self.__deserialize()

        return self._deserialized_data

    def __deserialize(self):
        decoded = None
        with open(self._serialized_file_name, "rb") as file:
            encoded = file.read()
        if self._serialization_format == "UBJSON":
            decoded = ubjson.loadb(encoded)
        elif self._serialization_format == "BSON":
            decoded = bson.loads(encoded)
        else:
            print("Unknown serialization format. Enter either \"UBJSON\" or \"BSON\"")
        return decoded
