#include <SmartPointers/Graph.h>

#include <regex>

namespace smartPointers
{ 
    void Graph::addEdge(const std::string label1, const std::string label2){
        
        GraphNodePtr node1, node2;
        for (auto& node : nodes_) {
            if (node->getLabel() == label1) {
                node1 = node;
            }
            if (node->getLabel() == label2) {
                node2 = node;
            }
        }
        
        if (!node1) {
            node1 = std::make_shared<GraphNode>(label1);
            nodes_.push_back(node1);
        }
        if (!node2) {
            node2 = std::make_shared<GraphNode>(label2);
            nodes_.push_back(node2);
        }
        
        bool edgeExists = false;
        for (auto& edge : node1->getEdges()) {
            if (edge == node2) {
                edgeExists = true;
                break;
            }
        }
        
        if (!edgeExists) {
            node1->addEdge(node2); 
        }
    }

    
    std::string Graph::toMermaid() const {
        if (nodes_.empty()){
            std::ostringstream os;
            os << "flowchart LR\n";
            return os.str();
        }
        else {
            std::ostringstream os;
            os << R"(flowchart LR
)";
            for (const auto& node : nodes_) {
                os << "    " << node->getLabel() << std::endl;
            }
            for (const auto& node : nodes_) {
                for (const auto& edge : node->getEdges()) {
                    os << "    " << node->getLabel() << " --> " << edge->getLabel() << std::endl;
                }
            }
            return os.str();
        }
    }

    void Graph::fromMermaid(const std::string& mermaidString) {
        nodes_.clear();
        std::regex nodeRegex(R"(^\s*(\w+)\s*$)");
        std::regex edgeRegex(R"(^\s*(\w+)\s*-->\s*(\w+)\s*$)");
        std::smatch match;

        // Add nodes
        std::istringstream iss(mermaidString);
        std::string line;
        while (std::getline(iss, line)) {
            if (std::regex_match(line, match, nodeRegex)) {
                std::string label = match[1];
                GraphNodePtr node = std::make_shared<GraphNode>(label);
                nodes_.push_back(node);
            }
        }

        // Add edges
        iss.clear();
        iss.seekg(0);
        while (std::getline(iss, line)) {
            if (std::regex_match(line, match, edgeRegex)) {
                std::string label1 = match[1];
                std::string label2 = match[2];
                GraphNodePtr node1, node2;
                for (auto& node : nodes_) {
                    if (node->getLabel() == label1) {
                        node1 = node;
                    }
                    if (node->getLabel() == label2) {
                        node2 = node;
                    }
                }
                if (node1 && node2) {
                    node1->addEdge(node2);
                }
            }
        }
    }

}  // namespace smartPointers