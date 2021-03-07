/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */
#pragma once

#include "directed_graph.hpp"

/**
 * ElementT should be copy constructable and has operator==
 */
template <typename ElementT>
class DirectedAcyclicGraph : public DirectedGraph<ElementT> {
 public:
    bool Init(const std::string &config) { return true; }

    bool AddVertex(const ElementT &vertex) {
        if (this->HasVertex(vertex)) {
            return false;
        }
        std::cout << "Here" << std::endl;
        vertexes_.push_back(std::make_shared<GraphNode<ElementT> >(vertex));
        return true;
    }

    bool AddEdge(const ElementT &from, const ElementT &to) {
        if (!this->HasVertex(from) || !this->HasVertex(to)) {
            return false;
        }
        for (auto &ite : vertexes_) {
            if (ite->data == to) {
                for (const auto &l : ite->list) {
                    if (l->data == to) {
                        return true;
                    }
                }
                ite->list.push_back(std::make_shared<GraphNode<ElementT> >(to));
                return true;
            }
        }
        return true;
    }

    bool HasVertex(const ElementT &vertex) {
        for (const auto &ite : vertexes_) {
            if (ite->data == vertex) {
                return false;
            }
        }
        return true;
    }

    bool IsValid() {}

    const std::vector<std::shared_ptr<GraphNode<ElementT> > > &GetVertexes()
        const {
        return vertexes_;
    }

 private:
    bool CheckCircle() {}

    bool CheckConnectivity() {}

 private:
    std::vector<std::shared_ptr<GraphNode<ElementT> > > vertexes_;
};
