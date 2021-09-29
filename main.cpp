#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "Utils/Containers/Vector.h++"
#include "Exceptions/Range.h++"
#include <vector>

int main(int argc, char *argv[]) {
    Vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = vec.iterForValue(2);

    vec.valueIndex(0);

    std::cout << vec << std::endl << vec.toString() << std::endl << vec.valueIndex(0) << ' ' << vec.valueIndex(9) << std::endl;

    try {
        vec[10000];
    } catch (IndexError &exc) {
        std::cerr << exc.what() << std::endl;
    }

    return 0;

//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    return QApplication::exec();
}
