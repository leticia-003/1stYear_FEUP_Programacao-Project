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
    void Ellipse::draw(PNGImage &img) const {
        // Calculate actual bounding box of the ellipse to check boundaries
        int minX = center.x - radius.x;
        int maxX = center.x + radius.x;
        int minY = center.y - radius.y;
        int maxY = center.y + radius.y;

        // Ensure the ellipse doesn't draw outside the canvas
        if (minX < 0 || maxX >= img.width() || minY < 0 || maxY >= img.height()) {
            return;  // Skip drawing if it exceeds boundaries
        }

        img.draw_ellipse(center, radius, fill);
    }

    void Ellipse::translate(const Point &translation) {
        center = center.translate(translation);
    }


    void Ellipse::scale(const Point &origin, int scaling_factor) {
        // Scale the radius
        radius.x *= scaling_factor;
        radius.y *= scaling_factor;

        // Scale the center position relative to the transform-origin
        center.x = origin.x + (center.x - origin.x) * scaling_factor;
        center.y = origin.y + (center.y - origin.y) * scaling_factor;
    }


    void Ellipse::rotate(const Point &origin, int degrees)
    {
        // Rotate the center of the ellipse around the origin
        center = center.rotate(origin, degrees);
    }

    void Ellipse::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
    }

    void Ellipse::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Ellipse::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
    }

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

    void Circle::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Circle::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
    }

    void Circle::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
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

    void Polyline::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
    }

    void Polyline::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Polyline::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
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

    void Line::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
    }

    void Line::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Line::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
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

    void Polygon::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
    }

    void Polygon::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Polygon::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
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

    void Rectangle::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
    }

    void Rectangle::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Rectangle::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
    }

}
