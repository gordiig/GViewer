//
// Created by 17105727 on 25.10.2021.
//

#ifndef GVIEWER_LABELEDSPINBOX_H
#define GVIEWER_LABELEDSPINBOX_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>


class LabeledSpinBox: public QWidget {
    Q_OBJECT

protected:
    QLabel *titleLabel;
    QSpinBox *spinBox;

protected slots:
    void spinBoxValueChangedSlot(int newValue) { emit valueChanged(newValue); }

public:
    enum TitlePos { LEFT_TITLE, TOP_TITLE };

    explicit LabeledSpinBox(const QString &title, TitlePos titlePosition = LEFT_TITLE, QWidget *parent = nullptr) :
            QWidget(parent) {
        titleLabel = new QLabel(title + ":", this);
        spinBox = new QSpinBox(this);
        spinBox->setMinimum(-1'000);
        spinBox->setMaximum(1'000);

        QLayout *newLayout = nullptr;
        if (titlePosition == LEFT_TITLE)
            newLayout = new QHBoxLayout(this);
        else
            newLayout = new QVBoxLayout(this);

        newLayout->addWidget(titleLabel);
        newLayout->addWidget(spinBox);

        this->setLayout(newLayout);

        QObject::connect(spinBox, SIGNAL(valueChanged(int)),
                         this, SLOT(spinBoxValueChangedSlot(int)));
    }

signals:
    void valueChanged(int);

public:
    ~LabeledSpinBox() override {
        delete titleLabel;
        delete spinBox;
    }

};


#endif //GVIEWER_LABELEDSPINBOX_H
