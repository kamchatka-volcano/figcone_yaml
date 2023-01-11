#include "assert_exception.h"
#include <figcone_yaml/parser.h>
#include <gtest/gtest.h>
#include <sstream>

namespace test_paramlistparser {

auto parseParam(const std::string& str)
{
    auto input = std::stringstream{str};
    auto parser = figcone::yaml::Parser{};
    return parser.parse(input);
}

TEST(TestParamListParser, Basic)
{
    auto result = parseParam(R"(
testIntList : [1, 2, 3]
)");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

TEST(TestParamListParser, BasicWithoutMacro)
{
    auto result = parseParam(R"(
testIntList : [1, 2, 3]
)");
    auto& tree = result.asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("testIntList").valueList(), (std::vector<std::string>{"1", "2", "3"}));
}

} //namespace test_paramlistparser
