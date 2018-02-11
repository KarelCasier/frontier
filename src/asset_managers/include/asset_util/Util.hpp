#pragma once

#include <string>

namespace frontier {

/// Get the path to the resource directory.
///
/// @param subDir The subdirectory to append to the resource path.
/// @returns The resource path.
std::string getResourcePath(const std::string& subDir = "");

}
