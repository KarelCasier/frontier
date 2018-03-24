#pragma once

#include <experimental/optional>

/// Inject optional into std
/// TODO: Remove when libc++ moves optional out of experimental
namespace std {
template <typename T>
using optional = experimental::optional<T>;
} // namespace std
