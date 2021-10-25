//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_SCREENVIEW_H
#define GVIEWER_SCREENVIEW_H

#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QColor>
#include "../Graphics/Screen/Screen.h++"
#include "../Graphics/Basics/RGBA.h++"


class ScreenView: public QGraphicsView {
protected:
    QGraphicsScene gs;
    QImage im;
    QGraphicsPixmapItem *curItem = nullptr;

    inline static QColor convertColor(const RGBA &color) noexcept {
        return {color.getR(), color.getG(), color.getB(), color.getA()};
    }

public:
    ScreenView(int width, int height, QWidget *parent = nullptr) :
            QGraphicsView(parent), gs(this), im(width, height, QImage::Format_ARGB32_Premultiplied) {
        setFixedWidth(width);
        setFixedHeight(height);
        this->setScene(&gs);
    }

    ScreenView(const ScreenView &copy) = delete;
    ScreenView(ScreenView &&move) noexcept = delete;

    ScreenView& operator = (const ScreenView &copy) = delete;
    ScreenView& operator = (ScreenView &&move) noexcept = delete;

    void setScreen(Screen &&screen) {
        const auto& [width, height] = screen.getSize();

        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                im.setPixelColor((int) x, (int) y, convertColor(screen.getPixedColor(x, y)));
            }
        }

        QPixmap px = QPixmap::fromImage(im);
        if (curItem) {
            gs.removeItem((QGraphicsItem*) curItem);
            delete curItem;
        }
        curItem = gs.addPixmap(px);
    }

    // Cur item's owner is gs, so we have no need to delete it
    ~ScreenView() override = default;
};

#endif //GVIEWER_SCREENVIEW_H
