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