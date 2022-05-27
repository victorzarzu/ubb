#pragma once
#include <vector>
#include <qabstractitemview.h>
#include "Masina.h"

using std::vector;

class GeneralTableModel : public QAbstractTableModel {
private:
	vector<Masina> masini;
public:

	GeneralTableModel(const vector <Masina>& masini);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

	bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

	QVariant data(const QModelIndex& parent, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void setMasini(const vector<Masina>& masini);
};

