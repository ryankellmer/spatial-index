#pragma once

#include "point.hpp"
#include <cstddef>
#include <memory>
#include <utility>

namespace spatial {

template <std::size_t Dim, typename T = double> struct KDNode {
  using PointT = Point<Dim, T>;
  using NodePtr = std::unique_ptr<KDNode<Dim, T>>;
  using size_type = std::size_t;

  PointT point;
  std::size_t axis;
  NodePtr left;
  NodePtr right;

  KDNode(const PointT &p, size_type a)
      : point(p), axis(a), left(nullptr), right(nullptr) {}

  KDNode(PointT &&p, size_type a)
      : point(std::move(p)), axis(a), left(nullptr), right(nullptr) {}

  KDNode(const KDNode &) = delete;
  KDNode &operator=(const KDNode &) = delete;

  KDNode(KDNode &&) = default;
  KDNode &operator=(KDNode &&) = default;
};
} // namespace spatial
