#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <algorithm>
#include <sstream>
#include <map>
#include <memory>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    vector<Point> parse_points(const string& points_str) {
        vector<Point> points;
        stringstream ss(points_str);
        char c;
        Point p;

        // Read each point, ignoring commas
        while (ss >> p.x) {
            ss >> c; // This should read the comma separator
            if (ss.peek() == ',') ss.ignore(); // If next character is a comma, ignore it
            ss >> p.y;
            points.push_back(p);
            // Skip all consecutive commas and whitespace
            while (isspace(ss.peek()) || ss.peek() == ',') ss.ignore();
        }

        return points;
    }

    // Function to parse transformation operations and apply them to an SVG element
    template<typename T>
    void parseTransform(T& element, const string& transform, const Point& transformOrigin) {
        stringstream ss(transform);
        string operation;

        while (getline(ss, operation, ')')) {
            if (operation.find("translate") != string::npos) {
                int x = 0, y = 0;
                size_t pos = operation.find('(');
                if (pos != string::npos) {
                    string translateString = operation.substr(pos + 1);
                    // Replace commas with spaces to handle both cases
                    replace(translateString.begin(), translateString.end(), ',', ' ');
                    istringstream iss(translateString);
                    iss >> x >> y;
                    element.addTransformation([=, &element]() { element.translate({x, y}); });
                }
            } else if (operation.find("rotate") != string::npos) {
                int angle;
                sscanf(operation.c_str(), "rotate(%d", &angle);
                element.addTransformation([&element, angle, transformOrigin]() { element.rotate(transformOrigin, angle); });
            } else if (operation.find("scale") != string::npos) {
                int factor;
                sscanf(operation.c_str(), "scale(%d", &factor);
                element.addTransformation([&element, factor, transformOrigin]() { element.scale(transformOrigin, factor); });
            }
        }
    }

    void parseSVGElement(XMLElement* element, const Point& transformOrigin, vector<SVGElement*>& svg_elements, map<string, unique_ptr<SVGElement>>& elementMap) {
        const string nodeName = element->Name();
        const char* attrValue = element->Attribute("transform");
        string transform = attrValue ? attrValue : ""; // Use empty string if null

        Point newTransformOrigin = transformOrigin;

        const char* originAttr = element->Attribute("transform-origin");
        string transformOriginStr = originAttr ? originAttr : "0 0";  // Provide a default "0 0" if not present
        sscanf(transformOriginStr.c_str(), "%d %d", &newTransformOrigin.x, &newTransformOrigin.y);

        // Handle different types of SVG elements
        if (nodeName == "g") {
            auto group = std::make_unique<SVGGroup>();
            group->id = element->Attribute("id") ? element->Attribute("id") : "";
            parseTransform(*group, transform, newTransformOrigin);

            // Process child elements of the group
            XMLElement* child = element->FirstChildElement();
            while (child != nullptr) {
                vector<SVGElement*> childElements;
                parseSVGElement(child, newTransformOrigin, childElements, elementMap);
                for (auto& childElement : childElements) {
                    group->addElement(unique_ptr<SVGElement>(childElement));
                }
                child = child->NextSiblingElement();
            }

            group->applyTransformations();

            // Add the group to the SVG elements vector and element map
            if (!group->id.empty()) {
                auto clonedGroup = group->clone();  // Clone before moving the unique_ptr to the map
                svg_elements.push_back(clonedGroup.release());
                elementMap[group->id] = std::move(group);
            }
            else {
                svg_elements.push_back(group.release());
            }

        } else if (nodeName == "use") {
            const char* href = element->Attribute("href");
            if (href && href[0] == '#') {
                string id = href + 1; // Skip the '#' character
                auto it = elementMap.find(id);
                if (it != elementMap.end()) {
                    // Clone the referenced element
                    auto clonedElement = it->second->clone();
                    clonedElement->setTransformOrigin(newTransformOrigin);
                    parseTransform(*clonedElement, transform, newTransformOrigin);
                    clonedElement->applyTransformations(); // Apply transformations immediately after parsing
                    svg_elements.push_back(clonedElement.release());
                }
            }
        } else {
            unique_ptr<SVGElement> newElement;
            // Determine SVG element type 
            if (nodeName == "ellipse") {
                int cx = element->IntAttribute("cx");
                int cy = element->IntAttribute("cy");
                int rx = element->IntAttribute("rx");
                int ry = element->IntAttribute("ry");
                string fill = element->Attribute("fill");
                Color fillColor = parse_color(fill);

                Point center{cx, cy};
                Point radius{rx, ry};

                newElement = std::make_unique<Ellipse>(fillColor, center, radius);
            } else if (nodeName == "circle") {
                int cx = element->IntAttribute("cx");
                int cy = element->IntAttribute("cy");
                int r = element->IntAttribute("r");
                string fill = element->Attribute("fill");
                Color fillColor = parse_color(fill);

                newElement = std::make_unique<Circle>(fillColor, Point{cx, cy}, r);
            } else if (nodeName == "polyline") {
                string points_str = element->Attribute("points");
                vector<Point> points = parse_points(points_str);
                string stroke = element->Attribute("stroke");
                Color strokeColor = parse_color(stroke);

                newElement = std::make_unique<Polyline>(strokeColor, points);
            } else if (nodeName == "line") {
                int x1 = element->IntAttribute("x1");
                int y1 = element->IntAttribute("y1");
                int x2 = element->IntAttribute("x2");
                int y2 = element->IntAttribute("y2");
                string stroke = element->Attribute("stroke") ? element->Attribute("stroke") : "black";

                Color strokeColor = parse_color(stroke);
                newElement = std::make_unique<Line>(strokeColor, Point{x1, y1}, Point{x2, y2});
            } else if (nodeName == "polygon") {
                string points_str = element->Attribute("points");
                vector<Point> points = parse_points(points_str);
                string fill = element->Attribute("fill");
                Color fillColor = parse_color(fill);

                newElement = std::make_unique<Polygon>(fillColor, points);
            } else if (nodeName == "rect") {
                int x = element->IntAttribute("x");
                int y = element->IntAttribute("y");
                int width = element->IntAttribute("width");
                int height = element->IntAttribute("height");
                string fill = element->Attribute("fill");
                Color fillColor = parse_color(fill);

                newElement = std::make_unique<Rectangle>(Point{x, y}, width, height, fillColor);
            }

            if (newElement) {
                newElement->setTransformOrigin(newTransformOrigin);
                parseTransform(*newElement, transform, newTransformOrigin);
                newElement->applyTransformations(); // Apply transformations immediately after parsing

                const char* idAttr = element->Attribute("id");
                if (idAttr) {
                    newElement->id = idAttr;
                    elementMap[newElement->id] = std::move(newElement);
                } else {
                    // If no ID, manage the element in the local vector
                    svg_elements.push_back(newElement.release());
                }
            }
        }
    }

    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement*>& svg_elements) {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS) {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement* xml_elem = doc.RootElement();
        map<string, unique_ptr<SVGElement>> elementMap;

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");

        XMLElement* child = xml_elem->FirstChildElement();
        while (child != nullptr) {
            parseSVGElement(child, {0, 0}, svg_elements, elementMap);
            child = child->NextSiblingElement();
        }
    }

}