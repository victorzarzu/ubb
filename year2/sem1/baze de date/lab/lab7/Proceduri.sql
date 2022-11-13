CREATE PROCEDURE UpdateVersiune1
AS
BEGIN
	SET NOCOUNT ON;

	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate DECIMAL(18, 4);

	UPDATE Versiune
	SET Versiune = 1;

	PRINT 'S-a schimbat cantitatea de materiale de la piese de la tipul real la decimal si baza de date este acum la versiunea 1'
END;
GO

CREATE PROCEDURE DownVersiune1
AS
BEGIN
	SET NOCOUNT ON;

	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate REAL;

	UPDATE Versiune
	SET Versiune = 0;

	PRINT 'S-a dat undo la schimbarea cantitatii de materiale de la tipul real la decimal si baza de date este acum la versiunea 0'
END;
GO

CREATE PROCEDURE UpdateVersiune2
AS
	IF EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_LiniiAsamblare_AnRenovare')
	BEGIN	
		PRINT 'Exista deja o constrangere de tip default pe anul de renovare al tabelei LiniiAsamblare';
	END
	ELSE
		BEGIN
		SET NOCOUNT ON;

		ALTER TABLE LiniiAsamblare
		ADD CONSTRAINT DF_LiniiAsamblare_AnRenovare DEFAULT YEAR(GETDATE()) FOR AnRenovare;

		UPDATE Versiune
		SET Versiune = 2;

		PRINT 'S-a adaugat o valoarea default pentru campul AnRenovare din tabela Linii Asamblare si baza de date este acum la versiunea 2'
		END
GO

CREATE PROCEDURE DownVersiune2
AS
	IF NOT EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'DF_LiniiAsamblare_AnRenovare')
	BEGIN
		PRINT 'Nu exista o constrangere de tip default pe anul de renovare al tabelei LiniiAsamblare';
	END
	ELSE
	BEGIN
		SET NOCOUNT ON;

		ALTER TABLE LiniiAsamblare
		DROP CONSTRAINT DF_LiniiAsamblare_AnRenovare;

		UPDATE Versiune
		SET Versiune = 1;

		PRINT 'S-a dat undo la adaugarea de o valoarea default pentru campul AnRenovare din tabela Linii Asamblare si baza de date este acum la versiunea 1'
	END
GO

CREATE PROCEDURE UpdateVersiune3
AS
	IF EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
	BEGIN
		PRINT 'Exista deja tabela Angajati in baza de date'
	END
	ELSE
	BEGIN
		SET NOCOUNT ON;

		CREATE TABLE Angajati (
			AngajatID INT PRIMARY KEY IDENTITY(1, 1),
			Nume NVARCHAR(30) NOT NULL,
			Prenume NVARCHAR(30) NOT NULL,
			Salariu MONEY NOT NULL
		);

		UPDATE Versiune
		SET Versiune = 3;

		PRINT 'S-a adaugat tabela angajati si baza de date este acum la versiunea 3'
	END
GO

CREATE PROCEDURE DownVersiune3
AS
	IF NOT EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
	BEGIN
		PRINT 'Nu exista o tabela Angajati in baza de date.'
	END
	ELSE
	BEGIN
		SET NOCOUNT ON;

		DROP TABLE Angajati;

		UPDATE Versiune
		SET Versiune = 2;

		PRINT 'S-a dat undo la agaugarea tabelei de angajati si baza de date este acum la versiunea 2'
	END
GO

CREATE PROCEDURE UpdateVersiune4
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
		SET NOCOUNT ON;

		ALTER TABLE Angajati
		ADD LinieAsamblareID INT NOT NULL;

		UPDATE Versiune
		SET Versiune = 4;

		PRINT 'S-a adaugat campul LinieAsamblareID in tabela Angajati  si baza de date este acum la versiunea 4'
	END
GO

CREATE PROCEDURE DownVersiune4
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
			SET NOCOUNT ON;

			ALTER TABLE Angajati
			DROP COLUMN LinieAsamblareID;

			UPDATE Versiune
			SET Versiune = 3;

		PRINT 'S-a dat undo la adaugarea campului LinieAsamblareID in tabela Angajati si baza de date este acum la versiunea 3'
		END
GO

CREATE PROCEDURE UpdateVersiune5
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
	BEGIN
		PRINT 'Nu exista tabela Angajati.'
	END
	ELSE IF EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Angajati')
	BEGIN
		PRINT 'Exista constrangerea de cheie straina pe tabela angajati';
	END
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE Angajati
			ADD CONSTRAINT FK_Angajati FOREIGN KEY (LinieAsamblareID) REFERENCES LiniiAsamblare(LinieAsamblareID);

			UPDATE Versiune
			SET Versiune = 5;

			PRINT 'S-a adaugat o constrangere de cheie straina pe campul LinieAsamblareID din tabela Angajati si baza de date este acum la versiunea 5'
		END
GO

CREATE PROCEDURE DownVersiune5
AS	
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
	BEGIN
		PRINT 'Nu exista tabela Angajati.'
	END
	ELSE IF NOT EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Angajati')
		PRINT 'Nu exista constrangerea de cheie straina pe tabela angajati';
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE Angajati
			DROP CONSTRAINT FK_Angajati;

			UPDATE Versiune
			SET Versiune = 4;

			PRINT 'S-a dat undo la adaugarea constrangerii de cheie straina pe campul LinieAsamblareID din tabela Angajati si baza de date este acum la versiunea 4'
		END
GO

CREATE PROCEDURE TransformaVersiune
@VersiuneDorita INT
AS
BEGIN
	DECLARE @VersiuneCurenta INT;
	SELECT @VersiuneCurenta = V.Versiune
	FROM Versiune V;

	IF @VersiuneDorita < 0 OR @VersiuneDorita > 5
	BEGIN
		PRINT 'Argument invalid'
	END
	ELSE
	BEGIN
		SET NOCOUNT ON;

		DECLARE @Procedura VARCHAR(25)

		IF @VersiuneCurenta < @VersiuneDorita
		BEGIN
			SET @VersiuneCurenta = @VersiuneCurenta + 1
			WHILE @VersiuneCurenta <= @VersiuneDorita
			BEGIN
				SET @Procedura = 'UpdateVersiune' + CONVERT(VARCHAR(2), @VersiuneCurenta);
				EXEC @Procedura
				SET @VersiuneCurenta = @VersiuneCurenta + 1
			END
		END
		ELSE
		BEGIN
			WHILE @VersiuneCurenta > @VersiuneDorita
			BEGIN
				SET @Procedura = 'DownVersiune' + CONVERT(VARCHAR(2), @VersiuneCurenta);
				EXEC @Procedura
				SET @VersiuneCurenta = @VersiuneCurenta - 1
			END
		END
	END
END
GO

EXEC TransformaVersiune @VersiuneDorita = 0;