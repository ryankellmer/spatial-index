#pragma once

#include "kd_node.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <vector>
namespace spatial {

template <std::size_t Dim, typename T = double> class KDTree {
public:
  using PointT = Point<Dim, T>;
  using Node = KDNode<Dim, T>;

  KDTree() = default;

  explicit KDTree(const std::vector<PointT> &points) { build(points); }

  void build(const std::vector<PointT> &points) {
    std::vector<PointT> pts = points;
    root_ = build_recursive(pts, 0);
  }

  const PointT *nearest(const PointT &query) const {
    if (!root_) {
      return nullptr;
    }

    const Node *best = nullptr;
    T best_dist = std::numeric_limits<T>::max();
    nearest_recursive(root_.get(), query, best, best_dist);
    return best ? &best->point : nullptr;
  }

private:
  std::unique_ptr<Node> root_;

  std::unique_ptr<Node> build_recursive(const std::vector<PointT> &points,
                                        std::size_t depth) {
    if (points.empty()) {
      return nullptr;
    }

    std::size_t axis = depth % Dim;
    auto mid_iter = points.begin() + points.size() / 2;

    std::nth_element(
        points.begin(), mid_iter, points.end(),
        [axis](const PointT &a, const PointT &b) { return a[axis] < b[axis]; });

    std::vector<PointT> left(points.begin(), mid_iter);
    std::vector<PointT> right(mid_iter + 1, points.end());

    auto node = std::make_unique<Node>(*mid_iter, axis);
    node->left = build_recursive(left, depth + 1);
    node->right = build_recursive(right, depth + 1);

    return node;
  }

  void nearest_recursive(const Node *node, const PointT &query,
                         const Node *&best, T &best_dist) const {
    if (!node) {
      return;
    }

    T dist = 0;
    for (std::size_t i = 0; i < Dim; ++i) {
      T d = node->point[i] - query[i];
      dist += d * d;
    }

    if (dist < best_dist) {
      best_dist = dist;
      best = node;
    }

    T diff = query[node->axis] - node->point[node->axis];
    const Node *first = diff < 0 ? node->left.get() : node->right.get();
    const Node *second = diff < 0 ? node->right.get() : node->left.get();

    nearest_recursive(first, query, best, best_dist);

    if (diff * diff < best_dist) {
      nearest_recursive(second, query, best, best_dist);
    }
  }
};
} // namespace spatial
