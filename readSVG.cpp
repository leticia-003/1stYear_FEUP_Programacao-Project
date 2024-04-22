
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

                // Create center point
                Point center{cx, cy};

                // Create Circle and store it
                svg_elements.push_back(new Circle(fillColor, center, r));
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
                svg_elements.push_back(new Polyline(strokeColor, points));
            }
            else if (nodeName == "line")
            {
                int x1 = child->IntAttribute("x1");
                int y1 = child->IntAttribute("y1");
                int x2 = child->IntAttribute("x2");
                int y2 = child->IntAttribute("y2");
                string stroke = child->Attribute("stroke");
                Color strokeColor = parse_color(stroke);

                Point start{x1, y1};
                Point end{x2, y2};
                svg_elements.push_back(new Line(strokeColor, start, end));
            }

            else if (nodeName == "polygon")
            {
                string points_str = child->Attribute("points");
                vector<Point> points = parse_points(points_str);
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);
                svg_elements.push_back(new Polygon(fillColor, points));
            }

            else if (nodeName == "rect")
            {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                string fill = child->Attribute("fill");
                Color fillColor = parse_color(fill);
                svg_elements.push_back(new Rectangle(fillColor, Point{x, y}, width, height));
            }


            // Move to the next child
            child = child->NextSiblingElement();
        }
        
    }
}