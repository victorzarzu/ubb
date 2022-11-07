CREATE PROCEDURE ModificareTipColoanaDown
AS
BEGIN
	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate REAL;

	UPDATE Versiune
	SET Versiune = 0;
END;