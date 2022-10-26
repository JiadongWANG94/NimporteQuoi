/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <vector>
#include <memory>
#include <string>

template <typename ElementT>
class GraphNode {
 public:
    GraphNode<ElementT>() = default;
    GraphNode<ElementT>(const ElementT &data) : data(data){};

 public:
    ElementT data;
    std::vector<std::shared_ptr<GraphNode<ElementT> > > list;
};

/**
 * ElementT should be copy constructable and has operator==
 */
template <typename ElementT>
class BaseGraph {
 public:
    virtual bool Init(const std::string &config) = 0;
    virtual bool AddVertex(const ElementT &vertex) = 0;
    virtual bool AddEdge(const ElementT &from, const ElementT &to) = 0;
    virtual bool HasVertex(const ElementT &vertex) const = 0;
    virtual const std::vector<std::shared_ptr<GraphNode<ElementT> > >
        &GetVertexes() const = 0;

 protected:
    std::vector<std::shared_ptr<GraphNode<ElementT> > > vertexes_;
};
