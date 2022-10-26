/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */
#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "base_graph.hpp"

/**
 * ElementT should be copy constructable and has operator==
 */
template <typename ElementT>
class DirectedGraph : public BaseGraph<ElementT> {
 public:
    bool Init(const std::string &config) override { return true; }

    bool AddVertex(const ElementT &vertex) override {
        if (this->HasVertex(vertex)) {
            return false;
        }
        vertexes_.push_back(std::make_shared<GraphNode<ElementT> >(vertex));
        return true;
    }

    bool AddEdge(const ElementT &from, const ElementT &to) override {
        if (!this->HasVertex(from) || !this->HasVertex(to)) {
            return false;
        }
        for (auto &ite : vertexes_) {
            if (ite->data == from) {
                for (const auto &l : ite->list) {
                    if (l->data == to) {
                        return true;
                    }
                }
                for (const auto &l : vertexes_) {
                    if (l->data == to) {
                        ite->list.push_back(l);
                    }
                }
                return true;
            }
        }
        return true;
    }

    bool HasVertex(const ElementT &vertex) const override {
        for (const auto &ite : vertexes_) {
            if (ite->data == vertex) {
                return true;
            }
        }
        return false;
    }

    const std::vector<std::shared_ptr<GraphNode<ElementT> > > &GetVertexes()
        const override {
        return vertexes_;
    }

 protected:
    std::vector<std::shared_ptr<GraphNode<ElementT> > > vertexes_;
};
