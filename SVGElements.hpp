

#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include <functional>
#include <vector>
#include <memory>
#include <string>
#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include "make_unique.h"  // Include the custom make_unique

namespace svg
{
    class SVGElement
    {
    public:
        std::string id;
        std::vector<std::function<void()>> transformations;

        SVGElement();
        virtual ~SVGElement();

        virtual void draw(PNGImage &img) const = 0;
        virtual void translate(const Point &translation) = 0;
        virtual void scale(const Point &origin, int scaling_factor) = 0;
        virtual void rotate(const Point &origin, int degrees) = 0;

        virtual std::unique_ptr<SVGElement> clone() const = 0;
        virtual void applyTransformations() = 0;
        virtual void setTransformOrigin(const Point& origin) = 0;
        virtual void addTransformation(const std::function<void()>& transformation) = 0;
    };

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

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill;
        Point center;
        Point radius;
        Point transformOrigin;
    };

    class Circle : public SVGElement
    {
    public:
        Circle(const Color &fill, const Point &center, int radius);

        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill;
        Point center;
        int radius;
        Point transformOrigin;
    };

    class Polyline : public SVGElement
    {
    public:
        Polyline(const Color &stroke, const std::vector<Point> &points);

        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

    private:
        Color stroke;
        std::vector<Point> points;
        Point transformOrigin;
    };

    class Line : public SVGElement
    {
    public:
        Line(const Color &stroke, const Point &start, const Point &end);

        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

    private:
        Color stroke;
        Point start;
        Point end;
        Point transformOrigin;
    };

    class Polygon : public SVGElement
    {
    public:
        Polygon(const Color &fill, const std::vector<Point> &points);

        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill;
        std::vector<Point> points;
        Point transformOrigin;
    };

    class Rectangle : public SVGElement
    {
    public:
        Rectangle(const Color &fill, const Point &upper_left, int width, int height);

        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill;
        Point upper_left;
        int width;
        int height;
        Point transformOrigin;
    };

    class SVGGroup : public SVGElement
    {
    public:
        SVGGroup();

        void draw(PNGImage &img) const override;
        void translate(const Point &translation) override;
        void scale(const Point &origin, int scaling_factor) override;
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations() override;
        void setTransformOrigin(const Point& origin) override;
        void addTransformation(const std::function<void()>& transformation) override;
        std::unique_ptr<SVGElement> clone() const override;

        void addElement(std::unique_ptr<SVGElement> element);

    private:
        std::vector<std::unique_ptr<SVGElement>> elements;
        Point transformOrigin;
    };
}

#endif


