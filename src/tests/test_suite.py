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
        assert data["total_words"] == 0
        assert data["highest_frequency"] == 0
        assert data["unique_words"] == 0

        d2.serialized_file_name = "src/tests/test_files/test2_serialized_summary.ubj"
        data = d2.deserialized_data
        assert data["total_words"] == 1
        assert data["highest_frequency"] == 1
        assert data["unique_words"] == 1

        # d2.serialized_file_name = "src/tests/test_files/test3_serialized_summary.ubj"
        # data = d2.deserialized_data
        # assert data["total_words"] == 10
        # assert data["highest_frequency"] == 4
        # assert data["unique_words"] == 4

        # d2.serialized_file_name = "src/tests/test_files/test4_serialized_summary.ubj"
        # data = d2.deserialized_data
        # assert data["total_words"] == 106
        # assert data["highest_frequency"] == 16
        # assert data["unique_words"] == 16

    def test_BSON_deserialization(self):
        d3 = Deserializer("src/tests/test_files/test1_serialized_summary.bson", "BSON")
        data = d3.deserialized_data
        assert data["total_words"] == 0
        assert data["highest_frequency"] == 0
        assert data["unique_words"] == 0

        d3.serialized_file_name = "src/tests/test_files/test2_serialized_summary.bson"
        data = d3.deserialized_data
        assert data["total_words"] == 1
        assert data["highest_frequency"] == 1
        assert data["unique_words"] == 1

        # d3.serialized_file_name = "src/tests/test_files/test3_serialized_summary.bson"
        # data = d3.deserialized_data
        # assert data["total_words"] == 10
        # assert data["highest_frequency"] == 4
        # assert data["unique_words"] == 4

        d3.serialized_file_name = "src/tests/test_files/test4_serialized_summary.bson"
        data = d3.deserialized_data
        assert data["total_words"] == 106
        assert data["highest_frequency"] == 16
        assert data["unique_words"] == 16
