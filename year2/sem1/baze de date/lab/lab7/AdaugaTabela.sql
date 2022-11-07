CREATE PROCEDURE AdaugaTabela
AS
	IF EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Angajati')
		PRINT 'Exista deja tabela Angajati in baza de date.'
	ELSE
		BEGIN
			CREATE TABLE Angajati (
				AngajatID INT PRIMARY KEY IDENTITY(1, 1),
				Nume NVARCHAR(30) NOT NULL,
				Prenume NVARCHAR(30) NOT NULL,
				Salariu MONEY NOT NULL
			);

			UPDATE Versiune
			SET Versiune = 3;
		END