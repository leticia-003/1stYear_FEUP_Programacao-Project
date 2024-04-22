#include "SVGElements.hpp"
#include <iostream>
namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }
    void Ellipse::translate(const Point &translation)
    {
        // Translate the center of the ellipse
        center = center.translate(translation);
    }

    void Ellipse::scale(const Point &origin, int scaling_factor)
    {
        // Scale the radius of the ellipse from the origin
        radius = radius.scale(origin, scaling_factor);
    }

    void Ellipse::rotate(const Point &origin, int degrees)
    {
        // Rotate the center of the ellipse around the origin
        center = center.rotate(origin, degrees);
    }
    // @todo provide the implementation of SVGElement derived classes

    // Circle
    Circle::Circle(const Color &fill, const Point &center, int radius)
            : fill(fill), center(center), radius(radius)
    {
    }

    void Circle::draw(PNGImage &img) const
    {
        // Draw an ellipse where rx = ry = radius
        Point radiusPoint{radius, radius};
        img.draw_ellipse(center, radiusPoint, fill);
    }
    void Circle::translate(const Point &translation)
    {
        // Translate the center of the circle
        center = center.translate(translation);
    }

    void Circle::scale(const Point &origin, int scaling_factor)
    {
        // Scale the radius of the circle from the origin
        radius *= scaling_factor;
        center = center.scale(origin, scaling_factor); // Translate the center
    }

    void Circle::rotate(const Point &origin, int degrees)
    {
        // Rotate the center of the circle around the origin
        center = center.rotate(origin, degrees);
    }


    //Polyline
    Polyline::Polyline(const Color &stroke, const std::vector<Point> &points)
            : stroke(stroke), points(points)
    {
    }

    void Polyline::draw(PNGImage& img) const {
        // Draw polyline
        for (size_t i = 0; i < points.size() - 1; ++i) {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    void Polyline::translate(const Point &translation)
    {
        // Translate each point of the polyline
        for (Point &p : points)
        {
            p = p.translate(translation);
        }
    }

    void Polyline::scale(const Point &origin, int scaling_factor)
    {
        // Scale each point of the polyline from the origin
        for (Point &p : points)
        {
            p = p.scale(origin, scaling_factor);
        }
    }

    void Polyline::rotate(const Point &origin, int degrees)
    {
        // Rotate each point of the polyline around the origin
        for (Point &p : points)
        {
            p = p.rotate(origin, degrees);
        }
    }

    //Line
    Line::Line(const Color& stroke, const Point& start, const Point& end)
            : stroke(stroke), start(start), end(end)
    {
    }

    void Line::draw(PNGImage& img) const {
        // Draw line
        img.draw_line(start, end, stroke);
    }

    void Line::translate(const Point &translation)
    {
        // Translate the start and end points of the line
        start = start.translate(translation);
        end = end.translate(translation);
    }

    void Line::scale(const Point &origin, int scaling_factor)
    {
        // Scale the start and end points of the line from the origin
        start = start.scale(origin, scaling_factor);
        end = end.scale(origin, scaling_factor);
    }

    void Line::rotate(const Point &origin, int degrees)
    {
        // Rotate the start and end points of the line around the origin
        start = start.rotate(origin, degrees);
        end = end.rotate(origin, degrees);
    }

    //Polygon
    Polygon::Polygon(const Color &fill, const std::vector<Point> &points)
            : fill(fill), points(points)
    {
    }

    void Polygon::draw(PNGImage &img) const
    {
        // Construct a vector of Point for drawing the polygon
        std::vector<Point> points_for_drawing = points; // Assuming points is a vector of Point

        // Draw the polygon
        img.draw_polygon(points_for_drawing, fill);
    }


    void Polygon::translate(const Point &translation)
    {
        // Translate each point of the polygon
        for (Point &p : points)
        {
            p = p.translate(translation);
        }
    }

    void Polygon::scale(const Point &origin, int scaling_factor)
    {
        // Scale each point of the polygon from the origin
        for (Point &p : points)
        {
            p = p.scale(origin, scaling_factor);
        }
    }

    void Polygon::rotate(const Point &origin, int degrees)
    {
        // Rotate each point of the polygon around the origin
        for (Point &p : points)
        {
            p = p.rotate(origin, degrees);
        }
    }

    //Rectangle
    Rectangle::Rectangle(const Color &fill, const Point &upper_left, int width, int height)
            : fill(fill), upper_left(upper_left), width(width), height(height)
    {
    }

    void Rectangle::draw(PNGImage &img) const
    {
        // Construct the points for drawing the rectangle
        std::vector<Point> points_for_drawing;
        points_for_drawing.emplace_back(Point{upper_left.x, upper_left.y});
        points_for_drawing.emplace_back(Point{upper_left.x + width, upper_left.y});
        points_for_drawing.emplace_back(Point{upper_left.x + width, upper_left.y + height});
        points_for_drawing.emplace_back(Point{upper_left.x, upper_left.y + height});

        // Draw the rectangle
        img.draw_polygon(points_for_drawing, fill);
    }

    void Rectangle::translate(const Point &translation)
    {
        // Translate the upper left corner of the rectangle
        upper_left = upper_left.translate(translation);
    }

    void Rectangle::scale(const Point &origin, int scaling_factor)
    {
        // Scale the width and height of the rectangle from the origin
        upper_left = upper_left.scale(origin, scaling_factor);
        width *= scaling_factor;
        height *= scaling_factor;
    }

    void Rectangle::rotate(const Point &origin, int degrees)
    {
        // Rotate the upper left corner of the rectangle around the origin
        upper_left = upper_left.rotate(origin, degrees);
    }

}
