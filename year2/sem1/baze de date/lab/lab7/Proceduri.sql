CREATE PROCEDURE ModificaTipColoana
AS
BEGIN
	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate DECIMAL(18, 4);

	UPDATE Versiune
	SET Versiune = 1;
END;

CREATE PROCEDURE ModificaTipColoanaDown
AS
BEGIN
	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate REAL;

	UPDATE Versiune
	SET Versiune = 0;
END;

CREATE PROCEDURE AdaugaDefault
AS
	IF EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_LiniiAsamblare_AnRenovare')
		PRINT 'Exista deja o constrangere de tip default pe anul de renovare al tabelei LiniiAsamblare';
	ELSE
		BEGIN
		ALTER TABLE LiniiAsamblare
		ADD CONSTRAINT DF_LiniiAsamblare_AnRenovare DEFAULT YEAR(GETDATE()) FOR AnRenovare;

		UPDATE Versiune
		SET Versiune = 2;
		END

CREATE PROCEDURE AdaugaDefaultDown
AS
	IF NOT EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_LiniiAsamblare_AnRenovare')
		PRINT 'Nu exista o constrangere de tip default pe anul de renovare al tabelei LiniiAsamblare';
	ELSE
		BEGIN
		ALTER TABLE LiniiAsamblare
		DROP CONSTRAINT DF_LiniiAsamblare_AnRenovare;

		UPDATE Versiune
		SET Versiune = 1;
		END

CREATE PROCEDURE AdaugaTabela
AS
	IF EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
		PRINT 'Exista deja tabela Angajati in baza de date'
	ELSE
		BEGIN
			CREATE TABLE Angajati (
				AngajatID INT PRIMARY KEY IDENTITY(1, 1),
				Nume NVARCHAR(30),
				Prenume NVARCHAR(30),
				Salariu MONEY
			);

			UPDATE Versiune
			SET Versiune = 3;
		END

CREATE PROCEDURE AdaugaTabelaDown
AS
	IF NOT EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
		PRINT 'Nu exista o tabela Angajati in baza de date.'
	ELSE
		BEGIN
			DROP TABLE Angajati;

			UPDATE Versiune
			SET Versiune = 2;
		END

CREATE PROCEDURE AdaugaCampNou
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
		PRINT 'Nu exista tabela Angajati.'
	ELSE IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Angajati' AND COLUMN_NAME = 'LinieAsamblareID')
		PRINT 'Exista deja campul LinieAsamblareID in tabela Angajati'
	ELSE
		BEGIN
			ALTER TABLE Angajati
			ADD LinieAsamblareID INT NOT NULL;

			UPDATE Versiune
			SET Versiune = 4;
		END

CREATE PROCEDURE AdaugaCampNouDown
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
		PRINT 'Nu exista tabela Angajati.'
	ELSE IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Angajati' AND COLUMN_NAME = 'LinieAsamblareID')
		PRINT 'Nu exista campul LinieAsamblareID in tabela Angajati'
	ELSE
		BEGIN
			ALTER TABLE Angajati
			DROP COLUMN LinieAsamblareID;

			UPDATE Versiune
			SET Versiune = 3;
		END

CREATE PROCEDURE AdaugaCheieStraina
AS
	IF EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Angajati')
		PRINT 'Exista constrangerea de cheie straina pe tabela angajati';
	ELSE
		BEGIN
			ALTER TABLE Angajati
			ADD CONSTRAINT FK_Angajati FOREIGN KEY (LinieAsamblareID) REFERENCES LiniiAsamblare(LinieAsamblareID);

			UPDATE Versiune
			SET Versiune = 5;
		END

CREATE PROCEDURE TransformaVersiune
@VersiuneDorita INT
AS
BEGIN
	DECLARE @VersiuneCurenta INT;
	SELECT @VersiuneCurenta = V.Versiune
	FROM Versiune V;

	WHILE @VersiuneDorita != @VersiuneCurenta
		IF @VersiuneCurenta < @VersiuneDorita
			BEGIN
				IF @VersiuneCurenta = 0
					EXEC ModificaTipColoana;
				ELSE IF @VersiuneCurenta = 1
					EXEC AdaugaDefault;
				ELSE IF @VersiuneCurenta = 2
					EXEC AdaugaTabela;
				ELSE IF @VersiuneCurenta = 3
					EXEC AdaugaCampNou;
				ELSE
					EXEC AdaugaCheieStraina;
				SET @VersiuneCurenta = @VersiuneCurenta + 1;
			END
		ELSE 
			BEGIN
				IF @VersiuneCurenta = 1
					EXEC ModificaTipColoanaDown;
				ELSE IF @VersiuneCurenta = 2
					EXEC AdaugaDefaultDown;
				ELSE IF @VersiuneCurenta = 3
					EXEC AdaugaTabelaDown;
				ELSE IF @VersiuneCurenta = 4
					EXEC AdaugaCampNouDown;
				ELSE
					EXEC AdaugaCheieStrainaDown;
				SET @VersiuneCurenta = @VersiuneCurenta - 1;
			END

END

EXEC TransformaVersiune @VersiuneDorita = 0;