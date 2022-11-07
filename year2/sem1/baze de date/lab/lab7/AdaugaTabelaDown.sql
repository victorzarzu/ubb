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