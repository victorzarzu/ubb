/* USE MASTER

IF EXISTS(SELECT NAME FROM sys.databases WHERE NAME = 'FabricaElectronice1')
	DROP DATABASE FabricaElectronice1
END

CREATE DATABASE FabricaElectronice1
GO
USE FabricaElectronice1
GO */

CREATE TABLE Furnizor (
	FurnizorID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(100),
	CUI VARCHAR(15)
);

CREATE TABLE Factura (
	FurnizorID INT FOREIGN KEY REFERENCES Furnizor(FurnizorID),
	NumarFactura INT,
	Platita BIT NOT NULL,
	CONSTRAINT PK_Factura PRIMARY KEY (FurnizorID, NumarFactura)
);

CREATE TABLE Material (
	MaterialID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(50),
	UnitateMasura VARCHAR(15),
);

CREATE TABLE MaterialFactura (
	MaterialID INT FOREIGN KEY REFERENCES Material(MaterialID),
	FurnizorID INT,
	NumarFactura INT,
	Cantitate REAL NOT NULL,
	PretPerUnitate MONEY NOT NULL,
	CONSTRAINT PK_MaterialFactura PRIMARY KEY (MaterialID, FurnizorID, NumarFactura),
	CONSTRAINT FK_MaterialFactura FOREIGN KEY (FurnizorID, NumarFactura) REFERENCES Factura(FurnizorID, NumarFactura)
);

CREATE TABLE LinieAsamblare (
	LinieAsamblareID INT PRIMARY KEY IDENTITY(1, 1),
	Nume VARCHAR(30),
	AnRenovare INT NOT NULL
);

CREATE TABLE Piesa (
	PiesaID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(50),
	TimpProductie REAL NOT NULL,
	LinieAsamblareID INT FOREIGN KEY REFERENCES LinieAsamblare(LinieAsamblareID)
);

CREATE TABLE Proprietate (
	ProprietateID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(20) NOT NULL,
	UnitateMasura NVARCHAR(15) NOT NULL
);

CREATE TABLE ProprietatePiese (
	ProprietateID INT FOREIGN KEY REFERENCES Proprietate(ProprietateID),
	PiesaID INT FOREIGN KEY REFERENCES Piesa(PiesaID),
	Valoare REAL NOT NULL,
	CONSTRAINT PK_ProprietatePiese PRIMARY KEY (ProprietateID, PiesaID)
)

CREATE TABLE MaterialPiese (
	MaterialID INT FOREIGN KEY REFERENCES Material(MaterialID),
	PiesaID INT FOREIGN KEY REFERENCES Piesa(PiesaID),
	Cantitate REAL NOT NULL,
	CONSTRAINT PK_MaterialPiese PRIMARY KEY (MaterialID, PiesaID)
);

CREATE TABLE Produs (
	ProdusID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(50)
);

CREATE TABLE PiesaProdus (
	PiesaID INT FOREIGN KEY REFERENCES Piesa(PiesaID),
	ProdusID INT FOREIGN KEY REFERENCES Produs(ProdusID),
	Numar INT NOT NULL,
	CONSTRAINT PK_PiesaProdus PRIMARY KEY (PiesaID, ProdusID)
);