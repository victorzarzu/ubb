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