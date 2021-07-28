
#include "FontIcon.h"

FontIconEngine::FontIconEngine(QFont font, QString text) : QIconEngine() {
    m_font = font;
    m_text = text;
}

QIconEngine* FontIconEngine::clone() const {
    return new FontIconEngine(m_fontName, m_text);
}

void FontIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) {
    painter->save();

    painter->setPen(Qt::black);
    painter->setFont(m_font);

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

QIcon* FontIconEngine::createIcon(QFont font, QString text) {
    return new QIcon(new FontIconEngine(font, text));
}
