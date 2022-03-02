//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_COORDSROW_H
#define GVIEWER_COORDSROW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <QSpacerItem>
#include "Utils/LabeledSpinBox.h++"


class CoordsRow: public QWidget {
    Q_OBJECT;

protected:
    QLabel *titleLabel;
    LabeledSpinBox *xSpinBox;
    LabeledSpinBox *ySpinBox;
    LabeledSpinBox *zSpinBox;

protected slots:
    void xSpinBoxValueChangedSlot(int newValue) { emit xChangedSignal(newValue); }

    void ySpinBoxValueChangedSlot(int newValue) { emit yChangedSignal(newValue); }

    void zSpinBoxValueChangedSlot(int newValue) { emit zChangedSignal(newValue); }

public:
    explicit CoordsRow(const QString &title, QWidget *parent = nullptr) : QWidget(parent) {
        // Initializing main layout and alignement
        auto* mainLayout = new QVBoxLayout(this);
        mainLayout->setAlignment(Qt::AlignmentFlag::AlignTop);

        // Initializing title label
        titleLabel = new QLabel(title + ":", this);

        // Adding label to layout on top
        mainLayout->addWidget(titleLabel);

        // Initializing labeled spin boxes
        xSpinBox = new LabeledSpinBox("x", LabeledSpinBox::LEFT_TITLE, this);
        ySpinBox = new LabeledSpinBox("y", LabeledSpinBox::LEFT_TITLE, this);
        zSpinBox = new LabeledSpinBox("z", LabeledSpinBox::LEFT_TITLE, this);

        // Initializing horizontal layout for spinBoxes
        auto* spinBoxesLayout = new QHBoxLayout(this);

        // Adding spin boxes to their layout
        spinBoxesLayout->addWidget(xSpinBox);
        spinBoxesLayout->addWidget(ySpinBox);
        spinBoxesLayout->addWidget(zSpinBox);

        // Adding spin boxes layout to main layout
        mainLayout->addLayout(spinBoxesLayout);

        // Adding layout to this
        setLayout(mainLayout);

        // Connecting basic signals and my delegate slots
        QObject::connect(xSpinBox, SIGNAL(valueChanged(int)),
                         this, SLOT(xSpinBoxValueChangedSlot(int)));
        QObject::connect(ySpinBox, SIGNAL(valueChanged(int)),
                         this, SLOT(ySpinBoxValueChangedSlot(int)));
        QObject::connect(zSpinBox, SIGNAL(valueChanged(int)),
                         this, SLOT(zSpinBoxValueChangedSlot(int)));
    }

signals:
    void xChangedSignal(int);
    void yChangedSignal(int);
    void zChangedSignal(int);

public:
    ~CoordsRow() override {
        delete titleLabel;
        delete xSpinBox;
        delete ySpinBox;
        delete zSpinBox;
    }

};


#endif //GVIEWER_COORDSROW_H
