#include <frontier/LevelNavParser.hpp>

#include <graphics/Util.hpp>
#include <log/log.hpp>
#include <sstream>
#include <sstream>

namespace {

using namespace frontier;
using namespace tinyxml2;

// Case insensitive string comparrison.
bool isEqual(const std::string_view& left, const std::string_view& right)
{
    auto lowerLeft = std::string{};
    std::transform(begin(left), end(left), std::back_inserter(lowerLeft), ::tolower);
    auto lowerRight = std::string{};
    std::transform(begin(right), end(right), std::back_inserter(lowerRight), ::tolower);
    return lowerLeft.compare(lowerRight) == 0;
}

/// Ensure that the element name is as expected.
void assertName(const XMLElement* element, const std::string_view& name)
{
    assert(element);
    if (!isEqual(element->Name(), name)) {
        auto err = std::stringstream{};
        err << "Parsing error. Expected: '" << name << "' but found: '" << element->Name() << "'";
        LOGE << err.str();
        throw std::runtime_error(err.str());
    }
}

/// Parse a space seperated list of points
/// ie. 100,5 10,6 67,80
std::vector<Vector2<float>> parsePoints(const std::string& pointList)
{
    std::vector<Vector2<float>> points;
    std::istringstream stream{pointList};
    auto point = std::string{};
    while (std::getline(stream, point, ' ')) {
        auto commaPos = point.find(",");
        auto x = std::stof(point.substr(0, commaPos));
        auto y = std::stof(point.substr(commaPos + 1));
        points.push_back({x, y});
    }

    return points;
}

std::shared_ptr<ConvexShape<float>> parseObject(const XMLElement* baseElement)
{
    assertName(baseElement, "object");
    const auto baseX = baseElement->FloatAttribute("x");
    const auto baseY = baseElement->FloatAttribute("y");

    auto element = baseElement->FirstChildElement();
    assertName(element, "polygon");
    const auto pointList = element->Attribute("points");
    auto points = parsePoints(pointList);

    for (auto& point : points) {
        point += {baseX, baseY};
    }

    return std::make_shared<ConvexShape<float>>(std::move(points));
};

} // namespace

namespace frontier {

LevelNavParser::LevelNavParser() {}

std::shared_ptr<NavMesh> LevelNavParser::parse(const std::string& file)
{
    const auto filePath = getResourcePath() + file;
    XMLDocument doc;
    doc.LoadFile(filePath.c_str());
    if (doc.Error()) {
        auto error = std::string{"XML Error: "} + doc.ErrorStr();
        throw std::runtime_error{error};
    }
    LOGI << "Parsing file: " << file;

    _navMesh = std::make_shared<NavMesh>();

    auto element = doc.RootElement();
    assertName(element, "map");

    element = element->FirstChildElement();
    assertName(element, "objectgroup");
    for (auto object = element->FirstChildElement(); object != nullptr; object = object->NextSiblingElement()) {
        _navMesh->addPoly(parseObject(object));
    }

    return _navMesh;
}

} // namespace frontier
