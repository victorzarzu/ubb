#pragma once
#include <qabstractitemview.h>
#include <vector>
#include "Masina.h"
#include <qobject.h>

using std::vector;

class MainListModel : public QAbstractListModel {
private:
	vector<Masina> masini;
public:
	MainListModel(const vector<Masina>& masini);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setMasini(const vector<Masina>& masini);
};

