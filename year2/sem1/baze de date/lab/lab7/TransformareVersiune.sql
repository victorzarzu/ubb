CREATE PROCEDURE TransformaVersiune
@VersiuneDorita INT
AS
BEGIN
	DECLARE @VersiuneCurenta INT;
	SELECT @VersiuneCurenta = V.Versiune
	FROM Versiune V;

	WHILE @VersiuneDorita != @VersiuneCurenta
		IF @VersiuneCurenta < @VersiuneDorita
			BEGIN
				IF @VersiuneCurenta = 0
					EXEC ModificaTipColoana;
				ELSE IF @VersiuneCurenta = 1
					EXEC AdaugaDefault;
				ELSE IF @VersiuneCurenta = 2
					EXEC AdaugaTabela;
				ELSE IF @VersiuneCurenta = 3
					EXEC AdaugaCampNou;
				ELSE
					EXEC AdaugaCheieStraina;
				SET @VersiuneCurenta = @VersiuneCurenta + 1;
			END
		ELSE 
			BEGIN
				IF @VersiuneCurenta = 1
					EXEC ModificaTipColoanaDown;
				ELSE IF @VersiuneCurenta = 2
					EXEC AdaugaDefaultDown;
				ELSE IF @VersiuneCurenta = 3
					EXEC AdaugaTabelaDown;
				ELSE IF @VersiuneCurenta = 4
					EXEC AdaugaCampNouDown;
				ELSE
					EXEC AdaugaCheieStrainaDown;
				SET @VersiuneCurenta = @VersiuneCurenta - 1;
			END

END

