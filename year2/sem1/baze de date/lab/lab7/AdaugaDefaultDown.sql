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

EXEC AdaugaDefaultDown;