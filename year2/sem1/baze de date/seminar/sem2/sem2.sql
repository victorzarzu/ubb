CREATE DATABASE ParcDeDistractii;
GO

USE ParcDeDistractii;
GO

CREATE TABLE Sectiuni (
	cod_s INT PRIMARY KEY IDENTITY(1,1),
	nume VARCHAR(50) NOT NULL,
	descriere VARCHAR(200)
);
GO

CREATE TABLE Atractii (
	cod_a INT PRIMARY KEY IDENTITY(1, 1),
	nume VARCHAR(50) NOT NULL,
	descriere VARCHAR(50),
	varsta_min TINYINT,
	cod_s INT FOREIGN KEY REFERENCES Sectiuni(cod_s)
);
GO

CREATE TABLE Categorii (
	cod_c INT PRIMARY KEY IDENTITY(1, 1),
	nume VARCHAR(50) NOT NULL
);
GO

CREATE TABLE Vizitatori (
	cod_v INT PRIMARY KEY IDENTITY(1, 1),
	nume VARCHAR(50) NOT NULL,
	email VARCHAR(25),
	cod_c INT FOREIGN KEY REFERENCES Categorii(cod_c)
);
GO

CREATE TABLE Note (
	cod_a INT FOREIGN KEY REFERENCES Atractii(cod_a),
	cod_v INT FOREIGN KEY REFERENCES Vizitatori(cod_v),
	nota FLOAT NOT NULL,
	CONSTRAINT PK_Note PRIMARY KEY (cod_a, cod_v)
);
GO