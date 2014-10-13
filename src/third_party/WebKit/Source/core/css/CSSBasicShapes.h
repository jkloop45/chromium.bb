/*
 * Copyright (C) 2011 Adobe Systems Incorporated. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER “AS IS” AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef CSSBasicShapes_h
#define CSSBasicShapes_h

#include "core/css/CSSPrimitiveValue.h"
#include "platform/graphics/WindRule.h"
#include "wtf/RefPtr.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace WebCore {

class CSSBasicShape : public RefCounted<CSSBasicShape> {
public:
    enum Type {
        CSSBasicShapeRectangleType,
        CSSDeprecatedBasicShapeCircleType,
        CSSDeprecatedBasicShapeEllipseType,
        CSSBasicShapeEllipseType,
        CSSBasicShapePolygonType,
        CSSBasicShapeInsetRectangleType,
        CSSBasicShapeCircleType,
        CSSBasicShapeInsetType
    };

    virtual Type type() const = 0;
    virtual String cssText() const = 0;
    virtual bool equals(const CSSBasicShape&) const = 0;

    CSSPrimitiveValue* layoutBox() const { return m_layoutBox.get(); }
    void setLayoutBox(PassRefPtr<CSSPrimitiveValue> layoutBox) { m_layoutBox = layoutBox; }

public:
    virtual ~CSSBasicShape() { }

protected:
    CSSBasicShape() { }
    RefPtr<CSSPrimitiveValue> m_layoutBox;
};

class CSSBasicShapeRectangle FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSBasicShapeRectangle> create() { return adoptRef(new CSSBasicShapeRectangle); }

    CSSPrimitiveValue* x() const { return m_x.get(); }
    CSSPrimitiveValue* y() const { return m_y.get(); }
    CSSPrimitiveValue* width() const { return m_width.get(); }
    CSSPrimitiveValue* height() const { return m_height.get(); }
    CSSPrimitiveValue* radiusX() const { return m_radiusX.get(); }
    CSSPrimitiveValue* radiusY() const { return m_radiusY.get(); }

    void setX(PassRefPtr<CSSPrimitiveValue> x) { m_x = x; }
    void setY(PassRefPtr<CSSPrimitiveValue> y) { m_y = y; }
    void setWidth(PassRefPtr<CSSPrimitiveValue> width) { m_width = width; }
    void setHeight(PassRefPtr<CSSPrimitiveValue> height) { m_height = height; }
    void setRadiusX(PassRefPtr<CSSPrimitiveValue> radiusX) { m_radiusX = radiusX; }
    void setRadiusY(PassRefPtr<CSSPrimitiveValue> radiusY) { m_radiusY = radiusY; }

    virtual Type type() const OVERRIDE { return CSSBasicShapeRectangleType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

private:
    CSSBasicShapeRectangle() { }

    RefPtr<CSSPrimitiveValue> m_y;
    RefPtr<CSSPrimitiveValue> m_x;
    RefPtr<CSSPrimitiveValue> m_width;
    RefPtr<CSSPrimitiveValue> m_height;
    RefPtr<CSSPrimitiveValue> m_radiusX;
    RefPtr<CSSPrimitiveValue> m_radiusY;
};

class CSSBasicShapeInsetRectangle FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSBasicShapeInsetRectangle> create() { return adoptRef(new CSSBasicShapeInsetRectangle); }

    CSSPrimitiveValue* top() const { return m_top.get(); }
    CSSPrimitiveValue* right() const { return m_right.get(); }
    CSSPrimitiveValue* bottom() const { return m_bottom.get(); }
    CSSPrimitiveValue* left() const { return m_left.get(); }
    CSSPrimitiveValue* radiusX() const { return m_radiusX.get(); }
    CSSPrimitiveValue* radiusY() const { return m_radiusY.get(); }

    void setTop(PassRefPtr<CSSPrimitiveValue> top) { m_top = top; }
    void setRight(PassRefPtr<CSSPrimitiveValue> right) { m_right = right; }
    void setBottom(PassRefPtr<CSSPrimitiveValue> bottom) { m_bottom = bottom; }
    void setLeft(PassRefPtr<CSSPrimitiveValue> left) { m_left = left; }
    void setRadiusX(PassRefPtr<CSSPrimitiveValue> radiusX) { m_radiusX = radiusX; }
    void setRadiusY(PassRefPtr<CSSPrimitiveValue> radiusY) { m_radiusY = radiusY; }

    virtual Type type() const OVERRIDE { return CSSBasicShapeInsetRectangleType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

private:
    CSSBasicShapeInsetRectangle() { }

    RefPtr<CSSPrimitiveValue> m_right;
    RefPtr<CSSPrimitiveValue> m_top;
    RefPtr<CSSPrimitiveValue> m_bottom;
    RefPtr<CSSPrimitiveValue> m_left;
    RefPtr<CSSPrimitiveValue> m_radiusX;
    RefPtr<CSSPrimitiveValue> m_radiusY;
};

class CSSBasicShapeCircle FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSBasicShapeCircle> create() { return adoptRef(new CSSBasicShapeCircle); }

    virtual Type type() const OVERRIDE { return CSSBasicShapeCircleType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

    CSSPrimitiveValue* centerX() const { return m_centerX.get(); }
    CSSPrimitiveValue* centerY() const { return m_centerY.get(); }
    CSSPrimitiveValue* radius() const { return m_radius.get(); }

    void setCenterX(PassRefPtr<CSSPrimitiveValue> centerX) { m_centerX = centerX; }
    void setCenterY(PassRefPtr<CSSPrimitiveValue> centerY) { m_centerY = centerY; }
    void setRadius(PassRefPtr<CSSPrimitiveValue> radius) { m_radius = radius; }

private:
    CSSBasicShapeCircle() { }

    RefPtr<CSSPrimitiveValue> m_centerX;
    RefPtr<CSSPrimitiveValue> m_centerY;
    RefPtr<CSSPrimitiveValue> m_radius;
};

class CSSDeprecatedBasicShapeCircle FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSDeprecatedBasicShapeCircle> create() { return adoptRef(new CSSDeprecatedBasicShapeCircle); }

    CSSPrimitiveValue* centerX() const { return m_centerX.get(); }
    CSSPrimitiveValue* centerY() const { return m_centerY.get(); }
    CSSPrimitiveValue* radius() const { return m_radius.get(); }

    void setCenterX(PassRefPtr<CSSPrimitiveValue> centerX) { m_centerX = centerX; }
    void setCenterY(PassRefPtr<CSSPrimitiveValue> centerY) { m_centerY = centerY; }
    void setRadius(PassRefPtr<CSSPrimitiveValue> radius) { m_radius = radius; }

    virtual Type type() const OVERRIDE { return CSSDeprecatedBasicShapeCircleType; }

    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

private:
    CSSDeprecatedBasicShapeCircle() { }

    RefPtr<CSSPrimitiveValue> m_centerY;
    RefPtr<CSSPrimitiveValue> m_centerX;
    RefPtr<CSSPrimitiveValue> m_radius;
};

class CSSBasicShapeEllipse FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSBasicShapeEllipse> create() { return adoptRef(new CSSBasicShapeEllipse); }

    virtual Type type() const OVERRIDE { return CSSBasicShapeEllipseType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

    CSSPrimitiveValue* centerX() const { return m_centerX.get(); }
    CSSPrimitiveValue* centerY() const { return m_centerY.get(); }
    CSSPrimitiveValue* radiusX() const { return m_radiusX.get(); }
    CSSPrimitiveValue* radiusY() const { return m_radiusY.get(); }

    void setCenterX(PassRefPtr<CSSPrimitiveValue> centerX) { m_centerX = centerX; }
    void setCenterY(PassRefPtr<CSSPrimitiveValue> centerY) { m_centerY = centerY; }
    void setRadiusX(PassRefPtr<CSSPrimitiveValue> radiusX) { m_radiusX = radiusX; }
    void setRadiusY(PassRefPtr<CSSPrimitiveValue> radiusY) { m_radiusY = radiusY; }

private:
    CSSBasicShapeEllipse() { }

    RefPtr<CSSPrimitiveValue> m_centerX;
    RefPtr<CSSPrimitiveValue> m_centerY;
    RefPtr<CSSPrimitiveValue> m_radiusX;
    RefPtr<CSSPrimitiveValue> m_radiusY;
};

class CSSDeprecatedBasicShapeEllipse FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSDeprecatedBasicShapeEllipse> create() { return adoptRef(new CSSDeprecatedBasicShapeEllipse); }

    CSSPrimitiveValue* centerX() const { return m_centerX.get(); }
    CSSPrimitiveValue* centerY() const { return m_centerY.get(); }
    CSSPrimitiveValue* radiusX() const { return m_radiusX.get(); }
    CSSPrimitiveValue* radiusY() const { return m_radiusY.get(); }

    void setCenterX(PassRefPtr<CSSPrimitiveValue> centerX) { m_centerX = centerX; }
    void setCenterY(PassRefPtr<CSSPrimitiveValue> centerY) { m_centerY = centerY; }
    void setRadiusX(PassRefPtr<CSSPrimitiveValue> radiusX) { m_radiusX = radiusX; }
    void setRadiusY(PassRefPtr<CSSPrimitiveValue> radiusY) { m_radiusY = radiusY; }

    virtual Type type() const OVERRIDE { return CSSDeprecatedBasicShapeEllipseType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

private:
    CSSDeprecatedBasicShapeEllipse() { }

    RefPtr<CSSPrimitiveValue> m_centerX;
    RefPtr<CSSPrimitiveValue> m_centerY;
    RefPtr<CSSPrimitiveValue> m_radiusX;
    RefPtr<CSSPrimitiveValue> m_radiusY;
};

class CSSBasicShapePolygon FINAL : public CSSBasicShape {
public:
    static PassRefPtr<CSSBasicShapePolygon> create() { return adoptRef(new CSSBasicShapePolygon); }

    void appendPoint(PassRefPtr<CSSPrimitiveValue> x, PassRefPtr<CSSPrimitiveValue> y)
    {
        m_values.append(x);
        m_values.append(y);
    }

    PassRefPtr<CSSPrimitiveValue> getXAt(unsigned i) const { return m_values.at(i * 2); }
    PassRefPtr<CSSPrimitiveValue> getYAt(unsigned i) const { return m_values.at(i * 2 + 1); }
    const Vector<RefPtr<CSSPrimitiveValue> >& values() const { return m_values; }

    void setWindRule(WindRule w) { m_windRule = w; }
    WindRule windRule() const { return m_windRule; }

    virtual Type type() const OVERRIDE { return CSSBasicShapePolygonType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;
private:
    CSSBasicShapePolygon()
        : m_windRule(RULE_NONZERO)
    {
    }

    Vector<RefPtr<CSSPrimitiveValue> > m_values;
    WindRule m_windRule;
};

class CSSBasicShapeInset : public CSSBasicShape {
public:
    static PassRefPtr<CSSBasicShapeInset> create() { return adoptRef(new CSSBasicShapeInset); }

    CSSPrimitiveValue* top() const { return m_top.get(); }
    CSSPrimitiveValue* right() const { return m_right.get(); }
    CSSPrimitiveValue* bottom() const { return m_bottom.get(); }
    CSSPrimitiveValue* left() const { return m_left.get(); }

    CSSPrimitiveValue* topLeftRadius() const { return m_topLeftRadius.get(); }
    CSSPrimitiveValue* topRightRadius() const { return m_topRightRadius.get(); }
    CSSPrimitiveValue* bottomRightRadius() const { return m_bottomRightRadius.get(); }
    CSSPrimitiveValue* bottomLeftRadius() const { return m_bottomLeftRadius.get(); }

    void setTop(PassRefPtr<CSSPrimitiveValue> top) { m_top = top; }
    void setRight(PassRefPtr<CSSPrimitiveValue> right) { m_right = right; }
    void setBottom(PassRefPtr<CSSPrimitiveValue> bottom) { m_bottom = bottom; }
    void setLeft(PassRefPtr<CSSPrimitiveValue> left) { m_left = left; }

    void updateShapeSize4Values(CSSPrimitiveValue* top, CSSPrimitiveValue* right, CSSPrimitiveValue* bottom, CSSPrimitiveValue* left)
    {
        setTop(top);
        setRight(right);
        setBottom(bottom);
        setLeft(left);
    }

    void updateShapeSize1Value(CSSPrimitiveValue* value1)
    {
        updateShapeSize4Values(value1, value1, value1, value1);
    }

    void updateShapeSize2Values(CSSPrimitiveValue* value1,  CSSPrimitiveValue* value2)
    {
        updateShapeSize4Values(value1, value2, value1, value2);
    }

    void updateShapeSize3Values(CSSPrimitiveValue* value1, CSSPrimitiveValue* value2,  CSSPrimitiveValue* value3)
    {
        updateShapeSize4Values(value1, value2, value3, value2);
    }


    void setTopLeftRadius(PassRefPtr<CSSPrimitiveValue> radius) { m_topLeftRadius = radius; }
    void setTopRightRadius(PassRefPtr<CSSPrimitiveValue> radius) { m_topRightRadius = radius; }
    void setBottomRightRadius(PassRefPtr<CSSPrimitiveValue> radius) { m_bottomRightRadius = radius; }
    void setBottomLeftRadius(PassRefPtr<CSSPrimitiveValue> radius) { m_bottomLeftRadius = radius; }

    virtual Type type() const OVERRIDE { return CSSBasicShapeInsetType; }
    virtual String cssText() const OVERRIDE;
    virtual bool equals(const CSSBasicShape&) const OVERRIDE;

private:
    CSSBasicShapeInset() { }

    RefPtr<CSSPrimitiveValue> m_top;
    RefPtr<CSSPrimitiveValue> m_right;
    RefPtr<CSSPrimitiveValue> m_bottom;
    RefPtr<CSSPrimitiveValue> m_left;

    RefPtr<CSSPrimitiveValue> m_topLeftRadius;
    RefPtr<CSSPrimitiveValue> m_topRightRadius;
    RefPtr<CSSPrimitiveValue> m_bottomRightRadius;
    RefPtr<CSSPrimitiveValue> m_bottomLeftRadius;
};

} // namespace WebCore

#endif // CSSBasicShapes_h
