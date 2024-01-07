#include "assert_exception.h"
#include <figcone_yaml/parser.h>
#include <gtest/gtest.h>
#include <sstream>

namespace test_paramparser {

auto parseParam(const std::string& str)
{
    auto input = std::stringstream{str};
    auto parser = figcone::yaml::Parser{};
    return parser.parse(input);
}

TEST(TestParam, Basic)
{
    auto result = parseParam(R"(
test : 1
)");
    auto& tree = result.root().asList().at(0).asItem();

    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("test").value(), "1");
}

TEST(TestParam, EmptyStringParam)
{
    auto result = parseParam(R"(
test : ""
)");
    auto& tree = result.root().asList().at(0).asItem();

    ASSERT_EQ(tree.paramsCount(), 1);
    EXPECT_EQ(tree.param("test").value(), "");
}

} //namespace test_paramparser
