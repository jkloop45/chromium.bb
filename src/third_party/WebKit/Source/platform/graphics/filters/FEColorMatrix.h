/*
 * Copyright (C) 2004, 2005, 2006, 2007 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005 Rob Buis <buis@kde.org>
 * Copyright (C) 2005 Eric Seidel <eric@webkit.org>
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef FEColorMatrix_h
#define FEColorMatrix_h

#include "platform/graphics/filters/Filter.h"
#include "platform/graphics/filters/FilterEffect.h"
#include "wtf/Vector.h"

namespace WebCore {

enum ColorMatrixType {
    FECOLORMATRIX_TYPE_UNKNOWN          = 0,
    FECOLORMATRIX_TYPE_MATRIX           = 1,
    FECOLORMATRIX_TYPE_SATURATE         = 2,
    FECOLORMATRIX_TYPE_HUEROTATE        = 3,
    FECOLORMATRIX_TYPE_LUMINANCETOALPHA = 4
};

class PLATFORM_EXPORT FEColorMatrix : public FilterEffect {
public:
    static PassRefPtr<FEColorMatrix> create(Filter*, ColorMatrixType, const Vector<float>&);

    ColorMatrixType type() const;
    bool setType(ColorMatrixType);

    const Vector<float>& values() const;
    bool setValues(const Vector<float>&);

    virtual PassRefPtr<SkImageFilter> createImageFilter(SkiaImageFilterBuilder*) OVERRIDE;

    virtual TextStream& externalRepresentation(TextStream&, int indention) const OVERRIDE;

    static inline void calculateSaturateComponents(float* components, float value);
    static inline void calculateHueRotateComponents(float* components, float value);

private:
    FEColorMatrix(Filter*, ColorMatrixType, const Vector<float>&);

    virtual void applySoftware() OVERRIDE;
    virtual bool applySkia() OVERRIDE;

    virtual bool affectsTransparentPixels() OVERRIDE;

    ColorMatrixType m_type;
    Vector<float> m_values;
};

inline void FEColorMatrix::calculateSaturateComponents(float* components, float value)
{
    components[0] = (0.213 + 0.787 * value);
    components[1] = (0.715 - 0.715 * value);
    components[2] = (0.072 - 0.072 * value);
    components[3] = (0.213 - 0.213 * value);
    components[4] = (0.715 + 0.285 * value);
    components[5] = (0.072 - 0.072 * value);
    components[6] = (0.213 - 0.213 * value);
    components[7] = (0.715 - 0.715 * value);
    components[8] = (0.072 + 0.928 * value);
}

inline void FEColorMatrix::calculateHueRotateComponents(float* components, float value)
{
    float cosHue = cos(value * piFloat / 180);
    float sinHue = sin(value * piFloat / 180);
    components[0] = 0.213 + cosHue * 0.787 - sinHue * 0.213;
    components[1] = 0.715 - cosHue * 0.715 - sinHue * 0.715;
    components[2] = 0.072 - cosHue * 0.072 + sinHue * 0.928;
    components[3] = 0.213 - cosHue * 0.213 + sinHue * 0.143;
    components[4] = 0.715 + cosHue * 0.285 + sinHue * 0.140;
    components[5] = 0.072 - cosHue * 0.072 - sinHue * 0.283;
    components[6] = 0.213 - cosHue * 0.213 - sinHue * 0.787;
    components[7] = 0.715 - cosHue * 0.715 + sinHue * 0.715;
    components[8] = 0.072 + cosHue * 0.928 + sinHue * 0.072;
}


} // namespace WebCore

#endif // FEColorMatrix_h
