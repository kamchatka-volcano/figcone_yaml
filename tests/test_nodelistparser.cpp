#include "assert_exception.h"
#include <figcone_tree/errors.h>
#include <figcone_yaml/parser.h>
#include <gtest/gtest.h>

namespace test_nodelistparser {

auto parse(const std::string& str)
{
    auto input = std::stringstream{str};
    auto parser = figcone::yaml::Parser{};
    return parser.parse(input);
}

TEST(TestNodeListParser, Basic)
{
    auto result = parse(R"(
testStr: Hello
testNodes:
 -
   testInt: 3
 -
   testInt: 2
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testStr"));
    ASSERT_TRUE(tree.param("testStr").isItem());
    EXPECT_EQ(tree.param("testStr").value(), "Hello");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testNodes"));
    ASSERT_TRUE(tree.node("testNodes").isList());
    auto& testNodes = tree.node("testNodes").asList();
    ASSERT_EQ(testNodes.size(), 2);
    {
        auto& nodeData = testNodes.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "3");
    }
    {
        auto& nodeData = testNodes.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "2");
    }
}

TEST(TestNodeListParser, BasicJSON)
{
    auto result = parse(R"({
"testStr": "Hello",
"testNodes":[
 {
   "testInt": 3
},
 {
   "testInt": 2
}]
} )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testStr"));
    ASSERT_TRUE(tree.param("testStr").isItem());
    EXPECT_EQ(tree.param("testStr").value(), "Hello");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testNodes"));
    ASSERT_TRUE(tree.node("testNodes").isList());
    auto& testNodes = tree.node("testNodes").asList();
    ASSERT_EQ(testNodes.size(), 2);
    {
        auto& nodeData = testNodes.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "3");
    }
    {
        auto& nodeData = testNodes.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "2");
    }
}

TEST(TestNodeListParser, BasicOtherOrder)
{
    auto result = parse(R"(
        testNodes:
         -
          testInt: 3
         -
          testInt: 2
        testStr: Hello
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testStr"));
    EXPECT_EQ(tree.param("testStr").value(), "Hello");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testNodes"));
    auto& testNodes = tree.node("testNodes").asList();
    ASSERT_EQ(testNodes.size(), 2);
    {
        auto& nodeData = testNodes.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_EQ(nodeData.hasParam("testInt"), 1);
        EXPECT_EQ(nodeData.param("testInt").value(), "3");
    }
    {
        auto& nodeData = testNodes.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_EQ(nodeData.hasParam("testInt"), 1);
        EXPECT_EQ(nodeData.param("testInt").value(), "2");
    }
}

TEST(TestNodeListParser, BasicOtherOrderJSON)
{
    auto result = parse(R"(
    {
        "testNodes": [
           { "testInt" : "3"},
           { "testInt" : "2"}
        ],
        "testStr": "Hello"
    }
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testStr"));
    EXPECT_EQ(tree.param("testStr").value(), "Hello");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testNodes"));
    auto& testNodes = tree.node("testNodes").asList();
    ASSERT_EQ(testNodes.size(), 2);
    {
        auto& nodeData = testNodes.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_EQ(nodeData.hasParam("testInt"), 1);
        EXPECT_EQ(nodeData.param("testInt").value(), "3");
    }
    {
        auto& nodeData = testNodes.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_EQ(nodeData.hasParam("testInt"), 1);
        EXPECT_EQ(nodeData.param("testInt").value(), "2");
    }
}

TEST(TestNodeListParser, Nested)
{
    auto result = parse(R"(
    testCfg:
       testStr: Hello
       testNodes:
        -
          testInt: 3
        -
          testInt: 2
    testDouble: 0.5
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testDouble"));
    ASSERT_TRUE(tree.param("testDouble").isItem());
    EXPECT_EQ(tree.param("testDouble").value(), "0.5");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testCfg"));
    auto& testCfg = tree.node("testCfg").asItem();
    ASSERT_EQ(testCfg.paramsCount(), 1);
    ASSERT_TRUE(testCfg.hasParam("testStr"));
    ASSERT_TRUE(testCfg.param("testStr").isItem());
    EXPECT_EQ(testCfg.param("testStr").value(), "Hello");
    ASSERT_EQ(testCfg.nodesCount(), 1);
    ASSERT_TRUE(testCfg.hasNode("testNodes"));
    auto& testNodes = testCfg.node("testNodes").asList();
    ASSERT_EQ(testNodes.size(), 2);
    {
        auto& nodeData = testNodes.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "3");
    }
    {
        auto& nodeData = testNodes.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "2");
    }
}

TEST(TestNodeListParser, NestedJSON)
{
    auto result = parse(R"(
   {
        "testCfg":{
            "testStr" : "Hello",
            "testNodes":[
                {"testInt": "3"},
                {"testInt": "2"}
            ]
        },
        "testDouble": "0.5"
 }
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testDouble"));
    ASSERT_TRUE(tree.param("testDouble").isItem());
    EXPECT_EQ(tree.param("testDouble").value(), "0.5");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testCfg"));
    auto& testCfg = tree.node("testCfg").asItem();
    ASSERT_EQ(testCfg.paramsCount(), 1);
    ASSERT_TRUE(testCfg.hasParam("testStr"));
    ASSERT_TRUE(testCfg.param("testStr").isItem());
    EXPECT_EQ(testCfg.param("testStr").value(), "Hello");
    ASSERT_EQ(testCfg.nodesCount(), 1);
    ASSERT_TRUE(testCfg.hasNode("testNodes"));
    auto& testNodes = testCfg.node("testNodes").asList();
    ASSERT_EQ(testNodes.size(), 2);
    {
        auto& nodeData = testNodes.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "3");
    }
    {
        auto& nodeData = testNodes.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testInt"));
        ASSERT_TRUE(nodeData.param("testInt").isItem());
        EXPECT_EQ(nodeData.param("testInt").value(), "2");
    }
}


TEST(TestNodeListParser, NestedCfgList)
{
    auto result = parse(R"(
        testList:
         -
           testStr: Hello
           testNodes:
            -
              testInt: 3
            -
              testInt: 33
         -
           testNodes:
            -
              testInt: 5
           testStr: World
        testStr: "Hello"
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testStr"));
    EXPECT_EQ(tree.param("testStr").value(), "Hello");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testList"));
    ASSERT_TRUE(tree.node("testList").isList());
    auto& testList = tree.node("testList").asList();
    ASSERT_EQ(testList.size(), 2);
    {
        auto& nodeData = testList.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_EQ(nodeData.hasParam("testStr"), 1);
        EXPECT_EQ(nodeData.param("testStr").value(), "Hello");
        ASSERT_EQ(nodeData.nodesCount(), 1);
        ASSERT_EQ(nodeData.hasNode("testNodes"), 1);
        auto& testNodes = nodeData.node("testNodes").asList();
        ASSERT_EQ(testNodes.size(), 2);
        {
            auto& listNodeData = testNodes.at(0).asItem();
            ASSERT_EQ(listNodeData.paramsCount(), 1);
            ASSERT_EQ(listNodeData.hasParam("testInt"), 1);
            ASSERT_TRUE(listNodeData.param("testInt").isItem());
            EXPECT_EQ(listNodeData.param("testInt").value(), "3");
        }
        {
            auto& listNodeData = testNodes.at(1).asItem();
            ASSERT_EQ(listNodeData.paramsCount(), 1);
            ASSERT_EQ(listNodeData.hasParam("testInt"), 1);
            ASSERT_TRUE(listNodeData.param("testInt").isItem());
            EXPECT_EQ(listNodeData.param("testInt").value(), "33");
        }
    }
    {
        auto& nodeData = testList.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testStr"));
        ASSERT_TRUE(nodeData.param("testStr").isItem());
        EXPECT_EQ(nodeData.param("testStr").value(), "World");
        ASSERT_EQ(nodeData.nodesCount(), 1);
        ASSERT_TRUE(nodeData.hasNode("testNodes"));
        auto& testNodes = nodeData.node("testNodes").asList();
        ASSERT_EQ(testNodes.size(), 1);
        {
            auto& listNodeData = testNodes.at(0).asItem();
            ASSERT_EQ(listNodeData.paramsCount(), 1);
            ASSERT_TRUE(listNodeData.hasParam("testInt"));
            EXPECT_EQ(listNodeData.param("testInt").value(), "5");
        }
    }
}

TEST(TestNodeListParser, NestedCfgListJSON)
{
    auto result = parse(R"(
    {
        "testList":[
        {
            "testStr": "Hello",
            "testNodes" :[
                {"testInt": "3"},
                {"testInt": "33"}
            ]
        },
        {
            "testNodes":[
                {"testInt": "5"}
            ],
            "testStr": "World"
        }
        ],
        "testStr" : "Hello"
    }
    )");

    auto& tree = result.root().asList().at(0).asItem();
    ASSERT_EQ(tree.paramsCount(), 1);
    ASSERT_TRUE(tree.hasParam("testStr"));
    EXPECT_EQ(tree.param("testStr").value(), "Hello");
    ASSERT_EQ(tree.nodesCount(), 1);
    ASSERT_TRUE(tree.hasNode("testList"));
    ASSERT_TRUE(tree.node("testList").isList());
    auto& testList = tree.node("testList").asList();
    ASSERT_EQ(testList.size(), 2);
    {
        auto& nodeData = testList.at(0).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_EQ(nodeData.hasParam("testStr"), 1);
        EXPECT_EQ(nodeData.param("testStr").value(), "Hello");
        ASSERT_EQ(nodeData.nodesCount(), 1);
        ASSERT_EQ(nodeData.hasNode("testNodes"), 1);
        auto& testNodes = nodeData.node("testNodes").asList();
        ASSERT_EQ(testNodes.size(), 2);
        {
            auto& listNodeData = testNodes.at(0).asItem();
            ASSERT_EQ(listNodeData.paramsCount(), 1);
            ASSERT_EQ(listNodeData.hasParam("testInt"), 1);
            ASSERT_TRUE(listNodeData.param("testInt").isItem());
            EXPECT_EQ(listNodeData.param("testInt").value(), "3");
        }
        {
            auto& listNodeData = testNodes.at(1).asItem();
            ASSERT_EQ(listNodeData.paramsCount(), 1);
            ASSERT_EQ(listNodeData.hasParam("testInt"), 1);
            ASSERT_TRUE(listNodeData.param("testInt").isItem());
            EXPECT_EQ(listNodeData.param("testInt").value(), "33");
        }
    }
    {
        auto& nodeData = testList.at(1).asItem();
        ASSERT_EQ(nodeData.paramsCount(), 1);
        ASSERT_TRUE(nodeData.hasParam("testStr"));
        ASSERT_TRUE(nodeData.param("testStr").isItem());
        EXPECT_EQ(nodeData.param("testStr").value(), "World");
        ASSERT_EQ(nodeData.nodesCount(), 1);
        ASSERT_TRUE(nodeData.hasNode("testNodes"));
        auto& testNodes = nodeData.node("testNodes").asList();
        ASSERT_EQ(testNodes.size(), 1);
        {
            auto& listNodeData = testNodes.at(0).asItem();
            ASSERT_EQ(listNodeData.paramsCount(), 1);
            ASSERT_TRUE(listNodeData.hasParam("testInt"));
            EXPECT_EQ(listNodeData.param("testInt").value(), "5");
        }
    }
}

} //namespace test_nodelistparser
