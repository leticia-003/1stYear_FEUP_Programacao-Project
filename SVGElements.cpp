#include "SVGElements.hpp"
#include <iostream>
#include <memory>
using namespace std;

namespace svg {
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Add a transformation to the element
    void SVGElement::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
    }
    
     // Implementation for Ellipse
    Ellipse::Ellipse(const Color& fill, const Point& center, const Point& radius)
            : fill(fill), center(center), radius(radius) {}

    void Ellipse::draw(PNGImage& img) const {
        img.draw_ellipse(center, radius, fill);
    }

    void Ellipse::translate(const Point& translation) {
        center = center.translate(translation);
    }

    void Ellipse::scale(const Point& origin, int scaling_factor) {
        radius.x *= scaling_factor;
        radius.y *= scaling_factor;
        center.x = origin.x + (center.x - origin.x) * scaling_factor;
        center.y = origin.y + (center.y - origin.y) * scaling_factor;
    }

    void Ellipse::rotate(const Point& origin, int degrees) {
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

    std::unique_ptr<SVGElement> Ellipse::clone() const {
        return std::make_unique<Ellipse>(*this);
    }

    // Implementation for Circle
    Circle::Circle(const Color& fill, const Point& center, int radius)
            : fill(fill), center(center), radius(radius) {}

    void Circle::draw(PNGImage& img) const {
        Point radiusPoint{radius, radius};
        if (center.x >= 0 && center.x < img.width() && center.y >= 0 && center.y < img.height()) {
            img.draw_ellipse(center, radiusPoint, fill);
        }
    }

    void Circle::translate(const Point& translation) {
        center = center.translate(translation);
    }

    void Circle::scale(const Point& origin, int scaling_factor) {
        radius *= scaling_factor;
        center = center.scale(origin, scaling_factor);
    }

    void Circle::rotate(const Point& origin, int degrees) {
        center = center.rotate(origin, degrees);
    }

    void Circle::applyTransformations() {
        for (const auto& transform : transformations) {
            transform();
        }
        transformations.clear();
    }

    void Circle::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
    }

    void Circle::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
    }

    std::unique_ptr<SVGElement> Circle::clone() const {
        return std::make_unique<Circle>(*this);
    }

    // Implementation for Polyline
    Polyline::Polyline(const Color& stroke, const std::vector<Point>& points)
            : stroke(stroke), points(points) {}

    void Polyline::draw(PNGImage& img) const {
        for (size_t i = 0; i < points.size() - 1; ++i) {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    void Polyline::translate(const Point& translation) {
        for (Point& p : points) {
            p = p.translate(translation);
        }
    }

    void Polyline::scale(const Point& origin, int scaling_factor) {
        for (Point& p : points) {
            p = p.scale(origin, scaling_factor);
        }
    }

    void Polyline::rotate(const Point& origin, int degrees) {
        for (Point& p : points) {
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

    std::unique_ptr<SVGElement> Polyline::clone() const {
        return std::make_unique<Polyline>(*this);
    }

    // Implementation for Line
    Line::Line(const Color& stroke, const Point& start, const Point& end)
            : stroke(stroke), start(start), end(end) {}

    void Line::draw(PNGImage& img) const {
        img.draw_line(start, end, stroke);
    }

    void Line::translate(const Point& translation) {
        start = start.translate(translation);
        end = end.translate(translation);
    }

    void Line::scale(const Point& origin, int scaling_factor) {
        start = start.scale(origin, scaling_factor);
        end = end.scale(origin, scaling_factor);
    }

    void Line::rotate(const Point& origin, int degrees) {
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

    std::unique_ptr<SVGElement> Line::clone() const {
        return std::make_unique<Line>(*this);
    }

    // Implementation for Polygon
    Polygon::Polygon(const Color& fill, const std::vector<Point>& points)
            : fill(fill), points(points) {}

    void Polygon::draw(PNGImage& img) const {
        img.draw_polygon(points, fill);
    }

    void Polygon::translate(const Point& translation) {
        for (Point& p : points) {
            p = p.translate(translation);
        }
    }

    void Polygon::scale(const Point& origin, int scaling_factor) {
        for (Point& p : points) {
            p = p.scale(origin, scaling_factor);
        }
    }

    void Polygon::rotate(const Point& origin, int degrees) {
        for (Point& p : points) {
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

    std::unique_ptr<SVGElement> Polygon::clone() const {
        return std::make_unique<Polygon>(*this);
    }

    // Implementation for Rectangle 
    std::vector<Point> rectangleCoordinates(const Point& topLeft, const int& width, const int& height){
        Point topRight, bottomLeft, bottomRight;
        std::vector<Point> coordinates;
        topRight = Point({topLeft.x+(width-1),topLeft.y});
        bottomLeft= Point({topLeft.x,topLeft.y+(height-1)});
        bottomRight= Point({topLeft.x+(width-1),topLeft.y+(height-1)});
        coordinates.push_back(topLeft);
        coordinates.push_back(topRight);
        coordinates.push_back(bottomRight);
        coordinates.push_back(bottomLeft);
        return coordinates;
    }

    Rectangle::Rectangle(const Point &topLeft, const int &width, const int &height, const Color &fill)
    : Polygon(fill, (rectangleCoordinates(topLeft, width, height))){}


    // Implementation for Group
    SVGGroup::SVGGroup() {}

    void SVGGroup::draw(PNGImage& img) const {
        for (const auto& element : elements) {
            element->draw(img);
        }
    }

    void SVGGroup::translate(const Point& translation) {
        for (auto& element : elements) {
            element->translate(translation);
        }
    }

    void SVGGroup::scale(const Point& origin, int scaling_factor) {
        for (auto& element : elements) {
            element->scale(origin, scaling_factor);
        }
    }

    void SVGGroup::rotate(const Point& origin, int degrees) {
        for (auto& element : elements) {
            element->rotate(origin, degrees);
        }
    }

    void SVGGroup::applyTransformations(){
        for (const auto& transform : transformations) {
            transform();
        }
        transformations.clear();
    }

    void SVGGroup::setTransformOrigin(const Point& origin) {
        transformOrigin = origin;
        for (auto& element : elements) {
            element->setTransformOrigin(origin);
        }
    }

    void SVGGroup::addTransformation(const std::function<void()>& transformation) {
        transformations.push_back(transformation);
    }

    void SVGGroup::addElement(std::unique_ptr<SVGElement> element) {
        elements.push_back(std::move(element));
    }

    std::unique_ptr<SVGElement> SVGGroup::clone() const {
        auto clonedGroup = std::make_unique<SVGGroup>();
        clonedGroup->id = this->id;
        clonedGroup->transformations = this->transformations;
        for (const auto& element : elements) {
            clonedGroup->elements.push_back(element->clone());
        }
        return clonedGroup;
    }
}
