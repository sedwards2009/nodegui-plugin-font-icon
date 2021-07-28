#pragma once

#include <QIcon>
#include <QIconEngine>
#include <QPainter>


class FontIconEngine : public QIconEngine {
    public:
        explicit FontIconEngine(QFont font, QString text);
        virtual QIconEngine* clone() const;
        virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state);
        virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state);
        static QIcon* createIcon(QFont font, QString text);
    private:
        QString m_fontName;
        QString m_text;
        QFont m_font;
};
