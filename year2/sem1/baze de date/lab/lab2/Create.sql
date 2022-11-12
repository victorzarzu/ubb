CREATE DATABASE FabricaElectronice
GO

USE FabricaElectronice;
GO

CREATE TABLE Furnizori (
	FurnizorID INT PRIMARY KEY IDENTITY(1, 1),
	Nume VARCHAR(50),
	CUI VARCHAR(15) NOT NULL
);
GO

CREATE TABLE Facturi (
	FurnizorID INT FOREIGN KEY REFERENCES Furnizori(FurnizorID),
	NumarFactura INT,
	Platita BIT NOT NULL,
	CONSTRAINT PK_Facturi PRIMARY KEY (FurnizorID, NumarFactura)
);
GO

CREATE TABLE LiniiAsamblare (
	LinieAsamblareID INT PRIMARY KEY IDENTITY(1, 1),
	Nume VARCHAR(30),
	AnRenovare INT NOT NULL
);
GO

CREATE TABLE Materiale (
	MaterialID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(50) NOT NULL,
	UnitateMasura VARCHAR(15) NOT NULL
);
GO

CREATE TABLE MaterialeFacturi (
	MaterialID INT FOREIGN KEY REFERENCES Materiale(MaterialID),
	FurnizorID INT NOT NULL,
	NumarFactura INT NOT NULL,
	Cantitate REAL NOT NULL,
	PretPerUnitate MONEY NOT NULL,
	CONSTRAINT FK_MaterialeFacturi FOREIGN KEY (FurnizorID, NumarFactura) REFERENCES Facturi(FurnizorID, NumarFactura),
	CONSTRAINT PK_MaterialeFacturi PRIMARY KEY (MaterialID, FurnizorID, NumarFactura)
);
GO

CREATE TABLE Piese (
	PiesaID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(50),
	TimpProductie REAL NOT NULL,
	LinieAsamblareID INT FOREIGN KEY REFERENCES LiniiAsamblare(LinieAsamblareID)
);
GO

CREATE TABLE MaterialePiese (
	MaterialID INT FOREIGN KEY REFERENCES Materiale(MaterialID),
	PiesaID INT FOREIGN KEY REFERENCES Piese(PiesaID),
	Cantitate REAL NOT NULL
);
GO

CREATE TABLE Produse (
	ProdusID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(50) NOT NULL
);
GO

CREATE TABLE PieseProduse (
	PiesaID INT FOREIGN KEY REFERENCES Piese(PiesaID),
	ProdusID INT FOREIGN KEY REFERENCES Produse(ProdusID),
	Numar INT NOT NULL,
	CONSTRAINT PK_PieseProduse PRIMARY KEY (PiesaID, ProdusID)
);
GO

CREATE TABLE Proprietati (
	ProprietateID INT PRIMARY KEY IDENTITY(1, 1),
	Nume NVARCHAR(30) NOT NULL,
	UnitateMasura NVARCHAR(15) NOT NULL,
);
GO

CREATE TABLE ProprietatiPiese (
	ProprietateID INT FOREIGN KEY REFERENCES Proprietati(ProprietateID),
	PiesaID INT FOREIGN KEY REFERENCES Piese(PiesaID),
	Valoare REAL NOT NULL,
	CONSTRAINT PK_ProprietatiPiese PRIMARY KEY (ProprietateID, PiesaID)
);
GO

CREATE TABLE Versiune (
	Versiune SMALLINT PRIMARY KEY DEFAULT 0
);