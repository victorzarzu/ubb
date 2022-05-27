#include "GeneralTableModel.h"

GeneralTableModel::GeneralTableModel(const vector<Masina>& masini) : masini{ masini } {};

int GeneralTableModel::rowCount(const QModelIndex &) const {
	return this->masini.size();
}

int GeneralTableModel::columnCount(const QModelIndex&) const {
	return 4;
}

bool GeneralTableModel::insertRows(int row, int count, const QModelIndex& parent) {
	beginInsertRows(parent, row, row + count - 1);
	endInsertRows();
	return true;
}

bool GeneralTableModel::removeRows(int row, int count, const QModelIndex& parent) {
	beginRemoveRows(parent, row, row + count - 1);
	endRemoveRows();
	return true;
}

QVariant GeneralTableModel::data(const QModelIndex& index, int role) const {
	if (role == Qt::DisplayRole) {
		auto masina = this->masini[index.row()];

		if (index.column() == 0) {
			return QString::fromStdString(masina.GetNrInmatriculare());
		}
		else if (index.column() == 1) {
			return QString::fromStdString(masina.GetProducator());
		}
		else if (index.column() == 2) {
			return QString::fromStdString(masina.GetModel());
		}
		else if (index.column() == 3) {
			return QString::fromStdString(masina.GetTip());
		}
	}
	return QVariant{};
}

QVariant GeneralTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return QString("Numar");
			}
			else if (section == 1) {
				return QString("Producator");
			}
			else if (section == 2) {
				return QString("Model");
			}
			else {
				return QString("Tip");
			}
		}
	}
	return QVariant{};
}

void GeneralTableModel::setMasini(const vector<Masina>& masini) {
	//if (rowCount()) {
	//	this->removeRows(0, rowCount());
	//}
	if (rowCount() > masini.size()) {
		this->removeRows(masini.size(), rowCount() - masini.size());
	}
	else if (rowCount() < masini.size()) {
		this->insertRows(rowCount(), masini.size() - rowCount());
	}
	
	this->masini = masini;
	auto topIndex = createIndex(0, 0);
	auto bottomIndex = createIndex(rowCount(), columnCount());

	//this->insertRows(0, rowCount());

	emit dataChanged(topIndex, bottomIndex);
	qDebug() << bottomIndex.row() << " " << bottomIndex.column();
}