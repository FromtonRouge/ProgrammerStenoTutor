// ======================================================================
// This file is a part of the KaladriusTrainer project
//
// Copyright (C) 2020  Vissale NEANG <fromtonrouge at gmail dot com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ======================================================================

#pragma once

#include <QtSvg/QGraphicsSvgItem>
#include <QtGui/QTransform>
#include <QtCore/QRectF>
#include <QtCore/QPointF>

class QGraphicsSimpleTextItem;
class QGraphicsRectItem;
class QGraphicsRotation;
class QSvgRenderer;
class QColor;
class KeycapGraphicsItem : public QGraphicsSvgItem
{
public:
    enum
    {
        Type = UserType + 1
    };

public:
    KeycapGraphicsItem( const QString& sKeycapId,
                        qreal dRotationAngle,
                        const QPointF& rotationOrigin,
                        const QRectF& rectOuterBorder,
                        QSvgRenderer* pSvgRenderer,
                        QGraphicsItem* pParent = nullptr);
    ~KeycapGraphicsItem();

    void setColor(const QColor& color);
    void setText(const QString& sText);
    void setTextFont(const QFont& font);
    void setTextOffsetX(qreal fX);
    void setTextOffsetY(qreal fY);

    virtual int type() const override {return Type;}
    virtual QPainterPath shape() const override;

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    virtual void paint(QPainter* pPainter, const QStyleOptionGraphicsItem* pOption, QWidget* pWidget) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* pEvent) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent) override;

private:
    void centerText();

private:
    QTransform _transformScene;
    QGraphicsRectItem* _pOuterBorderItem;
    QGraphicsSimpleTextItem* _pTextItem;
    qreal _dRotationAngle;
    QPointF _rotationOrigin;
    int _iTextPixelSize;
    QPointF _textOffset;
    QRectF _rectOuterBorder;
    QGraphicsRotation* _pRotation;
};
