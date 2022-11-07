CREATE PROCEDURE AdaugaCampNou
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Angajati')
		PRINT 'Nu exista tabela Angajati.'
	ELSE IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Angajati' AND COLUMN_NAME = 'LinieAsamblareID')
		PRINT 'Exista deja campul LinieAsamblareID in tabela Angajati'
	ELSE
		BEGIN
			ALTER TABLE Angajati
			ADD LinieAsamblareID INT FOREIGN KEY REFERENCES LiniiAsamblare(LinieAsamblareID);

			UPDATE Versiune
			SET Versiune = 4;
		END