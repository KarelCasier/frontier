#include <asset_util/Util.hpp>

#include <SDL2/SDL.h>
#include <log/log.hpp>

namespace frontier {

using namespace std::string_literals;

#ifdef _WIN32
constexpr auto pathSep = '\\';
#else
constexpr auto pathSep = '/';
#endif

const auto binaryDir = "bin"s;
const auto assetDir = "assets"s;

/*
 * Get the resource path for resources located in assets/subDir
 * It's assumed the project directory is structured as:
 * bin/
 *  binary
 * assets/
 *  subdir1/
 *  subdir2/
 */
std::string getResourcePath(const std::string& subDir)
{
    static std::string baseRes;
    if (baseRes.empty()) {
        // SDL_GetBasePath will return NULL if something went wrong in retrieving the path
        char* basePath = SDL_GetBasePath();
        if (basePath) {
            baseRes = basePath;
            SDL_free(basePath);
        } else {
            LOGE << "Error getting resource path: " << SDL_GetError();
            return "";
        }
        size_t pos = baseRes.rfind(binaryDir);
        baseRes = baseRes.substr(0, pos) + "assets" + pathSep;
    }
    return subDir.empty() ? baseRes : baseRes + subDir + pathSep;
}

} // namespace frontier
