//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_RIGHTMENU_H
#define GVIEWER_RIGHTMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include "CoordsRow.h++"


class RightMenu: public QWidget {
    Q_OBJECT;

protected:
    CoordsRow *coordsRow;

protected slots:
    void xSpinBoxValueChangedSlot(int newValue) { emit xChangedSignal(newValue); }

    void ySpinBoxValueChangedSlot(int newValue) { emit yChangedSignal(newValue); }

    void zSpinBoxValueChangedSlot(int newValue) { emit zChangedSignal(newValue); }

public:
    explicit RightMenu(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()): QWidget(parent, f) {
        // Creating layout
        auto* qVBoxLayout = new QVBoxLayout(this);

        // Creating coordinates row
        coordsRow = new CoordsRow("Camera position", this);

        // Adding coords row to layout
        qVBoxLayout->addWidget(coordsRow);

        // Setting layout
        this->setLayout(qVBoxLayout);

        // Connecting delegate signals
        QObject::connect(coordsRow, SIGNAL(xChangedSignal(int)),
                         this, SLOT(xSpinBoxValueChangedSlot(int)));
        QObject::connect(coordsRow, SIGNAL(yChangedSignal(int)),
                         this, SLOT(ySpinBoxValueChangedSlot(int)));
        QObject::connect(coordsRow, SIGNAL(zChangedSignal(int)),
                         this, SLOT(zSpinBoxValueChangedSlot(int)));
    }

signals:
    void xChangedSignal(int);
    void yChangedSignal(int);
    void zChangedSignal(int);

public:
    ~RightMenu() override {
        delete coordsRow;
    }
};

#endif //GVIEWER_RIGHTMENU_H
