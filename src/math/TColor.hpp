#pragma once
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "../CeramicsMacro.h"
#include "TMathUtils.hpp"
CERAMICS_NAMESPACE_BEGIN
template <class T>
struct THSL
{
    T h;
    T s;
    T l;
};
template <class T>
struct TColor
{
    typedef enum
        {
            aliceblue = 0xF0F8FF,
            antiquewhite = 0xFAEBD7,
            aqua = 0x00FFFF,
            aquamarine = 0x7FFFD4,
            azure = 0xF0FFFF,
            beige = 0xF5F5DC,
            bisque = 0xFFE4C4,
            black = 0x000000,
            blanchedalmond = 0xFFEBCD,
            blue = 0x0000FF,
            blueviolet = 0x8A2BE2,
            brown = 0xA52A2A,
            burlywood = 0xDEB887,
            cadetblue = 0x5F9EA0,
            chartreuse = 0x7FFF00,
            chocolate = 0xD2691E,
            coral = 0xFF7F50,
            cornflowerblue = 0x6495ED,
            cornsilk = 0xFFF8DC,
            crimson = 0xDC143C,
            cyan = 0x00FFFF,
            darkblue = 0x00008B,
            darkcyan = 0x008B8B,
            darkgoldenrod = 0xB8860B,
            darkgray = 0xA9A9A9,
            darkgreen = 0x006400,
            darkgrey = 0xA9A9A9,
            darkkhaki = 0xBDB76B,
            darkmagenta = 0x8B008B,
            darkolivegreen = 0x556B2F,
            darkorange = 0xFF8C00,
            darkorchid = 0x9932CC,
            darkred = 0x8B0000,
            darksalmon = 0xE9967A,
            darkseagreen = 0x8FBC8F,
            darkslateblue = 0x483D8B,
            darkslategray = 0x2F4F4F,
            darkslategrey = 0x2F4F4F,
            darkturquoise = 0x00CED1,
            darkviolet = 0x9400D3,
            deeppink = 0xFF1493,
            deepskyblue = 0x00BFFF,
            dimgray = 0x696969,
            dimgrey = 0x696969,
            dodgerblue = 0x1E90FF,
            firebrick = 0xB22222,
            floralwhite = 0xFFFAF0,
            forestgreen = 0x228B22,
            fuchsia = 0xFF00FF,
            gainsboro = 0xDCDCDC,
            ghostwhite = 0xF8F8FF,
            gold = 0xFFD700,
            goldenrod = 0xDAA520,
            gray = 0x808080,
            green = 0x008000,
            greenyellow = 0xADFF2F,
            grey = 0x808080,
            honeydew = 0xF0FFF0,
            hotpink = 0xFF69B4,
            indianred = 0xCD5C5C,
            indigo = 0x4B0082,
            ivory = 0xFFFFF0,
            khaki = 0xF0E68C,
            lavender = 0xE6E6FA,
            lavenderblush = 0xFFF0F5,
            lawngreen = 0x7CFC00,
            lemonchiffon = 0xFFFACD,
            lightblue = 0xADD8E6,
            lightcoral = 0xF08080,
            lightcyan = 0xE0FFFF,
            lightgoldenrodyellow = 0xFAFAD2,
            lightgray = 0xD3D3D3,
            lightgreen = 0x90EE90,
            lightgrey = 0xD3D3D3,
            lightpink = 0xFFB6C1,
            lightsalmon = 0xFFA07A,
            lightseagreen = 0x20B2AA,
            lightskyblue = 0x87CEFA,
            lightslategray = 0x778899,
            lightslategrey = 0x778899,
            lightsteelblue = 0xB0C4DE,
            lightyellow = 0xFFFFE0,
            lime = 0x00FF00,
            limegreen = 0x32CD32,
            linen = 0xFAF0E6,
            magenta = 0xFF00FF,
            maroon = 0x800000,
            mediumaquamarine = 0x66CDAA,
            mediumblue = 0x0000CD,
            mediumorchid = 0xBA55D3,
            mediumpurple = 0x9370DB,
            mediumseagreen = 0x3CB371,
            mediumslateblue = 0x7B68EE,
            mediumspringgreen = 0x00FA9A,
            mediumturquoise = 0x48D1CC,
            mediumvioletred = 0xC71585,
            midnightblue = 0x191970,
            mintcream = 0xF5FFFA,
            mistyrose = 0xFFE4E1,
            moccasin = 0xFFE4B5,
            navajowhite = 0xFFDEAD,
            navy = 0x000080,
            oldlace = 0xFDF5E6,
            olive = 0x808000,
            olivedrab = 0x6B8E23,
            orange = 0xFFA500,
            orangered = 0xFF4500,
            orchid = 0xDA70D6,
            palegoldenrod = 0xEEE8AA,
            palegreen = 0x98FB98,
            paleturquoise = 0xAFEEEE,
            palevioletred = 0xDB7093,
            papayawhip = 0xFFEFD5,
            peachpuff = 0xFFDAB9,
            peru = 0xCD853F,
            pink = 0xFFC0CB,
            plum = 0xDDA0DD,
            powderblue = 0xB0E0E6,
            purple = 0x800080,
            rebeccapurple = 0x663399,
            red = 0xFF0000,
            rosybrown = 0xBC8F8F,
            royalblue = 0x4169E1,
            saddlebrown = 0x8B4513,
            salmon = 0xFA8072,
            sandybrown = 0xF4A460,
            seagreen = 0x2E8B57,
            seashell = 0xFFF5EE,
            sienna = 0xA0522D,
            silver = 0xC0C0C0,
            skyblue = 0x87CEEB,
            slateblue = 0x6A5ACD,
            slategray = 0x708090,
            slategrey = 0x708090,
            snow = 0xFFFAFA,
            springgreen = 0x00FF7F,
            steelblue = 0x4682B4,
            tan = 0xD2B48C,
            teal = 0x008080,
            thistle = 0xD8BFD8,
            tomato = 0xFF6347,
            turquoise = 0x40E0D0,
            violet = 0xEE82EE,
            wheat = 0xF5DEB3,
            white = 0xFFFFFF,
            whitesmoke = 0xF5F5F5,
            yellow = 0xFFFF00,
            yellowgreen = 0x9ACD32
        } ColorKeywords;
    typedef T value_type;
    typedef TColor<T> type;
    typedef std::uint32_t hex_t;
    typedef std::uint8_t byte_t;
    typedef TMathUtils<T> MathUtils;
    typedef THSL<T> HSL;
    T r = T(0);
    T g = T(0);
    T b = T(0);

    TColor() {}
    TColor(std::string style) { this->set(style); }
    TColor(hex_t hex) { this->set(hex); }
    TColor(T r, T g, T b) { this->setRGB(r, g, b); }
    type &set(std::string value) { return this->setStyle(value); }
    type &set(hex_t value) { return this->setHex(value); }
    type &set(const type &value) { return this->copy(value); }
    type &setScalar(byte_t scalar)
    {
        this->r = scalar;
        this->g = scalar;
        this->b = scalar;
        return *this;
    }
    type &setHex(hex_t hex)
    {
        this->r = T(hex >> 16 & 255) / 255;
        this->g = T(hex >> 8 & 255) / 255;
        this->b = T(hex & 255) / 255;
        return *this;
    }
    type &setRGB(T r, T g, T b)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        return *this;
    }
    type &setHSL(T h, T s, T l)
    {
        // h,s,l ranges are in 0.0 - 1.0
        h = MathUtils::euclideanModulo(h, T(1));
        s = MathUtils::clamp(s, T(0), T(1));
        l = MathUtils::clamp(l, T(0), T(1));
        if (s == T(0))
        {
            this->r = this->g = this->b = l;
        }
        else
        {
            auto p = l <= 0.5 ? l * (1 + s) : l + s - (l * s);
            auto q = (2 * l) - p;
            this->r = hue2rgb(q, p, h + 1 / 3);
            this->g = hue2rgb(q, p, h);
            this->b = hue2rgb(q, p, h - 1 / 3);
        }
        return *this;
    }
    type &setStyle(std::string style)
    {
        std::regex reg("^((?:rgb|hsl)a?)\\(\\s*([^\\)]*)\\)");
        std::smatch m;
        if (std::regex_search(style, m, reg))
        {
            // if (m =.exec(style)) {
            // rgb / hsl
            std::regex color_reg;
            std::smatch color;
            std::string name = m[1];
            std::string components = m[2];
            if (name == "rgb" || name == "rgba")
            {
                color_reg =
                    "^(\\d+)\\s*,\\s*(\\d+)\\s*,\\s*(\\d+)\\s*(,\\s*([0-9]*\\.?"
                    "[0-9]+)\\s*)?$";
                if (std::regex_search(components, color, color_reg))
                {
                    // rgb(255,0,0) rgba(255,0,0,0.5)
                    this->r =
                        std::min(255, std::stoi(color[1], 0, 10)) / T(255);
                    this->g =
                        std::min(255, std::stoi(color[2], 0, 10)) / T(255);
                    this->b =
                        std::min(255, std::stoi(color[3], 0, 10)) / T(255);

                    handleAlpha(color[5]);

                    return *this;
                }
                color_reg =
                    "^(\\d+)\\%\\s*,\\s*(\\d+)\\%\\s*,\\s*(\\d+)\\%\\s*(,\\s*(["
                    "0-9]*\\.?[0-9]+)\\s*)?$";
                if (std::regex_search(components, color, color_reg))
                {
                    // rgb(100%,0%,0%)
                    // rgba(100%,0%,0%,0.5)
                    this->r =
                        std::min(100, std::stoi(color[1], 0, 10)) / T(100);
                    this->g =
                        std::min(100, std::stoi(color[2], 0, 10)) / T(100);
                    this->b =
                        std::min(100, std::stoi(color[3], 0, 10)) / T(100);
                    handleAlpha(color[5]);
                    return *this;
                }
            }
            else if (name == "hsl" || name == "hsla")
            {
                color_reg =
                    "^([0-9]*\\.?[0-9]+)\\s*,\\s*(\\d+)\\%\\s*,\\s*(\\d+)\\%"
                    "\\s*(,\\s*([0-9]*\\.?[0-9]+)\\s*)?$";
                if (std::regex_search(components, color, color_reg))
                {
                    // hsl(120,50%,50%)
                    // hsla(120,50%,50%,0.5)
                    auto h = std::stof(color[1]) / T(360);
                    auto s = std::stoi(color[2], 0, 10) / T(100);
                    auto l = std::stoi(color[3], 0, 10) / T(100);
                    handleAlpha(color[5]);
                    return this->setHSL(h, s, l);
                }
            }
        }
        else
        {
            reg = "^#([A-Fa-f0-9]+)$";
            // if (m = .exec(style)) {
            if (std::regex_search(style, m, reg))
            {
                // hex color
                std::string hex = m[1];
                auto size = hex.size();
                if (size == 3)
                {
                    // #ff0
                    std::ostringstream ss;
                    ss<<hex[0]<<hex[0];
                    this->r = std::stoi(ss.str(), 0, 16) / T(255);
                    ss.clear();
                    ss<<hex[1]<<hex[1];
                    this->r = std::stoi(ss.str(), 0, 16) / T(255);
                    ss.clear();
                    ss<<hex[2]<<hex[2];
                    this->r = std::stoi(ss.str(), 0, 16) / T(255);
                    return *this;
                }
                else if (size == 6)
                {
                    // #ff0000
                    this->r = std::stoi(hex.substr(0,2), 0, 16) / T(255);
                    this->g = std::stoi(hex.substr(2,2), 0, 16) / T(255);
                    this->b = std::stoi(hex.substr(4,2), 0, 16) / T(255);
                    return *this;
                }
            }
        }
        if (style.size() > 0)
        {
            return this->setColorName(style);
        }
        return *this;
    }
    type &setColorName(ColorKeywords style)
    {
        hex_t hex = hex_t(style);
        this->setHex(hex);
        return *this;
    }
    type clone() { return *this; }
    type &operator=(const type &color) { return this->copy(color); }
    type &copy(const type &color)
    {
        this->r = color.r;
        this->g = color.g;
        this->b = color.b;
        return *this;
    }
    type &copyGammaToLinear(const type &color, T gammaFactor = T(2))
    {
        this->r = std::pow(color.r, gammaFactor);
        this->g = std::pow(color.g, gammaFactor);
        this->b = std::pow(color.b, gammaFactor);
        return *this;
    }
    type &copyLinearToGamma(const type &color, T gammaFactor = T(2))
    {
        auto safeInverse =
            (gammaFactor > T(0)) ? (T(1.0) / gammaFactor) : T(1.0);
        this->r = std::pow(color.r, safeInverse);
        this->g = std::pow(color.g, safeInverse);
        this->b = std::pow(color.b, safeInverse);
        return *this;
    }
    type &convertGammaToLinear(T gammaFactor)
    {
        this->copyGammaToLinear(*this, gammaFactor);
        return *this;
    }
    type &convertLinearToGamma(T gammaFactor)
    {
        this->copyLinearToGamma(*this, gammaFactor);
        return *this;
    }
    type &copySRGBToLinear(const type &color)
    {
        this->r = SRGBToLinear(color.r);
        this->g = SRGBToLinear(color.g);
        this->b = SRGBToLinear(color.b);
        return *this;
    }
    type &copyLinearToSRGB(const type &color)
    {
        this->r = LinearToSRGB(color.r);
        this->g = LinearToSRGB(color.g);
        this->b = LinearToSRGB(color.b);
        return *this;
    }
    type &convertSRGBToLinear()
    {
        this->copySRGBToLinear(*this);
        return *this;
    }
    type &convertLinearToSRGB()
    {
        this->copyLinearToSRGB(this);
        return *this;
    }
    hex_t getHex()
    {
        return hex_t(this->r * 255) << 16 ^ hex_t(this->g * 255) << 8 ^
            hex_t(this->b * 255) << 0;
    }
    std::string getHexS()
    {
        std::ostringstream ss;
        ss <<std::setw(6)<<std::right <<std::setfill('0')<<std::hex<<this->getHex();
        return ss.str();
    }
    HSL getHSL()
    {
        HSL target;
        return getHSL(target);
    }
    HSL getHSL(HSL &target)
    {
        // h,s,l ranges are in 0.0 - 1.0
        auto r = this->r, g = this->g, b = this->b;
        auto max = std::max(r, g, b);
        auto min = std::min(r, g, b);
        T hue, saturation;
        auto lightness = (min + max) / 2.0;
        if (min == max)
        {
            hue = 0;
            saturation = 0;
        }
        else
        {
            auto delta = max - min;
            saturation = lightness <= 0.5 ? delta / (max + min)
                : delta / (2 - max - min);
            switch (max)
            {
            case r:
                hue = (g - b) / delta + (g < b ? 6 : 0);
                break;
            case g:
                hue = (b - r) / delta + 2;
                break;
            case b:
                hue = (r - g) / delta + 4;
                break;
            }
            hue /= 6;
        }
        target.h = hue;
        target.s = saturation;
        target.l = lightness;
        return target;
    }
    std::string getStyle()
    {
        std::ostringstream ss;
        ss<<"rgb(";
        ss<<byte_t(this->r * 255);
        ss<<',';
        ss<<byte_t(this->g * 255);
        ss<<',';
        ss<<byte_t(this->b * 255);
        ss<<')';
        return ss.str();
    }
    type &offsetHSL(T h, T s, T l)
    {
        HSL _hslA;
        this->getHSL(_hslA);
        _hslA.h += h;
        _hslA.s += s;
        _hslA.l += l;
        this->setHSL(_hslA.h, _hslA.s, _hslA.l);
        return *this;
    }
    type &add(const type &color)
    {
        this->r += color.r;
        this->g += color.g;
        this->b += color.b;
        return *this;
    }
    type &addColors(const type &color1, const type &color2)
    {
        this->r = color1.r + color2.r;
        this->g = color1.g + color2.g;
        this->b = color1.b + color2.b;
        return *this;
    }
    type &addScalar(T s)
    {
        this->r += s;
        this->g += s;
        this->b += s;
        return *this;
    }
    type &sub(const type &color)
    {
        this->r = std::max(0, this->r - color.r);
        this->g = std::max(0, this->g - color.g);
        this->b = std::max(0, this->b - color.b);
        return *this;
    }
    type &multiply(const type &color)
    {
        this->r *= color.r;
        this->g *= color.g;
        this->b *= color.b;
        return *this;
    }
    type &multiplyScalar(const type &s)
    {
        this->r *= s;
        this->g *= s;
        this->b *= s;
        return *this;
    }
    type &lerp(const type &color, T alpha)
    {
        this->r += (color.r - this->r) * alpha;
        this->g += (color.g - this->g) * alpha;
        this->b += (color.b - this->b) * alpha;
        return *this;
    }
    type &lerpHSL(const type &color, T alpha)
    {
        HSL _hslA,_hslB;
        this->getHSL(_hslA);
        color.getHSL(_hslB);
        auto h = MathUtils::lerp(_hslA.h, _hslB.h, alpha);
        auto s = MathUtils::lerp(_hslA.s, _hslB.s, alpha);
        auto l = MathUtils::lerp(_hslA.l, _hslB.l, alpha);
        this->setHSL(h, s, l);
        return *this;
    }
    bool operator==(const type &c) { return equals(c); }
    bool equals(const type &c)
    {
        return (c.r == this->r) && (c.g == this->g) && (c.b == this->b);
    }
    // TODO : edge check?
    type &fromArray(T array[], size_t offset = 0)
    {
        this->r = array[offset];
        this->g = array[offset + 1];
        this->b = array[offset + 2];
        return *this;
    }
    // TODO : edge check?
    T *toArray(T *array, size_t offset = 0)
    {
        // if ( array === undefined ) array = [];
        array[offset] = this->r;
        array[offset + 1] = this->g;
        array[offset + 2] = this->b;
        return array;
    }
    // type &fromBufferAttribute( attribute, index ) {
    // 	this->r = attribute.getX( index );
    // 	this->g = attribute.getY( index );
    // 	this->b = attribute.getZ( index );
    // 	if ( attribute.normalized === true ) {
    // 		// assuming Uint8Array
    // 		this->r /= 255;
    // 		this->g /= 255;
    // 		this->b /= 255;
    // 	}
    // 	return *this;
    // }
    static float hue2rgb(float p, float q, float t)
    {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1 / 6) return p + (q - p) * 6 * t;
        if (t < 1 / 2) return q;
        if (t < 2 / 3) return p + (q - p) * 6 * (2 / 3 - t);
        return p;
    }
    static float SRGBToLinear(float c)
    {
        return (c < 0.04045) ? c * 0.0773993808
            : std::pow(c * 0.9478672986 + 0.0521327014, 2.4);
    }
    static float LinearToSRGB(float c)
    {
        return (c < 0.0031308) ? c * 12.92
            : 1.055 * (std::pow(c, 0.41666)) - 0.055;
    }
    static void handleAlpha(std::string string)
    {
        if (std::stof(string) < 1) {
            // console.warn('CERAMICS.Color: Alpha component of ' + style + ' will
            // be ignored.');
        }
    }
};
CERAMICS_NAMESPACE_END
