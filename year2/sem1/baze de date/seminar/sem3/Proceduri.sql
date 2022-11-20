USE ParcDeDistractii;
GO

-- P1
CREATE PROCEDURE InsertSectiune
@nume VARCHAR(50),
@descriere VARCHAR(200)
AS
BEGIN
	INSERT INTO Sectiuni(nume, descriere) VALUES(@nume, @descriere);
END;

EXEC InsertSectiune @nume = 'Flat rides section', @descriere = 'Flat rides are usually considered to be those that move their passengers in a plane generally parallel to the ground';
EXEC InsertSectiune @nume = 'Roller coasters section', @descriere = 'Amusement parks often feature multiple roller coasters of primarily timber or steel construction';
EXEC InsertSectiune @nume = 'Water rides section', @descriere = 'Amusement parks with water resources generally feature a few water rides, such as the log flume, bumper boats, rapids and rowing boats';

SELECT * FROM Sectiuni;
GO

-- P2
CREATE PROCEDURE InsertCategorie
@nume VARCHAR(50)
AS
BEGIN
	IF EXISTS(SELECT * FROM Categorii WHERE nume = @nume)
		PRINT 'Categorie deja existenta';
	ELSE
		INSERT INTO Categorii(nume) VALUES(@nume);
END;
GO

EXEC InsertCategorie @nume = 'Pensionari';
EXEC InsertCategorie @nume = 'Adulti';
EXEC InsertCategorie @nume = 'Copii';


SELECT * FROM Categorii;
GO

-- P3
CREATE PROCEDURE InsertAtractie
	@nume VARCHAR(30),
	@descriere VARCHAR(200),
	@varsta_min INT,
	@sectiune VARCHAR(30)
AS
BEGIN
	IF NOT EXISTS(SELECT nume FROM Sectiuni WHERE nume = @sectiune)
		EXEC InsertSectiune @sectiune, NULL;

	DECLARE @cod_s AS INT;
	SELECT TOP 1 @cod_s = cod_s FROM Sectiuni WHERE nume = @sectiune; 
	INSERT INTO Atractii(nume, descriere, varsta_min, cod_s) VALUES(@nume, @descriere, @varsta_min, @cod_s);
END

EXEC InsertAtractie @nume = 'Montagne russe', @descriere = 'Descriere', @varsta_min = 12, @sectiune = 'Roller coasters section';
EXEC InsertAtractie @nume = 'Dark train', @descriere = 'Transport', @varsta_min = 16, @sectiune = 'Dark rides section';

SELECT * FROM Atractii;
SELECT * FROM Sectiuni;
GO;

-- P4
CREATE PROCEDURE ExistaVizitator
	@email VARCHAR(25)
AS
BEGIN
	DECLARE @cod AS INT;
	SET @cod = NULL;

	SELECT @cod = cod_v FROM Vizitatori WHERE email = @email;
	IF @cod IS NULL
		RAISERROR('Nu exista niciun vizitator cu acest mail', 7, 0);
	ELSE 
		RETURN @cod;
END