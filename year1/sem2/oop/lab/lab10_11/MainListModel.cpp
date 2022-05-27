#include "MainListModel.h"

MainListModel::MainListModel(const vector<Masina>& masini) : masini{ masini }{};

int MainListModel::rowCount(const QModelIndex&) const {
	return this->masini.size();
}

QVariant MainListModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		auto masina = this->masini[index.row()];
		return QString("%1").arg(QString::fromStdString(masina.GetNrInmatriculare()));
	}

	return QVariant();
}

void MainListModel::setMasini(const vector<Masina>& masini) {
	this->masini = masini;
	auto topIndex = createIndex(0, 0);
	auto bottomIndex = createIndex(masini.size(), 0);
	emit dataChanged(topIndex, bottomIndex);
}