//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

/*! 
    * @brief Namespace svg
    * This namespace contains the classes and functions to read and convert SVG files to PNG files.
*/
namespace svg
{
    /*! 
        * @brief Class SVGElement
        * This class is an abstract class that represents an SVG element..
    */
    class SVGElement
    {
    public:
        /*! 
            * @brief Constructor of SVGElement
            * This constructor initializes the SVGElement with the default values.
        */
        SVGElement();
        /*! 
            * @brief Destructor of SVGElement
            * This destructor is used to destroy the SVGElement object.
        */
        virtual ~SVGElement();
        /*! 
            * @brief draw
            * This function is used to draw the SVGElement on the PNGImage.
            * @param img PNGImage object
        */
        virtual void draw(PNGImage &img) const = 0;
        /*! 
            * @brief translate
            * This function is used to translate the SVGElement.
            * @param translation Point object
        */
        virtual void translate(const Point &translation) = 0;
        /*! 
            * @brief scale
            * This function is used to scale the SVGElement.
            * @param origin Point object
            * @param scaling_factor int value
        */
        virtual void scale(const Point &origin, int scaling_factor) = 0;
        /*! 
            * @brief rotate
            * This function is used to rotate the SVGElement.
            * @param origin Point object
            * @param degrees int value
        */
        virtual void rotate(const Point &origin, int degrees) = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    /*! 
        * @brief readSVG
        * This function is used to read the SVG file and store the dimensions and SVG elements.
        * @param svg_file string object
        * @param dimensions Point object
        * @param svg_elements vector of SVGElement pointers
    */
    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    /*!
        * @brief convert
        * This function is used to convert the SVG file to PNG file.
        * @param svg_file string object
        * @param png_file string object
    */
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    /*!
        * @brief Class Ellipse
        * This class is used to represent an Ellipse.
    */
    class Ellipse : public SVGElement
    {
    public:
        /*!
            * @brief Constructor of Ellipse
            * This constructor initializes the Ellipse with the default values.
        */
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        /*!
            * @brief draw
            * This function is used to draw the Ellipse on the PNGImage.
            * @param img PNGImage object
        */
        void draw(PNGImage &img) const override;
        /*!
            * @brief translate
            * This function is used to translate the Ellipse.
            * @param translation Point object
        */
        void translate(const Point &translation) override;
        /*!
            * @brief scale
            * This function is used to scale the Ellipse.
            * @param origin Point object
            * @param scaling_factor int value
        */
        void scale(const Point &origin, int scaling_factor) override;
        /*!
            * @brief rotate
            * This function is used to rotate the Ellipse.
            * @param origin Point object
            * @param degrees int value
        */
        void rotate(const Point &origin, int degrees) override;

    private:
        /*!
            * @brief fill
            * This variable stores the fill color of the Ellipse.
        */
        Color fill;
        /*!
            * @brief center
            * This variable stores the center of the Ellipse.
            * The center is a Point object that stores the x and y coordinates.
        */
        Point center;
        /*!
            * @brief radius
            * This variable stores the radius of the Ellipse.
            * The radius is a Point object that stores the x and y coordinates.
        */
        Point radius;
    };

    /*!
        * @brief Class Circle
        * This class is used to represent a Circle.
    */
    class Circle : public SVGElement
    {
    public:
        /*!
            * @brief Constructor of Circle
            * This constructor initializes the Circle with the default values.
        */
        Circle(const Color &fill, const Point &center, int radius);
        /*!
            * @brief draw
            * This function is used to draw the Circle on the PNGImage.
            * @param img PNGImage object
        */
        void draw(PNGImage &img) const override;
        /*!
            * @brief translate
            * This function is used to translate the Circle.
            * @param translation Point object
        */
        void translate(const Point &translation) override;
        /*!
            * @brief scale
            * This function is used to scale the Circle.
            * @param origin Point object
            * @param scaling_factor int value
        */
        void scale(const Point &origin, int scaling_factor) override;
        /*!
            * @brief rotate
            * This function is used to rotate the Circle.
            * @param origin Point object
            * @param degrees int value
        */
        void rotate(const Point &origin, int degrees) override;

        void setTransformOrigin(const Point& origin);
        void addTransformation(const std::function<void()>& transformation);
        void applyTransformations();

    private:
        /*!
            * @brief fill
            * This variable stores the fill color of the Circle.
        */
        Color fill;
        /*!
            * @brief center
            * This variable stores the center of the Circle.
            * The center is a Point object that stores the x and y coordinates.
        */
        Point center;
        /*!
            * @brief radius
            * This variable stores the radius of the Circle.
        */
        int radius;

        Point transformOrigin;
        std::vector<std::function<void()>> transformations;
    };

    /*!
        * @brief Class Polyline
        * This class is used to represent a Polyline.
    */
    class Polyline : public SVGElement
    {
    public:
        /*!
            * @brief Constructor of Polyline
            * This constructor initializes the Polyline with the default values.
        */
        Polyline(const Color& stroke, const std::vector<Point>& points);
        /*!
            * @brief draw
            * This function is used to draw the Polyline on the PNGImage.
            * @param img PNGImage object
        */
        void draw(PNGImage &img) const override;
        /*!
            * @brief translate
            * This function is used to translate the Polyline.
            * @param translation Point object
        */
        void translate(const Point &translation) override;
        /*!
            * @brief scale
            * This function is used to scale the Polyline.
            * @param origin Point object
            * @param scaling_factor int value
        */
        void scale(const Point &origin, int scaling_factor) override;
        /*!
            * @brief rotate
            * This function is used to rotate the Polyline.
            * @param origin Point object
            * @param degrees int value
        */
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations();
        void setTransformOrigin(const Point& origin);
        void addTransformation(const std::function<void()>& transformation);

    private:
        /*!
            * @brief stroke
            * This variable stores the stroke color of the Polyline.
        */
        Color stroke;
        /*!
            * @brief points
            * This variable stores the points of the Polyline.
            * The points is a vector of Point objects that stores the x and y coordinates.
        */
        std::vector<Point> points;

        Point transformOrigin;
        std::vector<std::function<void()>> transformations;
    };

    /*!
        * @brief Class Line
        * This class is used to represent a Line.
    */
    class Line : public SVGElement {
    public:
        /*!
            * @brief Constructor of Line
            * This constructor initializes the Line with the default values.
        */
        Line(const Color& stroke, const Point& start, const Point& end);
        /*!
            * @brief draw
            * This function is used to draw the Line on the PNGImage.
            * @param img PNGImage object
        */
        void draw(PNGImage& img) const override;
        /*!
            * @brief translate
            * This function is used to translate the Line.
            * @param translation Point object
        */
        void translate(const Point &translation) override;
        /*!
            * @brief scale
            * This function is used to scale the Line.
            * @param origin Point object
            * @param scaling_factor int value
        */
        void scale(const Point &origin, int scaling_factor) override;
        /*!
            * @brief rotate
            * This function is used to rotate the Line.
            * @param origin Point object
            * @param degrees int value
        */
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations();
        void setTransformOrigin(const Point& origin);
        void addTransformation(const std::function<void()>& transformation);

    private:
        /*!
            * @brief stroke
            * This variable stores the stroke color of the Line.
        */
        Color stroke;
        /*!
            * @brief start
            * This variable stores the start point of the Line
            * The start is a Point object that stores the x and y coordinates.
        */
        Point start;
        /*!
            * @brief end
            * This variable stores the end point of the Line.
            * The end is a Point object that stores the x and y coordinates.
        */
        Point end;

        Point transformOrigin;
        std::vector<std::function<void()>> transformations;
    };

    /*!
        * @brief Class Polygon
        * This class is used to represent a Polygon.
    */
    class Polygon : public SVGElement {
    public:
        /*!
            * @brief Constructor of Polygon
            * This constructor initializes the Polygon with the default values.
        */
        Polygon(const Color &fill, const std::vector<Point> &points);
        /*!
            * @brief draw
            * This function is used to draw the Polygon on the PNGImage.
            * @param img PNGImage object
        */
        void draw(PNGImage& img) const override;
        /*!
            * @brief translate
            * This function is used to translate the Polygon.
            * @param translation Point object
        */
        void translate(const Point &translation) override;
        /*!
            * @brief scale
            * This function is used to scale the Polygon.
            * @param origin Point object
            * @param scaling_factor int value
        */
        void scale(const Point &origin, int scaling_factor) override;
        /*!
            * @brief rotate
            * This function is used to rotate the Polygon.
            * @param origin Point object
            * @param degrees int value
        */
        void rotate(const Point &origin, int degrees) override;

        void applyTransformations();
        void setTransformOrigin(const Point& origin);
        void addTransformation(const std::function<void()>& transformation);

    private:
        /*!
            * @brief fill
            * This variable stores the fill color of the Polygon.
        */
        Color fill;
        /*!
            * @brief points
            * This variable stores the points of the Polygon.
            * The points is a vector of Point objects that stores the x and y coordinates.
        */
        std::vector<Point> points;

        Point transformOrigin;
        std::vector<std::function<void()>> transformations;
    };

    /*!
        * @brief Class Rectangle
        * This class is used to represent a Rectangle.
    */
    class Rectangle : public SVGElement
    {
    public:
        /*!
            * @brief Constructor of Rectangle
            * This constructor initializes the Rectangle with the default values.
        */
        Rectangle(const Color &fill, const Point &upper_left, int width, int height);
        /*!
            * @brief draw
            * This function is used to draw the Rectangle on the PNGImage.
            * @param img PNGImage object
        */
        void draw(PNGImage &img) const override;
        /*!
            * @brief translate
            * This function is used to translate the Rectangle.
            * @param translation Point object
        */
        void translate(const Point &translation) override;
        /*!
            * @brief scale
            * This function is used to scale the Rectangle.
            * @param origin Point object
            * @param scaling_factor int value
        */
        void scale(const Point &origin, int scaling_factor) override;
        /*!
            * @brief rotate
            * This function is used to rotate the Rectangle.
            * @param origin Point object
            * @param degrees int value
        */
        void rotate(const Point &origin, int degrees) override;

    private:
        /*!
            * @brief fill
            * This variable stores the fill color of the Rectangle.
        */
        Color fill;
        /*!
            * @brief upper_left
            * This variable stores the upper left point of the Rectangle.
            * The upper_left is a Point object that stores the x and y coordinates.
        */
        Point upper_left;
        /*!
            * @brief width
            * This variable stores the width of the Rectangle.
        */
        int width;
        /*!
            * @brief height
            * This variable stores the height of the Rectangle.
        */
        int height;
    };

}
#endif