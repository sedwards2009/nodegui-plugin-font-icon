#include <math.h>
#include "FontIcon.h"


FontIconEngine::FontIconEngine(QFont font, QString text, qreal scale, qreal rotation, QRgb normalOnRgb,
                               QRgb disabledOnRgb, QRgb activeOnRgb, QRgb selectedOnRgb, QRgb normalOffRgb,
                               QRgb disabledOffRgb, QRgb activeOffRgb, QRgb selectedOffRgb) : QIconEngine() {
    m_font = font;
    m_text = text;
    m_scale = scale;
    m_rotation = rotation;

    m_rgb[0] = normalOnRgb;
    m_rgb[1] = disabledOnRgb;
    m_rgb[2] = activeOnRgb;
    m_rgb[3] = selectedOnRgb;
    m_rgb[4] = normalOffRgb;
    m_rgb[5] = disabledOffRgb;
    m_rgb[6] = activeOffRgb;
    m_rgb[7] = selectedOffRgb;
}

QIconEngine* FontIconEngine::clone() const {
    return new FontIconEngine(m_fontName, m_text, m_scale, m_rotation, m_rgb[0], m_rgb[1], m_rgb[2], m_rgb[3], m_rgb[4],
                              m_rgb[5], m_rgb[6], m_rgb[7]);
}

void FontIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) {
    painter->save();

    uint index = (state * 4) + mode;
    painter->setPen(QColor(m_rgb[index]));

    QFont font = m_font;
    font.setPixelSize(round(rect.height() * m_scale));
    painter->setFont(font);

    if (m_rotation != 0.0) {
        qreal height = rect.height();
        qreal width = rect.width();
        auto transform = QTransform().translate(width/2, height/2).rotate(m_rotation).translate(-width/2, -height/2);
        painter->setTransform(transform);
    }

    painter->drawText(rect, Qt::AlignCenter, m_text);
    painter->restore();
}

QPixmap FontIconEngine::pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) {
    QPixmap pix(size);
    pix.fill(Qt::transparent);
    {
        QPainter painter(&pix);
        paint(&painter, QRect(QPoint(0,0), size), mode, state);
    }
    return pix;
}

QIcon* FontIconEngine::createIcon(QFont font, QString text, qreal scale, qreal rotation,
                                  QRgb normalOnRgb, QRgb disabledOnRgb, QRgb activeOnRgb, QRgb selectedOnRgb,
                                  QRgb normalOffRgb, QRgb disabledOffRgb, QRgb activeOffRgb, QRgb selectedOffRgb) {
    return new QIcon(new FontIconEngine(font, text, scale, rotation, normalOnRgb, disabledOnRgb, activeOnRgb,
                                        selectedOnRgb, normalOffRgb, disabledOffRgb, activeOffRgb, selectedOffRgb));
}
