
#include <SmartPointers/Graph.h>
#include <gtest/gtest.h>

#include <algorithm>

TEST(TestAddEdge, AddEdge)
{
    using namespace smartPointers;

    Graph graph{};
    std::shared_ptr<GraphNode> nodeA = std::make_shared<GraphNode>("A");
    std::shared_ptr<GraphNode> nodeB = std::make_shared<GraphNode>("B");

    graph.addNode(nodeA);
    graph.addNode(nodeB);
    graph.addEdge("B", "A");
    graph.addEdge("A", "C");
    graph.addEdge("D", "E");
    graph.addEdge("F", "E");
    graph.addEdge("F", "D");

    auto nodes = graph.getNodes();
    ASSERT_EQ(6, nodes.size());
    EXPECT_EQ(nodes[0]->getLabel(), "A");
    ASSERT_EQ(nodes[0]->getEdges().size(), 1);
    EXPECT_EQ(nodes[0]->getEdges()[0], nodes[2]);

    EXPECT_EQ(nodes[1]->getLabel(), "B");
    ASSERT_EQ(nodes[1]->getEdges().size(), 1);
    EXPECT_EQ(nodes[1]->getEdges()[0], nodes[0]);

    EXPECT_EQ(nodes[2]->getLabel(), "C");
    ASSERT_EQ(nodes[2]->getEdges().size(), 0);

    EXPECT_EQ(nodes[3]->getLabel(), "D");
    ASSERT_EQ(nodes[3]->getEdges().size(), 1);
    EXPECT_EQ(nodes[3]->getEdges()[0], nodes[4]);

    EXPECT_EQ(nodes[4]->getLabel(), "E");
    ASSERT_EQ(nodes[4]->getEdges().size(), 0);

    EXPECT_EQ(nodes[5]->getLabel(), "F");
    ASSERT_EQ(nodes[5]->getEdges().size(), 2);
    EXPECT_EQ(nodes[5]->getEdges()[0], nodes[4]);
    EXPECT_EQ(nodes[5]->getEdges()[1], nodes[3]);
}