#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#include "SmartPointers/Graph.h"

namespace smartPointers
{
namespace
{
// Test fixture for Graph tests
class TestBasicGraph : public ::testing::Test
{
protected:
    void SetUp() override
    {
        nodeA_ = std::make_shared<GraphNode>("A");
        nodeB_ = std::make_shared<GraphNode>("B");
        nodeC_ = std::make_shared<GraphNode>("C");
        nodeD_ = std::make_shared<GraphNode>("D");
        nodeE_ = std::make_shared<GraphNode>("E");

        nodeA_->addEdge(nodeB_);
        nodeA_->addEdge(nodeC_);
        nodeB_->addEdge(nodeC_);
        nodeC_->addEdge(nodeD_);
        nodeC_->addEdge(nodeE_);

        graph_.addNode(nodeA_);
        graph_.addNode(nodeB_);
        graph_.addNode(nodeC_);
        graph_.addNode(nodeD_);
        graph_.addNode(nodeE_);
    }

    Graph graph_{};
    std::shared_ptr<GraphNode> nodeA_{};
    std::shared_ptr<GraphNode> nodeB_{};
    std::shared_ptr<GraphNode> nodeC_{};
    std::shared_ptr<GraphNode> nodeD_{};
    std::shared_ptr<GraphNode> nodeE_{};
};

// Test that the Graph class adds nodes correctly
TEST_F(TestBasicGraph, AddsNodes)
{
    EXPECT_EQ(5, graph_.getNodes().size());
    EXPECT_EQ(nodeA_, graph_.getNodes()[0]);
    EXPECT_EQ(nodeB_, graph_.getNodes()[1]);
    EXPECT_EQ(nodeC_, graph_.getNodes()[2]);
    EXPECT_EQ(nodeD_, graph_.getNodes()[3]);
    EXPECT_EQ(nodeE_, graph_.getNodes()[4]);
}

// Test that the Graph class returns the correct nodes for each edge
TEST_F(TestBasicGraph, ReturnsCorrectEdges)
{
    auto edgesA = nodeA_->getEdges();
    ASSERT_EQ(2, edgesA.size());
    EXPECT_EQ(nodeB_, edgesA[0]);
    EXPECT_EQ(nodeC_, edgesA[1]);

    auto edgesB = nodeB_->getEdges();
    ASSERT_EQ(1, edgesB.size());
    EXPECT_EQ(nodeC_, edgesB[0]);

    auto edgesC = nodeC_->getEdges();
    ASSERT_EQ(2, edgesC.size());
    EXPECT_EQ(nodeD_, edgesC[0]);
    EXPECT_EQ(nodeE_, edgesC[1]);

    auto edgesD = nodeD_->getEdges();
    ASSERT_EQ(0, edgesD.size());
    auto edgesE = nodeE_->getEdges();
    ASSERT_EQ(0, edgesE.size());
}

}  // namespace
}  // namespace smartPointers