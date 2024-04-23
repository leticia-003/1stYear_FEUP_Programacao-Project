
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <sstream>

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
            ss >> c;  // This should read the comma separator
            if (ss.peek() == ',') ss.ignore();  // If next character is a comma, ignore it
            ss >> p.y;
            points.push_back(p);
            // Skip all consecutive commas and whitespace
            while (isspace(ss.peek()) || ss.peek() == ',') ss.ignore();
        }

        return points;
    }
    template<typename T>

    void parseTransform(T& element, const string& transform, const Point& transformOrigin) {
        stringstream ss(transform);
        string operation;

        while (ss >> operation) {
            if (operation.find("translate") != string::npos) {
                int x, y;
                sscanf(operation.c_str(), "translate(%d %d)", &x, &y);
                element.addTransformation([&element, x, y]() { element.translate({x, y}); });
            } else if (operation.find("rotate") != string::npos) {
                int angle;
                sscanf(operation.c_str(), "rotate(%d)", &angle);
                element.addTransformation([&element, angle, &transformOrigin]() { element.rotate(transformOrigin, angle); });
            } else if (operation.find("scale") != string::npos) {
                int factor;
                sscanf(operation.c_str(), "scale(%d)", &factor);
                element.addTransformation([&element, factor, &transformOrigin]() { element.scale(transformOrigin, factor); });
            }
        }
    }



    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();
        vector<SVGElement *> shapes;

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        // TODO complete code -->
        // Parsing ellipse elements
        XMLElement* child = xml_elem->FirstChildElement();
        while (child != nullptr)
        {
            const string nodeName = child->Name();

            const char* attrValue = child->Attribute("transform");
            string transform = attrValue ? attrValue : "";  // Use empty string if null

            const char* fillAttr = child->Attribute("fill");
            string fill = fillAttr ? fillAttr : "default_color";  // Provide a default color if missing

            Point transformOrigin{0, 0}; // Default origin

            const char* originAttr = child->Attribute("transform-origin");
            string transformOriginStr = originAttr ? originAttr : "0 0";  // Provide a default "0 0" if not present
            sscanf(transformOriginStr.c_str(), "%d %d", &transformOrigin.x, &transformOrigin.y);




            // Determine SVG element type
            if (nodeName == "ellipse")
            {
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int rx = child->IntAttribute("rx");
                int ry = child->IntAttribute("ry");
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                // Create center and radius points
                Point center;
                center.x = cx;
                center.y = cy;

                Point radius;
                radius.x = rx;
                radius.y = ry;

                // Create Ellipse and store it
                Ellipse* ellipse = new Ellipse(fillColor, center, radius);
                svg_elements.push_back(ellipse);
            }

            else if (nodeName == "circle")
            {
                int cx = child->IntAttribute("cx");
                int cy = child->IntAttribute("cy");
                int r = child->IntAttribute("r");
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                Circle* circle = new Circle(fillColor, Point{cx, cy}, r);
                circle->setTransformOrigin(transformOrigin);
                parseTransform(*circle, transform, transformOrigin);
                circle->applyTransformations();
                svg_elements.push_back(circle);
            }

            else if (nodeName == "polyline")
            {
                string points_str = child->Attribute("points");
                vector<Point> points;
                stringstream ss(points_str);
                while (!ss.eof())
                {
                    Point p;
                    char c;
                    ss >> p.x >> c >> p.y;
                    points.push_back(p);
                }
                string stroke = child->Attribute("stroke");
                Color strokeColor = parse_color(stroke);
                Polyline* polyline = new Polyline(strokeColor, points);

                polyline->setTransformOrigin(transformOrigin);
                parseTransform(*polyline, transform, transformOrigin);
                polyline->applyTransformations();

                svg_elements.push_back(polyline);
            }
            else if (nodeName == "line") {
                int x1 = child->IntAttribute("x1");
                int y1 = child->IntAttribute("y1");
                int x2 = child->IntAttribute("x2");
                int y2 = child->IntAttribute("y2");
                string stroke = child->Attribute("stroke") ? child->Attribute("stroke") : "black";

                Color strokeColor = parse_color(stroke);
                Line* line = new Line(strokeColor, Point{x1, y1}, Point{x2, y2});

                line->setTransformOrigin(transformOrigin);
                parseTransform(*line, transform, transformOrigin);
                line->applyTransformations();

                svg_elements.push_back(line);
            }

            else if (nodeName == "polygon")
            {
                string points_str = child->Attribute("points");
                vector<Point> points = parse_points(points_str);
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);

                Polygon* polygon = new Polygon(fillColor, points);

                polygon->setTransformOrigin(transformOrigin);
                parseTransform(*polygon, transform, transformOrigin);
                polygon->applyTransformations();

                svg_elements.push_back(polygon);
            }

            else if (nodeName == "rect")
            {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);
                width -= 1;
                height -= 1;
                svg_elements.push_back(new Rectangle(fillColor, Point{x, y}, width, height));
            }


            // Move to the next child
            child = child->NextSiblingElement();
        }
        
    }
}