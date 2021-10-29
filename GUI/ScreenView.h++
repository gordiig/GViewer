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
    QGraphicsPixmapItem *pixmapItem;

    inline static QColor convertColor(const RGBA &color) noexcept {
        return {color.getR(), color.getG(), color.getB()};
    }

    void updateGraphicsScene() {
        if (pixmapItem) {
            gs.removeItem(pixmapItem);
            delete pixmapItem;
        }
        pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(im));
        gs.addItem(pixmapItem);
    }

public:
    ScreenView(int width, int height, QWidget *parent = nullptr) :
            QGraphicsView(parent), gs(this), im(width, height, QImage::Format_ARGB32_Premultiplied), pixmapItem(nullptr) {
        // Setting size and gs
        setFixedWidth(width);
        setFixedHeight(height);
        this->setScene(&gs);

        // Filling screen with black color on init
        im.fill(QColor(0, 0, 0));
        updateGraphicsScene();

        // Removing scrolls
        const auto& rcontent = this->contentsRect();
        this->setSceneRect(0, 0, rcontent.width(), rcontent.height());
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    ScreenView(const ScreenView &copy) = delete;
    ScreenView(ScreenView &&move) noexcept = delete;

    ScreenView& operator = (const ScreenView &copy) = delete;
    ScreenView& operator = (ScreenView &&move) noexcept = delete;

    void setScreen(Screen &&screen) {
        const auto& screenSize = screen.getSize();
        const auto& width = screenSize.first;
        const auto& height = screenSize.second;

        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                const auto& screenPixelColor = screen.getPixedColor(x, y);
                const auto& qtColor = convertColor(screenPixelColor);

                im.setPixelColor((int) x, (int) y, qtColor);
            }
        }

        updateGraphicsScene();
        this->show();
    }

    // Cur item's owner is gs, so we have no need to delete it
    ~ScreenView() override {
        delete pixmapItem;
    }
};

#endif //GVIEWER_SCREENVIEW_H
