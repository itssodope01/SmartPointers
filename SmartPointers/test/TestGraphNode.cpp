
#include <SmartPointers/Graph.h>
#include <gtest/gtest.h>

#include <algorithm>

std::string demangle(char const *name);
std::string demangle(char const *name)
{
    int status = -4;
    std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, NULL, NULL, &status), std::free};
    return (status == 0) ? res.get() : name;
}

TEST(TestGraphNode, Demangle)
{
    std::shared_ptr<smartPointers::GraphNode> node = std::make_shared<smartPointers::GraphNode>("node1");

    EXPECT_EQ(demangle(typeid(node->getLabel()).name()),
              "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >");
    EXPECT_EQ(demangle(typeid(node->getEdges()).name()),
              "std::vector<std::shared_ptr<smartPointers::GraphNode>, std::allocator<std::shared_ptr<smartPointers::GraphNode> "
              "> >");
    EXPECT_EQ(demangle(typeid(smartPointers::GraphNodePtr).name()), "std::shared_ptr<smartPointers::GraphNode>");
    EXPECT_EQ(demangle(typeid(*node).name()), "smartPointers::GraphNode");
}

TEST(TestGraphNode, AddEdge)
{
    std::shared_ptr<smartPointers::GraphNode> node1 = std::make_shared<smartPointers::GraphNode>("node1");
    std::shared_ptr<smartPointers::GraphNode> node2 = std::make_shared<smartPointers::GraphNode>("node2");

    node1->addEdge(node2);

    EXPECT_EQ(node1->getEdges().size(), 1);
    EXPECT_EQ(node1->getEdges()[0], node2);
}

TEST(TestGraphNode, GetLabel)
{
    std::shared_ptr<smartPointers::GraphNode> node = std::make_shared<smartPointers::GraphNode>("node1");

    EXPECT_EQ(node->getLabel(), "node1");
}

TEST(TestGraphNode, GetEdges)
{
    std::shared_ptr<smartPointers::GraphNode> node1 = std::make_shared<smartPointers::GraphNode>("node1");
    std::shared_ptr<smartPointers::GraphNode> node2 = std::make_shared<smartPointers::GraphNode>("node2");

    node1->addEdge(node2);

    std::vector<std::shared_ptr<smartPointers::GraphNode>> edges = node1->getEdges();
    EXPECT_EQ(edges.size(), 1);
    EXPECT_EQ(edges[0], node2);
}