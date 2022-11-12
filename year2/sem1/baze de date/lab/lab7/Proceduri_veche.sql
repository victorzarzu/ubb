CREATE PROCEDURE ModificaTipColoana
AS
BEGIN
	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate DECIMAL(18, 4);

	UPDATE Versiune
	SET Versiune = 1;

	PRINT 'S-a schimbat cantitatea de materiale de la piese de la tipul real la decimal'
END;

CREATE PROCEDURE ModificaTipColoanaDown
AS
BEGIN
	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate REAL;

	UPDATE Versiune
	SET Versiune = 0;

	PRINT 'S-a dat undo la schimbarea cantitatii de materiale de la piese de la tipul real la decimal'
END;

CREATE PROCEDURE AdaugaDefault
AS
	IF EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_LiniiAsamblare_AnRenovare')
	BEGIN	
		PRINT 'Exista deja o constrangere de tip default pe anul de renovare al tabelei LiniiAsamblare';
	END
	ELSE
		BEGIN
		ALTER TABLE LiniiAsamblare
		ADD CONSTRAINT DF_LiniiAsamblare_AnRenovare DEFAULT YEAR(GETDATE()) FOR AnRenovare;

		UPDATE Versiune
		SET Versiune = 2;

		PRINT 'S-a adaugat o valoarea default pentru campul AnRenovare din tabela Linii Asamblare'
		END

CREATE PROCEDURE AdaugaDefaultDown
AS
	IF NOT EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_LiniiAsamblare_AnRenovare')
	BEGIN	
		PRINT 'Nu exista o constrangere de tip default pe anul de renovare al tabelei LiniiAsamblare';
	END
	ELSE
		BEGIN
		ALTER TABLE LiniiAsamblare
		DROP CONSTRAINT DF_LiniiAsamblare_AnRenovare;

		UPDATE Versiune
		SET Versiune = 1;

		PRINT 'S-a dat undo la adaugarea de o valoarea default pentru campul AnRenovare din tabela Linii Asamblare'
		END

CREATE PROCEDURE AdaugaTabela
AS
	IF EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
	BEGIN	
		PRINT 'Exista deja tabela Angajati in baza de date'
	END
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

			PRINT 'S-a adaugat tabela angajati'
		END

CREATE PROCEDURE AdaugaTabelaDown
AS
	IF NOT EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
	BEGIN	
		PRINT 'Nu exista o tabela Angajati in baza de date.'
	END
	ELSE
		BEGIN
			DROP TABLE Angajati;

			UPDATE Versiune
			SET Versiune = 2;

			PRINT 'S-a dat undo la agaugarea tabelei de angajati'
		END

CREATE PROCEDURE AdaugaCampNou
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
	BEGIN	
		PRINT 'Nu exista tabela Angajati.'
	END
	ELSE IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Angajati' AND COLUMN_NAME = 'LinieAsamblareID')
	BEGIN	
		PRINT 'Exista deja campul LinieAsamblareID in tabela Angajati'
	END
	ELSE
		BEGIN
			ALTER TABLE Angajati
			ADD LinieAsamblareID INT NOT NULL;

			UPDATE Versiune
			SET Versiune = 4;

			PRINT 'S-a adaugat campul LinieAsamblareID in tabela Angajati'
		END

CREATE PROCEDURE AdaugaCampNouDown
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
	BEGIN	
		PRINT 'Nu exista tabela Angajati.'
	END
	ELSE IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Angajati' AND COLUMN_NAME = 'LinieAsamblareID')
	BEGIN	
		PRINT 'Nu exista campul LinieAsamblareID in tabela Angajati'
	END
	ELSE
		BEGIN
			ALTER TABLE Angajati
			DROP COLUMN LinieAsamblareID;

			UPDATE Versiune
			SET Versiune = 3;

			PRINT 'S-a dat undo la adaugarea campului LinieAsamblareID in tabela Angajati'
		END

CREATE PROCEDURE AdaugaCheieStraina
AS
	IF EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Angajati')
	BEGIN	
		PRINT 'Exista constrangerea de cheie straina pe tabela angajati';
	END
	ELSE
		BEGIN
			ALTER TABLE Angajati
			ADD CONSTRAINT FK_Angajati FOREIGN KEY (LinieAsamblareID) REFERENCES LiniiAsamblare(LinieAsamblareID);

			UPDATE Versiune
			SET Versiune = 5;

			PRINT 'S-a adaugat o constrangere de cheie straina pe campul LinieAsamblareID din tabela Angajati'
		END

CREATE PROCEDURE AdaugaCheieStrainaDown
AS
	IF NOT EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Angajati')
	BEGIN	
		PRINT 'Nu exista constrangerea de cheie straina pe tabela angajati';
	DOWN
	ELSE
		BEGIN
			ALTER TABLE Angajati
			DROP CONSTRAINT FK_Angajati;

			UPDATE Versiune
			SET Versiune = 4;

			PRINT 'S-a dat undo la adaugarea constrangerii de cheie straina pe campul LinieAsamblareID din tabela Angajati'
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

EXEC TransformaVersiune @VersiuneDorita = 5;