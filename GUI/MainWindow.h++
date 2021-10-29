//
// Created by 17105727 on 22.10.2021.
//

#ifndef GVIEWER_MAINWINDOW_H
#define GVIEWER_MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "ScreenView.h++"
#include "RightMenu.h++"
#include "Facade.h++"


class MainWindow: public QMainWindow {
    Q_OBJECT;

protected:
    ScreenView *sv;
    RightMenu *rightMenu;
    Facade facade;

public:
    MainWindow(int width, int height, int screenWidth, int screenHeight) : QMainWindow(), facade(screenWidth, screenHeight) {
        setFixedWidth(width);
        setFixedHeight(height);
        setWindowTitle("GViewer");

        // Setting central widget for window
        auto* cw = new QWidget();
        setCentralWidget(cw);

        // Creating screenView and right menu
        sv = new ScreenView(screenWidth, screenHeight, this);
        rightMenu = new RightMenu(this);

        // Initializing layout
        auto* newLayout = new QHBoxLayout();

        // Adding ScreenView and right menu to layout
        newLayout->addWidget(sv);
        newLayout->addWidget(rightMenu);

        // Setting top layout to the central widget
        centralWidget()->setLayout(newLayout);

        // Connecting delegate signals
//        QObject::connect(rightMenu, SIGNAL(xChangedSignal(int)),
//                         this, SLOT(xSpinBoxValueChangedSlot(int)));
//        QObject::connect(rightMenu, SIGNAL(yChangedSignal(int)),
//                         this, SLOT(ySpinBoxValueChangedSlot(int)));
//        QObject::connect(rightMenu, SIGNAL(zChangedSignal(int)),
//                         this, SLOT(zSpinBoxValueChangedSlot(int)));

        // Initializing graphics
//        try {
            Screen scr = facade.render();
            sv->setScreen(std::move(scr));
//        } catch (const std::exception &e) {
//            std::cout << e.what() << std::endl;
//        }
    }

    ~MainWindow() override {
        delete rightMenu;
        delete sv;
    }
};

#endif //GVIEWER_MAINWINDOW_H
