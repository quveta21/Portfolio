#include <QtWidgets/QApplication>
#include "ProductGUI.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MedicamentRepoFile repo("file_repo");
    MedList serv(repo);
    ProductGUI gui(serv);
    gui.show();

    return a.exec();
}
