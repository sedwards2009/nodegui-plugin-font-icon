#pragma once

#include <QIcon>
#include <QIconEngine>
#include <QPainter>


class FontIconEngine : public QIconEngine {
    public:
        explicit FontIconEngine(QFont font, QString text, qreal scale, qreal rotation, QRgb normalOnRgb,
                                QRgb disabledOnRgb, QRgb activeOnRgb, QRgb selectedOnRgb, QRgb normalOffRgb,
                                QRgb disabledOffRgb, QRgb activeOffRgb, QRgb selectedOffRgb);
        virtual QIconEngine* clone() const;
        virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state);
        virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state);
        static QIcon* createIcon(QFont font, QString text, qreal scale, qreal rotation,
                                 QRgb normalOnRgb, QRgb disabledOnRgb, QRgb activeOnRgb, QRgb selectedOnRgb,
                                 QRgb normalOffRgb, QRgb disabledOffRgb, QRgb activeOffRgb, QRgb selectedOffRgb);
    private:
        QString m_fontName;
        QString m_text;
        qreal m_scale;
        qreal m_rotation;
        QFont m_font;
        QRgb m_rgb[8];
};
