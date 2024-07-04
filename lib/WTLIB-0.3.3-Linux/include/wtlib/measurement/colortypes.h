#ifndef WTL_COLORTYPES_H
#define WTL_COLORTYPES_H

#include <array>
#include <cstdint>

namespace wtl {

struct YCbCr
{
	uint8_t Y, Cb, Cr;

    bool operator==(const YCbCr& other) const = default;
};

struct RGB
{
	uint8_t R, G, B;

    bool operator==(const RGB& other) const = default;
};

typedef std::array<RGB, 256> paletteRGB256;
typedef std::array<YCbCr, 256> paletteYcBCr256;

static YCbCr YCbCrfromRGB(const RGB& rgb)
{
    YCbCr res{};
    int Y, Cb, Cr;
    Y = (int)(rgb.R * 0.299 + (double)rgb.G * 0.587 + (double)rgb.B * 0.114);
    Cb = (int)(rgb.R * (-0.16874) - (double)rgb.G * 0.33126 +
                (double)rgb.B * 0.5 + 128);
    Cr = (int)(rgb.R * 0.5 - (double)rgb.G * 0.418689 -
                (double)rgb.B * 0.08131 + 128);

    res.Y = Y > 255 ? 255 : Y < 0 ? 0 : Y;
    res.Cb = Cb > 255 ? 255 : Cb < 0 ? 0 : Cb;
    res.Cr = Cr > 255 ? 255 : Cr < 0 ? 0 : Cr;
    return res;
}

static RGB RGBfromYcRcB(const YCbCr& ycbcr)
{
    int R, G, B;
    RGB res{};
    R = (int)(ycbcr.Y + 1.40200 * ((double)ycbcr.Cb - 128));
    G = (int)(ycbcr.Y - 0.34414 * ((double)ycbcr.Cr - 128) -
               0.71414 * ((double)ycbcr.Cb - 128));
    B = (int)(ycbcr.Y + 1.77200 * ((double)ycbcr.Cr - 128));

    res.R = R > 255 ? 255 : R < 0 ? 0 : R;
    res.G = G > 255 ? 255 : G < 0 ? 0 : G;
    res.B = B > 255 ? 255 : B < 0 ? 0 : B;
    return res;
}
} // namespace wtl

#endif // WTL_RGB_H
