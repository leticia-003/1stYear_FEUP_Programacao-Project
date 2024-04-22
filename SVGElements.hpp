//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
        virtual void translate(const Point &translation) = 0;
        virtual void scale(const Point &origin, int scaling_factor) = 0;
        virtual void rotate(const Point &origin, int degrees) = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

    private:
        Color fill;
        Point center;
        Point radius;
    };

    class Circle : public SVGElement
    {
    public:
        Circle(const Color &fill, const Point &center, int radius);
        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

    private:
        Color fill;
        Point center;
        int radius;
    };
}
#endif
