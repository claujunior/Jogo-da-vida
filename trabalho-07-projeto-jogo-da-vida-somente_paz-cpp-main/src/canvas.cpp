/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.hpp"

namespace life {
/*!
 * Deep copy of the canvas.
 * @param clone The object we are copying from.
 */
Canvas::Canvas(const Canvas& clone) {
    m_width = clone.m_width;
    m_height = clone.m_height;
    m_block_size = clone.m_block_size;
    m_pixels = clone.m_pixels;
   
}
const size_t Canvas::offset(const coord_t x,const coord_t y){ 
    return ((y*image_depth*m_block_size*m_width*m_block_size)+(x*image_depth*m_block_size));
}
/*!
 * @param source The object we are copying information from.
 * @return A reference to the `this` object.
 */
Canvas& Canvas::operator=(const Canvas& source) { return *this; }

/// Assigns a black color to the whole image.
void Canvas::clear(const Color& color) {
     
    for(int i = 0;i<m_pixels.size();i = i + image_depth){
        m_pixels[i] = color.channels[Color::R]; 
    }
    for(int i = 1;i<m_pixels.size();i = i + image_depth){
        m_pixels[i] = color.channels[Color::G]; 
    }
    for(int i = 2;i<m_pixels.size();i = i + image_depth){
        m_pixels[i] = color.channels[Color::B]; 
    }
    for(int i = 3;i<m_pixels.size();i = i + image_depth){
        m_pixels[i] = 255; 
    }
}

/*!
 * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
 * @param x The (virtual) X coordinate of the pixel we want to know the color of.
 * @param x The (virtual) Y coordinate of the pixel we want to know the color of.
 * @return The pixel color.
 */
Color Canvas::pixel(coord_t x, coord_t y) const { return BLACK; }

/*!
 * Draw a pixel on the virtual image at the requested coordinate.
 *
 * @note Nothing is done if the  pixel coordinate is located outside the canvas.
 * @param x The (virtual) X coordinate of the pixel we want to know the color of.
 * @param x The (virtual) Y coordinate of the pixel we want to know the color of.
 * @param c The color.
 */
void Canvas::pixel(coord_t x, coord_t y, const Color& c) {

    size_t lugar = offset(x,y);   
    size_t k = 0;
 
    auto p=lugar;
   while(k!=m_block_size){
    size_t i = p;
    size_t j = i + 1;
    size_t t = j+1;
    size_t blo = 0;
    while(blo<(m_block_size)){
    m_pixels[i] = c.channels[Color::R];
    i = i + image_depth;
    m_pixels[j] = c.channels[Color::G];
    j = j + image_depth;
    m_pixels[t] = c.channels[Color::B];
    m_pixels[t+1] = 255;
    t = t + image_depth;
    blo++;
    
    }
    k++;
    p = p + image_depth*m_block_size*m_width;
   }
  
}

}  // namespace life
//================================[ canvas.cpp ]================================//
