#pragma once

#include <QAbstractTableModel>
#include "service.h"
using std::vector;

class TableModel : public QAbstractTableModel, public Observer {
	vector<Medicament> lista;
public:
	TableModel(const vector<Medicament>& lst): lista{ lst }{
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return lista.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << "\n";
		if (role == Qt::DisplayRole) {
			Medicament m = lista.at(index.row());
			if (index.column() == 0)
				return QString::fromStdString(m.getDenumire());
			if (index.column() == 1)
				return QString::number(m.getPret());
			if (index.column() == 2)
				return QString::fromStdString(m.getProducator());
			if (index.column() == 3)
				return QString::fromStdString(m.getSubstanta());
		}
		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				switch (section) {
				case 0: return "Denumire";
				case 1: return "Pret";
				case 2: return "Producator";
				case 3: return "Substanta";
				default: return QVariant();
				}
			}
		}
		return QVariant();
	}

	void update() override {
		beginResetModel();
		endResetModel();
	}

	void setList(const vector<Medicament>& newList) {
		beginResetModel();
		lista = newList;
		endResetModel();
	}
};