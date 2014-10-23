/*
* Arduino JSON library
* Benoit Blanchon 2014 - MIT License
*/

#include <gtest/gtest.h>
#include <ArduinoJson/JsonArray.hpp>
#include <ArduinoJson/JsonObject.hpp>
#include <ArduinoJson/StaticJsonBuffer.hpp>

using namespace ArduinoJson;

class JsonArray_PrintTo_Tests : public testing::Test {
 protected:
  JsonArray array;
  StaticJsonBuffer<3> json;

  virtual void SetUp() { array = json.createArray(); }

  void outputMustBe(const char *expected) {
    size_t n = array.printTo(buffer, sizeof(buffer));
    EXPECT_STREQ(expected, buffer);
    EXPECT_EQ(strlen(expected), n);
  }

 private:
  char buffer[256];
};

TEST_F(JsonArray_PrintTo_Tests, Empty) { outputMustBe("[]"); }

TEST_F(JsonArray_PrintTo_Tests, Null) {
  array.add((char *)0);

  outputMustBe("[null]");
}

TEST_F(JsonArray_PrintTo_Tests, OneString) {
  array.add("hello");

  outputMustBe("[\"hello\"]");
}

TEST_F(JsonArray_PrintTo_Tests, TwoStrings) {
  array.add("hello");
  array.add("world");

  outputMustBe("[\"hello\",\"world\"]");
}

TEST_F(JsonArray_PrintTo_Tests, OneStringOverCapacity) {
  array.add("hello");
  array.add("world");
  array.add("lost");

  outputMustBe("[\"hello\",\"world\"]");
}

TEST_F(JsonArray_PrintTo_Tests, OneDoubleDefaultDigits) {
  array.add(3.14159265358979323846);
  outputMustBe("[3.14]");
}

TEST_F(JsonArray_PrintTo_Tests, OneDoubleFourDigits) {
  array.add(3.14159265358979323846, 4);
  outputMustBe("[3.1416]");
}

TEST_F(JsonArray_PrintTo_Tests, OneInteger) {
  array.add(1);

  outputMustBe("[1]");
}

TEST_F(JsonArray_PrintTo_Tests, TwoIntegers) {
  array.add(1);
  array.add(2);

  outputMustBe("[1,2]");
}

TEST_F(JsonArray_PrintTo_Tests, OneIntegerOverCapacity) {
  array.add(1);
  array.add(2);
  array.add(3);

  outputMustBe("[1,2]");
}

TEST_F(JsonArray_PrintTo_Tests, OneTrue) {
  array.add(true);

  outputMustBe("[true]");
}

TEST_F(JsonArray_PrintTo_Tests, OneFalse) {
  array.add(false);

  outputMustBe("[false]");
}

TEST_F(JsonArray_PrintTo_Tests, TwoBooleans) {
  array.add(false);
  array.add(true);

  outputMustBe("[false,true]");
}

TEST_F(JsonArray_PrintTo_Tests, OneBooleanOverCapacity) {
  array.add(false);
  array.add(true);
  array.add(false);

  outputMustBe("[false,true]");
}

TEST_F(JsonArray_PrintTo_Tests, OneEmptyNestedArray) {
  array.createNestedArray();

  outputMustBe("[[]]");
}

TEST_F(JsonArray_PrintTo_Tests, OneEmptyNestedHash) {
  array.createNestedObject();

  outputMustBe("[{}]");
}