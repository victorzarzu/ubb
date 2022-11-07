CREATE PROCEDURE ModificareTipColoana
AS
BEGIN
	ALTER TABLE MaterialePiese
	ALTER COLUMN Cantitate DECIMAL(18, 4);

	UPDATE Versiune
	SET Versiune = 1;
END;