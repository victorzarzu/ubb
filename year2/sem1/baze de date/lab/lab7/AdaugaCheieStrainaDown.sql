CREATE PROCEDURE AdaugaCheieStrainaDown
AS
	IF NOT EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_Angajati')
		PRINT 'Nu exista constrangerea de cheie straina pe tabela angajati';
	ELSE
		BEGIN
			ALTER TABLE Angajati
			DROP CONSTRAINT FK_Angajati;

			UPDATE Versiune
			SET Versiune = 4;
		END