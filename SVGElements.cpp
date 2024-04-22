#include "SVGElements.hpp"

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

}
