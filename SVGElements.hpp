#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include <functional>
#include <vector>
#include <memory>
#include <string>
#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include "make_unique.h" 

namespace svg
{
    /**
     * @brief Base class for SVG elements.
     */
    class SVGElement
    {
    public:
        std::string id; ///< The id of the element.
        std::vector<std::function<void()>> transformations; ///< The transformations to be applied to the element.

        SVGElement(); ///< Default constructor.
        virtual ~SVGElement(); ///< Destructor.
        /**
         * @brief Draws the SVG element on the given image.
         * @param img The image to draw on.
         */
        virtual void draw(PNGImage &img) const = 0;
        /**
         * @brief Translates the SVG element.
         * @param translation The translation point.
         */
        virtual void translate(const Point &translation) = 0;
        /**
         * @brief Scales the SVG element.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        virtual void scale(const Point &origin, int scaling_factor) = 0;
        /**
         * @brief Rotates the SVG element.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        virtual void rotate(const Point &origin, int degrees) = 0;
        /**
         * @brief Clones the SVG element.
         * @return A unique pointer to the cloned element.
         */
        virtual std::unique_ptr<SVGElement> clone() const = 0;
        /**
         * @brief Applies the transformations to the SVG element.
         */
        virtual void applyTransformations() = 0;
        /**
         * @brief Sets the transformation origin for the SVG element.
         * @param origin origin The transformation origin point.
         */
        virtual void setTransformOrigin(const Point& origin) = 0;
        /**
         * @brief Adds a transformation to the SVG element.
         * @param transformation The transformation function.
         */
        virtual void addTransformation(const std::function<void()>& transformation) = 0;
    };

    /**
     * @brief Reads an SVG file and populates dimensions and SVG elements.
     * @param svg_file The path to the SVG file.
     * @param dimensions The dimensions of the SVG.
     * @param svg_elements The vector to store SVG elements.
     */
    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    /**
     * @brief Converts an SVG file to a PNG file.
     * @param svg_file The path to the SVG file.
     * @param png_file The path to the PNG file.
     */
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    /**
     * @brief Class representing an ellipse in SVG.
     */
    class Ellipse : public SVGElement
    {
    public:
        /**
         * @brief Constructs an Ellipse object.
         * @param fill The fill color of the ellipse.
         * @param center The center point of the ellipse.
         * @param radius The radius of the ellipse.
         */
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        /**
         * @brief Draws the ellipse on the image.
         * @param img The image to draw on.
         */
        virtual void draw(PNGImage &img) const override;
        /**
         * @brief Translates the ellipse.
         * @param translation The translation point.
         */
        void translate(const Point &translation) override;
        /**
         * @brief Scales the ellipse.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        void scale(const Point &origin, int scaling_factor) override;
        /**
         * @brief Rotates the ellipse.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        void rotate(const Point &origin, int degrees) override;
        /**
         * @brief Applies the transformations to the ellipse.
         */
        void applyTransformations() override;
        /**
         * @brief Sets the transformation origin for the ellipse.
         * @param origin The transformation origin point.
         */
        void setTransformOrigin(const Point& origin) override;
        /**
         * @brief Adds a transformation to the ellipse.
         * @param transformation The transformation function.
         */
        void addTransformation(const std::function<void()>& transformation) override;
        /**
         * @brief Clones the ellipse.
         * @return A unique pointer to the cloned ellipse.
         */
        virtual std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill; ///< The fill color of the ellipse.
        Point center; ///< The center point of the ellipse.
        Point radius; ///< The radius of the ellipse.
        Point transformOrigin; ///< The transformation origin point of the ellipse.
    };

    /**
     * @brief Class representing a circle in SVG.
     */
    class Circle : public SVGElement
    {
    public:
        /**
         * @brief Constructs a Circle object.
         * @param fill The fill color of the circle.
         * @param center The center point of the circle.
         * @param radius The radius of the circle.
         */
        Circle(const Color &fill, const Point &center, int radius);
        /**
         * @brief Draws the circle on the image.
         * @param img The image to draw on.
         */
        virtual void draw(PNGImage &img) const override;
        /**
         * @brief Translates the circle.
         * @param translation The translation point.
         */
        void translate(const Point &translation) override;
        /**
         * @brief Scales the circle.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        void scale(const Point &origin, int scaling_factor) override;
        /**
         * @brief Rotates the circle.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        void rotate(const Point &origin, int degrees) override;
        /**
         * @brief Applies the transformations to the circle.
         */
        void applyTransformations() override;
        /**
         * @brief Sets the transformation origin for the circle.
         * @param origin The transformation origin point.
         */
        void setTransformOrigin(const Point& origin) override;
        /**
         * @brief Adds a transformation to the circle.
         * @param transformation The transformation function.
         */
        void addTransformation(const std::function<void()>& transformation) override;
        /**
         * @brief Clones the circle.
         * @return A unique pointer to the cloned circle.
         */
        virtual std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill; ///< The fill color of the circle.
        Point center; ///< The center point of the circle.
        int radius; ///< The radius of the circle.
        Point transformOrigin; ///< The transformation origin point of the circle.
    };

    /**
     * @brief Class representing a polyline in SVG.
     */
    class Polyline : public SVGElement
    {
    public:
        /**
         * @brief Constructs a Polyline object.
         * @param stroke The stroke color of the polyline.
         * @param points The points of the polyline.
         */
        Polyline(const Color &stroke, const std::vector<Point> &points);
        /**
         * @brief Draws the polyline on the image.
         * @param img The image to draw on.
         */
        void draw(PNGImage &img) const override;
        /**
         * @brief Translates the polyline.
         * @param translation The translation point.
         */
        void translate(const Point &translation) override;
        /**
         * @brief Scales the polyline.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        void scale(const Point &origin, int scaling_factor) override;
        /**
         * @brief Rotates the polyline.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        void rotate(const Point &origin, int degrees) override;
        /**
         * @brief Applies the transformations to the polyline.
         */
        void applyTransformations() override;
        /**
         * @brief Sets the transformation origin for the polyline.
         * @param origin The transformation origin point.
         */
        void setTransformOrigin(const Point& origin) override;
        /**
         * @brief Adds a transformation to the polyline.
         * @param transformation The transformation function.
         */
        void addTransformation(const std::function<void()>& transformation) override;
        /**
         * @brief Clones the polyline.
         * @return A unique pointer to the cloned polyline.
         */
        virtual std::unique_ptr<SVGElement> clone() const override;

    private:
        Color stroke; ///< The stroke color of the polyline.
        std::vector<Point> points; ///< The points of the polyline. 
        Point transformOrigin; ///< The transformation origin point of the polyline.
    };

    /**
     * @brief Class representing a line in SVG.
     */
    class Line : public SVGElement
    {
    public:
        /**
         * @brief Constructs a Line object.
         * @param stroke The stroke color of the line.
         * @param start The start point of the line.
         * @param end The end point of the line.
         */
        Line(const Color &stroke, const Point &start, const Point &end);
        /**
         * @brief Draws the line on the image.
         * @param img The image to draw on.
         */
        void draw(PNGImage &img) const override;
        /**
         * @brief Translates the line.
         * @param translation The translation point.
         */
        void translate(const Point &translation) override;
        /**
         * @brief Scales the line.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        void scale(const Point &origin, int scaling_factor) override;
        /**
         * @brief Rotates the line.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        void rotate(const Point &origin, int degrees) override;
        /**
         * @brief Applies the transformations to the line.
         */
        void applyTransformations() override;
        /**
         * @brief Sets the transformation origin for the line.
         * @param origin The transformation origin point.
         */
        void setTransformOrigin(const Point& origin) override;
        /**
         * @brief Adds a transformation to the line.
         * @param transformation The transformation function.
         */
        void addTransformation(const std::function<void()>& transformation) override;
        /**
         * @brief Clones the line.
         * @return A unique pointer to the cloned line.
         */
        virtual std::unique_ptr<SVGElement> clone() const override;

    private:
        Color stroke; ///< The stroke color of the line.
        Point start; ///< The start point of the line.
        Point end; ///< The end point of the line.
        Point transformOrigin; ///< The transformation origin point of the line.
    };

    /**
     * @brief Class representing a polygon in SVG.
     */
    class Polygon : public SVGElement
    {
    public:
        /**
         * @brief Constructs a Polygon object.
         * @param fill The fill color of the polygon.
         * @param points The points of the polygon.
         */
        Polygon(const Color &fill, const std::vector<Point> &points);
        /**
         * @brief Draws the polygon on the image.
         * @param img The image to draw on.
         */
        void draw(PNGImage &img) const override;
        /**
         * @brief Translates the polygon.
         * @param translation The translation point.
         */
        void translate(const Point &translation) override;
        /**
         * @brief Scales the polygon.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        void scale(const Point &origin, int scaling_factor) override;
        /**
         * @brief Rotates the polygon.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        void rotate(const Point &origin, int degrees) override;
        /**
         * @brief Applies the transformations to the polygon.
         */
        void applyTransformations() override;
        /**
         * @brief Sets the transformation origin for the polygon.
         * @param origin The transformation origin point.
         */
        void setTransformOrigin(const Point& origin) override;
        /**
         * @brief Adds a transformation to the polygon.
         * @param transformation The transformation function.
         */
        void addTransformation(const std::function<void()>& transformation) override;
        /**
         * @brief Clones the polygon.
         * @return A unique pointer to the cloned polygon.
         */
        virtual std::unique_ptr<SVGElement> clone() const override;

    private:
        Color fill; ///< The fill color of the polygon.
        std::vector<Point> points; ///< The points of the polygon.
        Point transformOrigin; ///< The transformation origin point of the polygon.
    };
    
    /**
     * @brief Class representing a rectangle in SVG.
     */
    class Rectangle: public Polygon
    {
    public:
        /**
         * @brief Constructs a Rectangle object.
         * @param topLeft The top left point of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         * @param fill The fill color of the rectangle.
         */
        Rectangle(const Point &topLeft, const int &width,const int &height, const Color &fill);
    };
    
    /**
     * @brief Class representing a group of SVG elements.
     */
    class SVGGroup : public SVGElement
    {
    public:
        SVGGroup(); ///< Default constructor.
        std::vector<std::unique_ptr<SVGElement>> elements;  ///< The elements in the group.
        /**
         * @brief Draws the group on the image.
         * @param img The image to draw on.
         */
        void draw(PNGImage &img) const override;
        /**
         * @brief Translates the group.
         * @param translation The translation point.
         */
        void translate(const Point &translation) override;
        /**
         * @brief Scales the group.
         * @param origin The origin point for scaling.
         * @param scaling_factor The scaling factor.
         */
        void scale(const Point &origin, int scaling_factor) override;
        /**
         * @brief Rotates the group.
         * @param origin The origin point for rotation.
         * @param degrees The degrees of rotation.
         */
        void rotate(const Point &origin, int degrees) override;
        /**
         * @brief Applies the transformations to the group.
         */ 
        void applyTransformations() override;
        /**
         * @brief Sets the transformation origin for the group.
         * @param origin The transformation origin point.
         */
        void setTransformOrigin(const Point& origin) override;
        /**
         * @brief Adds a transformation to the group.
         * @param transformation The transformation function.
         */
        void addTransformation(const std::function<void()>& transformation) override;
        /**
         * @brief Clones the group.
         * @return A unique pointer to the cloned group.
         */
        virtual std::unique_ptr<SVGElement> clone() const override;
        /**
         * @brief Adds an element to the group.
         * @param element The element to add.
         */
        void addElement(std::unique_ptr<SVGElement> element);

    private:
        Point transformOrigin; ///< The transformation origin point of the group.
    };
}

#endif


