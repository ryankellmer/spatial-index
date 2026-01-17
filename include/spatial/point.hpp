#pragma once

#include <cstddef>
#include <stdexcept>
#include <type_traits>

namespace spatial {

template <std::size_t Dim, typename T = double> struct Point {
  static_assert(Dim > 0, "Dimension must be greater than 0");
  static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type");
  using value_type = T;
  using size_type = std::size_t;
  static constexpr size_type dimension = Dim;

  std::array<T, Dim> coords{};

  constexpr T &operator[](size_type i) noexcept { return coords[i]; }

  constexpr const T &operator[](size_type i) const noexcept {
    return coords[i];
  }

  constexpr T &at(size_type i) {
    if (i >= Dim) {
      throw std::out_of_range("Point coordinate index out of range");
    }

    return coords[i];
  }

  constexpr const T &at(size_type i) const {
    if (i >= Dim) {
      throw std::out_of_range("Point coordinate index out of range");
    }

    return coords[i];
  }

  constexpr bool operator==(const Point &) const = default;
};
} // namespace spatial
