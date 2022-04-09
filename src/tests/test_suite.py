from src.Deserializer import Deserializer


class TestSuite:
    def test_names(self):
        d1 = Deserializer("test_files/test1.txt", "UBJSON")
        assert d1.serialized_file_name == "test_files/test1.txt"

        d1.serialized_file_name = "test_files/test2.txt"
        assert d1.serialized_file_name == "test_files/test2.txt"

        assert d1.serialization_format == "UBJSON"
        d1.serialization_format = "BSON"
        assert d1.serialization_format == "BSON"

    def test_UBJSON_deserialization(self):
        d2 = Deserializer("src/tests/test_files/test1_serialized_summary.ubj", "UBJSON")
        data = d2.deserialized_data
        assert data["total_words"] == str(0)
        assert data["highest_frequency"] == str(0)
        assert data["unique_words"] == str(0)

        d2.serialized_file_name = "src/tests/test_files/test2_serialized_summary.ubj"
        data = d2.deserialized_data
        assert data["total_words"] == str(1)
        assert data["highest_frequency"] == str(1)
        assert data["unique_words"] == str(1)

        d2.serialized_file_name = "src/tests/test_files/test3_serialized_summary.ubj"
        data = d2.deserialized_data
        assert data["total_words"] == str(10)
        assert data["highest_frequency"] == str(4)
        assert data["unique_words"] == str(4)

        d2.serialized_file_name = "src/tests/test_files/test4_serialized_summary.ubj"
        data = d2.deserialized_data
        assert data["total_words"] == str(106)
        assert data["highest_frequency"] == str(16)
        assert data["unique_words"] == str(16)

        # d2.serialized_file_name = "src/tests/test_files/test5_serialized_summary.ubj"
        # data = d2.deserialized_data

    def test_BSON_deserialization(self):
        d3 = Deserializer("src/tests/test_files/test1_serialized_summary.bson", "BSON")
        data = d3.deserialized_data
        assert data["total_words"] == str(0)
        assert data["highest_frequency"] == str(0)
        assert data["unique_words"] == str(0)

        d3.serialized_file_name = "src/tests/test_files/test2_serialized_summary.bson"
        data = d3.deserialized_data
        assert data["total_words"] == str(1)
        assert data["highest_frequency"] == str(1)
        assert data["unique_words"] == str(1)

        d3.serialized_file_name = "src/tests/test_files/test3_serialized_summary.bson"
        data = d3.deserialized_data
        assert data["total_words"] == str(10)
        assert data["highest_frequency"] == str(4)
        assert data["unique_words"] == str(4)

        d3.serialized_file_name = "src/tests/test_files/test4_serialized_summary.bson"
        data = d3.deserialized_data
        assert data["total_words"] == str(106)
        assert data["highest_frequency"] == str(16)
        assert data["unique_words"] == str(16)

        # d3.serialized_file_name = "src/tests/test_files/test5_serialized_summary.bson"
        # data = d3.deserialized_data

