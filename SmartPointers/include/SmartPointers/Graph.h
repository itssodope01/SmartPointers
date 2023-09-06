#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace smartPointers
{
    class GraphNode;
    using GraphNodePtr = std::shared_ptr<GraphNode>;

    class GraphNode {
    private:
        std::string label_;
        std::vector<GraphNodePtr> edges_;

    public:
        GraphNode(const std::string& label) : label_(label), edges_() {}

        void addEdge(GraphNodePtr node) {
            edges_.push_back(node);
        }
        const std::string& getLabel() const {
            return label_;
        }
        const std::vector<GraphNodePtr>& getEdges() const {
            return edges_;
        }
    };

    class Graph {
    private:
        std::vector<GraphNodePtr> nodes_;

    public:
        Graph() : nodes_() {}

        void addNode(GraphNodePtr node) {
            nodes_.push_back(node);
        }
        const std::vector<GraphNodePtr>& getNodes() const {
            return nodes_;
        }

        void addEdge(const std::string label1, const std::string label2);

        std::string toMermaid() const;
        void fromMermaid(const std::string& mermaidString);
    };
}  // namespace smartPointers