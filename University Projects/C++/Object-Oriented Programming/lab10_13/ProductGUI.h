#pragma once
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qtablewidget.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <vector>
#include <string>
#include <QtWidgets/qwidget.h>
#include "service.h"
#include "ModelView.h"
#include "Observer.h"
using std::vector;
using std::string;

class ProductGUI;
class RetetaCRUDGUI;
class RetetaReadOnlyGUI;

class GUIException {
    vector<QString> msg;
public:
    GUIException(const vector<QString>& m) : msg{ m } {
    }
    /*
    * Returneaza mesajul exceptiei - string
    */
    QString getMessage() {
        QString errors;
        for (const QString& e : msg) {
            errors.append(e);
        }
        return errors;
    }

    ~GUIException() = default;
};



class RetetaCRUDGUI : public QWidget, public Observer {
public:
    RetetaCRUDGUI(MedList& serv) : serv{ serv } {
        initGUIReteta();
        initConnectReteta();
    }

    ~RetetaCRUDGUI() {
        serv.removeObserver(this);
    }

private:
    friend class RetetaReadOnlyGUI;

    MedList& serv;
    TableModel* model;

    QHBoxLayout* lyReteta = nullptr;
    QTableView* tbl /*= new QTableWidget(0, 4, this)*/;
    QPushButton* btnAddToReteta = new QPushButton{ "Adauga la reteta" };
    QPushButton* btnEmptyReteta = new QPushButton{ "Goleste reteta" };
    QPushButton* btnGenerateReteta = new QPushButton{ "Genereaza aleator reteta" };
    QPushButton* btnSalveazaReteta = new QPushButton{ "Salveaza reteta in fisier" };

    void initConnectReteta() {
        QObject::connect(btnEmptyReteta, &QPushButton::clicked, [&]() {
            serv.emptyReteta();
            QMessageBox::information(this, "Reteta", "Reteta este goala, intoarceti-va dupa ce adaugati medicamente!!");
            this->close();
            });

        QObject::connect(btnGenerateReteta, &QPushButton::clicked, [&]() {
            auto lyBox = new QVBoxLayout;
            auto lyGenerate = new QFormLayout;
            lyBox->addLayout(lyGenerate);
            lyReteta->addLayout(lyBox);
            auto lineEdit = new QLineEdit;
            lyGenerate->addRow("Numarul de elemente aleatorii", lineEdit);
            auto btnNrGenerate = new QPushButton{ "Genereaza medicamentele!" };
            lyBox->addWidget(btnNrGenerate);
            QObject::connect(btnNrGenerate, &QPushButton::clicked, [&, lineEdit, lyBox, btnNrGenerate, lyGenerate]() {
                try {
                    if (lineEdit->text().isEmpty())
                        throw GUIException({ "Numarul de elemente trebuie sa fie mai mare decat 0!! " });
                    auto nr = getInt(lineEdit->text());
                    serv.generateReteta(serv.getAll(), nr);
                    //loadTable(serv.getRetetaAll());
                    model->setList(serv.getRetetaAll());
                    delete lineEdit;
                    lyGenerate->removeRow(0);
                    delete btnNrGenerate;
                    lyReteta->removeItem(lyBox);
                    delete lyBox;
                }
                catch (GUIException& err) {
                    QMessageBox::warning(this, "Eroare la generarea medicamentelor!!", err.getMessage());
                }
                });
            });

        QObject::connect(btnSalveazaReteta, &QPushButton::clicked, [&]() {
            auto lyBox = new QVBoxLayout;
            auto lyGenerate = new QFormLayout;
            lyBox->addLayout(lyGenerate);
            lyReteta->addLayout(lyBox);
            auto lineEdit = new QLineEdit;
            lyGenerate->addRow("Numele fisierului:", lineEdit);
            auto btnSaveFile = new QPushButton{ "Salveaza reteta!" };
            lyBox->addWidget(btnSaveFile);
            QObject::connect(btnSaveFile, &QPushButton::clicked, [&, lineEdit, lyBox, btnSaveFile, lyGenerate]() {
                try {
                    if (lineEdit->text().isEmpty())
                        throw GUIException({ "Nu ati introdus un nume de fisier!!" });
                    string filename = lineEdit->text().toStdString();
                    serv.saveToFile(filename);
                    QMessageBox::information(this, "Reteta", "Reteta a fost salvata in fisier!!");
                    delete lineEdit;
                    lyGenerate->removeRow(0);
                    delete btnSaveFile;
                    lyReteta->removeItem(lyBox);
                    delete lyBox;
                }
                catch (GUIException& err) {
                    QMessageBox::warning(this, "Eroare la salvarea retetei!!", err.getMessage());
                }
                });
            });
    }

    void initGUIReteta() {
        serv.addObserver(this);
        lyReteta = new QHBoxLayout;
        this->setLayout(lyReteta);
        tbl = new QTableView();
        model = new TableModel(serv.getRetetaAll());
        model->setList(serv.getRetetaAll());
        tbl->setModel(model);
        /*tbl->setHorizontalHeaderItem(0, new QTableWidgetItem("Denumire"));
        tbl->setHorizontalHeaderItem(1, new QTableWidgetItem("Pret"));
        tbl->setHorizontalHeaderItem(2, new QTableWidgetItem("Producator"));
        tbl->setHorizontalHeaderItem(3, new QTableWidgetItem("Substanta activa"));*/
        lyReteta->addWidget(tbl);
        //loadTable(serv.getRetetaAll());

        auto lyRetetaBtns = new QVBoxLayout;
        lyRetetaBtns->addWidget(btnEmptyReteta);
        lyRetetaBtns->addWidget(btnGenerateReteta);
        lyRetetaBtns->addWidget(btnSalveazaReteta);
        lyReteta->addLayout(lyRetetaBtns);

        this->show();
    }

    void update() override {
        try {
            //loadTable(serv.getRetetaAll());
            model->setList(serv.getRetetaAll());
        }
        catch (RetetaException& err) {
            this->close();
        }
    }

    /*void loadTable(const vector<Medicament>& medicamente) {
        tbl->clearContents();
        tbl->setRowCount(medicamente.size());
        for (int i = 0; i < medicamente.size(); i++) {
            const auto& m = medicamente.at(i);
            tbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m.getDenumire())));
            tbl->setItem(i, 1, new QTableWidgetItem(QString::number(m.getPret())));
            tbl->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m.getProducator())));
            tbl->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(m.getSubstanta())));
        }
    }*/

    int getInt(const QString& nrCitit) {
        bool invalid = (nrCitit.isEmpty());
        int nr = 0;
        for (auto& ch : nrCitit.toStdString()) {
            if ('0' <= ch && ch <= '9')
                nr = nr * 10 + (ch - '0');
            else
                invalid = true;	//invalid daca gaseste macar un caracter non cifra
        }
        if (invalid) {
            nr = -1;
        }
        return nr;
    }
};


class RetetaReadOnlyGUI: public QWidget, public Observer {
private:
    friend class RetetaCRUDGUI;
    MedList& serv;


    void initReadOnlyGUI() {
        serv.addObserver(this);
        this->show();
        repaint();
    }

    void update() override {
        try {
            repaint();
        }
        catch (RetetaException& err) {
            this->close();
        }
    }
protected:
    void paintEvent(QPaintEvent* ev) override {
        try {
            QPainter p{ this };
            int x = 0;
            int y = 0;
            int maxWidth = this->width();
            for (const auto& med : serv.getRetetaAll()) {
                p.drawImage(x, y, QImage("spongebob.jpg"));
                x += 200;

                if (x + 200 > maxWidth) {
                    x = 0;
                    y += 200;
                }
            }
        }
        catch (RetetaException& err) {
            this->close();
        }
    }
public:
    RetetaReadOnlyGUI(MedList& serv) : serv{ serv } {
        initReadOnlyGUI();
    }

    ~RetetaReadOnlyGUI() {
        serv.removeObserver(this);
    }
};



class ProductGUI : public QWidget {
public:
    ProductGUI(MedList& service) : serv{ service } {
		initGUI();
        loadData();
        initConnect();
	}
private:
    MedList& serv;
    QListWidget* lst = new QListWidget{};
    RetetaCRUDGUI* GUIReteta = nullptr;
    RetetaReadOnlyGUI* GUIRetetaRO = nullptr;
    QHBoxLayout* lyReteta = nullptr;
    QComboBox* comboSort = new QComboBox{};
    QComboBox* comboFilter = new QComboBox{};
    QPushButton* btnExit = new QPushButton{ "Exit" };
    QPushButton* btnAdd = new QPushButton{ "Adauga" };
    QPushButton* btnDelete = new QPushButton{ "Sterge" };
    QPushButton* btnModify = new QPushButton{ "Modifica" };
    QPushButton* btnSearch = new QPushButton{ "Cauta" };
    QPushButton* btnReteta = new QPushButton{ "RetetaCRUD" };
    QPushButton* btnRetetaRO = new QPushButton{ "RetetaReadOnly" };
    QPushButton* btnAddToReteta = new QPushButton{ "Adauga la reteta" };
    QLineEdit* txtDenumire = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;
    QLineEdit* txtProducator = new QLineEdit;
    QLineEdit* txtSubstanta = new QLineEdit;
    //QTableWidget* tbl = new QTableWidget(0, 4, this);

    void loadData() {
        lst->clear();
        for (const auto& el : serv.getAll()) {
            /*lst->addItem(QString::fromStdString("Denumire: " + el.getDenumire() + ", Pret: " + std::to_string(el.getPret())
                + ", Producator: " + el.getProducator() + ", Substanta: " + el.getSubstanta()));*/
            auto* item = new QListWidgetItem(QString::fromStdString("Denumire: " + el.getDenumire() + ", Pret: " + std::to_string(el.getPret())
                + ", Producator: " + el.getProducator() + ", Substanta: " + el.getSubstanta()));
            item->setData(Qt::UserRole, QString::fromStdString(el.getDenumire()));
            lst->addItem(item);
        }
    }

    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            QMessageBox::warning(this, "Info", "Salutare!!");
            close();
        });

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            try {
                auto denumire = txtDenumire->text();
                auto pret = txtPret->text();
                auto producator = txtProducator->text();
                auto substanta = txtSubstanta->text();
                validate(denumire.toStdString(), getInt(pret), producator.toStdString(), substanta.toStdString());
                serv.add(denumire.toStdString(), getInt(pret), producator.toStdString(), substanta.toStdString());
                loadData();
                txtDenumire->setText("");
                txtPret->setText("");
                txtProducator->setText("");
                txtSubstanta->setText("");
            }
            catch (GUIException& err) {
                QMessageBox::warning(this, "Eroare la adaugarea medicamentului!!", err.getMessage());
            }
            catch (RepoException& err) {
                QMessageBox::warning(this, "Eroare la adaugarea medicamentului!!", QString::fromStdString(err.getMessage()));
            }
        });

        QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
            try {
                if (lst->selectedItems().isEmpty()) {
                    throw GUIException({ "Nu ati selectat un medicament pentru stergere!" });
                }
                QListWidgetItem* selectedItem = lst->currentItem();
                QString denumire = selectedItem->data(Qt::UserRole).toString();
                auto it = std::find_if(serv.getAll().begin(), serv.getAll().end(), [&](const auto& med) {
                    return QString::fromStdString(med.getDenumire()) == denumire;
                });
                if (it != serv.getAll().end()) {
                    int index = std::distance(serv.getAll().begin(), it);
                    serv.rmv(index + 1);
                }
                loadData();
            }
            catch (GUIException& err) {
                QMessageBox::warning(this, "Eroare la stergerea medicamentului!!", err.getMessage());
            }
        });

        QObject::connect(btnModify, &QPushButton::clicked, [&]() {
            try {
                if (lst->selectedItems().isEmpty()) {
                    throw GUIException({ "Nu ati selectat un medicament pentru modificare!" });
                }
                auto denumire = txtDenumire->text();
                auto pret = txtPret->text();
                auto producator = txtProducator->text();
                auto substanta = txtSubstanta->text();
                validate(denumire.toStdString(), getInt(pret), producator.toStdString(), substanta.toStdString());
                serv.modify(lst->row(lst->currentItem()) + 1, denumire.toStdString(), getInt(pret), producator.toStdString(), substanta.toStdString());
                loadData();
                txtDenumire->setText("");
                txtPret->setText("");
                txtProducator->setText("");
                txtSubstanta->setText("");
            }
            catch (GUIException& err) {
                QMessageBox::warning(this, "Eroare la modificarea medicamentului!!", err.getMessage());
            }
        });

        QObject::connect(btnSearch, &QPushButton::clicked, [&]() {
            try {
                auto denumire = txtDenumire->text();
                auto pret = txtPret->text();
                auto producator = txtProducator->text();
                auto substanta = txtSubstanta->text();
                validate(denumire.toStdString(), getInt(pret), producator.toStdString(), substanta.toStdString());
                const auto& m = serv.search(denumire.toStdString(), producator.toStdString());
                for (int i = 0; i < lst->count(); i++) {
                    auto* item = lst->item(i);
                    if (item->data(Qt::UserRole).toString() == QString::fromStdString(m.getDenumire())) {
                        lst->setCurrentItem(item);
                        lst->scrollToItem(item);
                        break;
                    }
                }
            }
            catch(GUIException& err){
                QMessageBox::warning(this, "Eroare la cautarea medicamentului!!", err.getMessage());
            }
            catch (RepoException& err) {
                QMessageBox::warning(this, "Eroare la cautarea medicamentului!!", QString::fromStdString(err.getMessage()));
            }
        });

        QObject::connect(btnReteta, &QPushButton::clicked, [&]() {
            try {
                GUIReteta = new RetetaCRUDGUI(serv);
            }
            catch (RetetaException& err) {
                QMessageBox::warning(this, "Eroare la vizualizarea retetei!!", QString::fromStdString(err.getMessage()));
            }
        });

        QObject::connect(btnRetetaRO, &QPushButton::clicked, [&]() {
            try {
                GUIRetetaRO = new RetetaReadOnlyGUI(serv);
            }
            catch (RetetaException& err) {
                QMessageBox::warning(this, "Eroare la vizualizarea retetei!!", QString::fromStdString(err.getMessage()));
            }
        });

        QObject::connect(btnAddToReteta, &QPushButton::clicked, [&]() {
            try {
                if (lst->selectedItems().isEmpty()) {
                    throw GUIException({ "Nu ati selectat un medicament pentru adaugare la reteta!" });
                }
                QListWidgetItem* selectedItem = lst->currentItem();
                QString denumire = selectedItem->data(Qt::UserRole).toString();
                auto it = std::find_if(serv.getAll().begin(), serv.getAll().end(), [&](const auto& med) {
                    return QString::fromStdString(med.getDenumire()) == denumire;
                    });
                if (it != serv.getAll().end()) {
                    serv.addToReteta(*it);
                    QMessageBox::information(this, "Reteta", "Medicamentul a fost adaugat la reteta!!");
                }
                //loadTable(serv.getRetetaAll());
            }
            catch (GUIException& err) {
                QMessageBox::warning(this, "Eroare la cautarea medicamentului!!", err.getMessage());
            }
        });

        QObject::connect(comboSort, &QComboBox::currentTextChanged, [&]() {
            QString tipSelectat = comboSort->currentText();
            vector<Medicament> listaSortata;
            if (tipSelectat == "Nesortat") {
                listaSortata = serv.getAll();
            }
            else if(tipSelectat == "Sortare dupa denumire") {
                listaSortata = serv.sort(compare_denumire);
            }
            else if (tipSelectat == "Sortare dupa producator") {
                listaSortata = serv.sort(compare_producator);
            }
            else if (tipSelectat == "Sortare dupa substanta + pret") {
                listaSortata = serv.sort(compare_subst_pret);
            }
            lst->clear();
            for (const auto& el : listaSortata) {
                auto* item = new QListWidgetItem(QString::fromStdString("Denumire: " + el.getDenumire() + ", Pret: " + std::to_string(el.getPret())
                    + ", Producator: " + el.getProducator() + ", Substanta: " + el.getSubstanta()));
                item->setData(Qt::UserRole, QString::fromStdString(el.getDenumire()));
                lst->addItem(item);
            }
        });


        QObject::connect(comboFilter, &QComboBox::currentTextChanged, [&]() {
            try {
                QString tipSelectat = comboFilter->currentText();
                vector<Medicament> listaFiltrata;
                if (tipSelectat == "Nefiltrat") {
                    listaFiltrata = serv.getAll();
                }
                else if (tipSelectat == "Filtreaza dupa pret") {
                    int pret = getInt(txtPret->text());
                    if (pret < 0)
                        throw GUIException({ "Nu ati introdus un pret valid!" });
                    listaFiltrata = serv.filter_pret(pret);
                }
                else if (tipSelectat == "Filtreaza dupa substanta activa") {
                    auto substanta = txtSubstanta->text();
                    if (substanta.isEmpty())
                        throw GUIException({ "Nu ati introdus o substanta valida!" });
                    listaFiltrata = serv.filter_subst(substanta.toStdString());
                }

                lst->clear();
                for (const auto& el : listaFiltrata) {
                    auto* item = new QListWidgetItem(QString::fromStdString("Denumire: " + el.getDenumire() + ", Pret: " + std::to_string(el.getPret())
                        + ", Producator: " + el.getProducator() + ", Substanta: " + el.getSubstanta()));
                    item->setData(Qt::UserRole, QString::fromStdString(el.getDenumire()));
                    lst->addItem(item);
                }
            }
            catch (GUIException& err) {
                QMessageBox::warning(this, "Eroare la filtrarea medicamentelor!!", err.getMessage());
            }
            catch (RepoException& err) {
                QMessageBox::warning(this, "Eroare la filtrarea medicamentelor!!", QString::fromStdString(err.getMessage()));
            }
        });
    }

	void initGUI() {
        auto lyMain = new QHBoxLayout{};
        this->setLayout(lyMain);

        auto lyList = new QVBoxLayout{};
        lyList->addWidget(lst);

        auto lySortFilter = new QHBoxLayout{};
        lyList->addLayout(lySortFilter);
        comboSort->addItem("Nesortat");
        comboSort->addItem("Sortare dupa denumire");
        comboSort->addItem("Sortare dupa producator");
        comboSort->addItem("Sortare dupa substanta + pret");
        lySortFilter->addWidget(comboSort);

        comboFilter->addItem("Nefiltrat");
        comboFilter->addItem("Filtreaza dupa pret");
        comboFilter->addItem("Filtreaza dupa substanta activa");
        lySortFilter->addWidget(comboFilter);
        lyMain->addLayout(lyList);

        auto lyFormBtns = new QVBoxLayout{};
        lyMain->addLayout(lyFormBtns);

        auto formLy = new QFormLayout{};
        formLy->addRow("Denumire", txtDenumire);
        formLy->addRow("Pret", txtPret);
        formLy->addRow("Producator", txtProducator);
        formLy->addRow("Substanta", txtSubstanta);
        lyFormBtns->addLayout(formLy);


        auto lyBtns = new QHBoxLayout{};
        lyBtns->addWidget(btnAdd);
        lyBtns->addWidget(btnDelete);
        lyBtns->addWidget(btnModify);
        lyBtns->addWidget(btnSearch);
        lyBtns->addWidget(btnExit);
        lyFormBtns->addLayout(lyBtns);

        auto lyReteta = new QHBoxLayout{};
        lyReteta->addWidget(btnReteta);
        lyReteta->addWidget(btnRetetaRO);
        lyReteta->addWidget(btnAddToReteta);
        lyFormBtns->addLayout(lyReteta);
	}

    bool validate(const string& denumire, int pret, const string& producator, const string& substanta) {
        vector<QString> errors;
        if (denumire.empty())
            errors.emplace_back("Nu ati introdus o denumire valida!\n");
        if (producator.empty())
            errors.emplace_back("Nu ati introdus un producator valid!\n");
        if (substanta.empty())
            errors.emplace_back("Nu ati introdus o substanta valida!\n");
        if (pret < 0)
            errors.emplace_back("Nu ati introdus un pret valid!\n");
        if (errors.empty())
            return true;
        throw GUIException(errors);
    }

    /*void loadTable(const vector<Medicament>& medicamente) {
        tbl->clearContents();
        tbl->setRowCount(medicamente.size());
        for (int i = 0; i < medicamente.size(); i++) {
            const auto& m = medicamente.at(i);
            tbl->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m.getDenumire())));
            tbl->setItem(i, 1, new QTableWidgetItem(QString::number(m.getPret())));
            tbl->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m.getProducator())));
            tbl->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(m.getSubstanta())));
        }
    }*/

    int getInt(const QString& nrCitit) {
        bool invalid = (nrCitit.isEmpty());
        int nr = 0;
        for (auto& ch : nrCitit.toStdString()) {
            if ('0' <= ch && ch <= '9')
                nr = nr * 10 + (ch - '0');
            else
                invalid = true;	//invalid daca gaseste macar un caracter non cifra
        }
        if (invalid) {
            nr = -1;
        }
        return nr;
    }
};
