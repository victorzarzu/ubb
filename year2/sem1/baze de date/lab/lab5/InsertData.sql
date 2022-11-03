USE FabricaElectronice;

-- Insert in LiniiAsamblare
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('STEN 1', 2017);
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('STEN 2', 2019);
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('STEN 3', 2022);
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('TIN 1', 2015);
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('TIN 2', 2019);
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('PER 1', 2018);
INSERT INTO LiniiAsamblare (Nume, AnRenovare) VALUES ('PER 2', 2020);

-- Insert into Piese
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Senzor optic', 5, 1);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('CPU socket', 20, 2);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Conector incarcare Type-C', 3, 5);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Port video HDMI', 4, 4);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Port video DVI', 6, 3);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Port USB', 1, 5);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Jack', 2, 3);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Tranzistor', 0.2, 6);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Ventilator CPU', 4, 2);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Buton mouse', 15, 3);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Rotita mouse', 2, 1);
INSERT INTO Piese (Nume, TimpProductie, LinieAsamblareID) VALUES ('Conector USB', 1, 5);

-- Insert in Furnizori
INSERT INTO Furnizori (Nume, CUI) VALUES ('SC IMPEX SRL', 45125609);
INSERT INTO Furnizori (Nume, CUI) VALUES ('SC CHIMCOMPLEX SRL', 12592801);
INSERT INTO Furnizori (Nume, CUI) VALUES ('Rock Tech Lithium', 12091524);
INSERT INTO Furnizori (Nume, CUI) VALUES ('Thermo Materiale', 14342421);

-- Insert in Facturi
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (1, 154, 1);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (1, 432, 0);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (1, 565, 0);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (2, 113, 1);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (2, 1433, 0);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (3, 1234, 0);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (3, 16453, 0);
INSERT INTO Facturi (FurnizorID, NumarFactura, Platita) VALUES (4, 2231, 1);

-- Insert in Materiale
INSERT INTO Materiale (Nume, UnitateMasura) VALUES ('Nichel', 'Kilogram');
INSERT INTO Materiale (Nume, UnitateMasura) VALUES ('Litiu', 'Kilogram');
INSERT INTO Materiale (Nume, UnitateMasura) VALUES ('Silicon', 'Litru');
INSERT INTO Materiale (Nume, UnitateMasura) VALUES ('Otel', 'Kilogram');
INSERT INTO Materiale (Nume, UnitateMasura) VALUES ('Cupru', 'Kilogram');
INSERT INTO Materiale (Nume, UnitateMasura) VALUES ('Plastic', 'Kilogram');

-- Insert into MaterialeFacturi
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (1, 1, 565, 345, 1346);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (1, 2, 113, 156.6, 3100);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (2, 2, 1433, 1234.32, 544);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (3, 1, 154, 154.9, 356.99);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (3, 3, 1234, 1346, 4768);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (3, 3, 16453, 3045.6, 415.77);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (3, 4, 2231, 4342, 13443);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (4, 1, 432, 345, 5600);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (5, 1, 565, 125, 1800);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (5, 2, 1433, 3256, 1900);
INSERT INTO MaterialeFacturi (MaterialID, FurnizorID, NumarFactura, Cantitate, PretPerUnitate) VALUES (6, 2, 113, 454, 2313);

-- Insert into MaterialePiese
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (1, 1, 0.005);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (2, 1, 0.02);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (2, 2, 0.1);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (2, 8, 0.0002);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (3, 8, 0.0004);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (4, 12, 0.01);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (5, 3, 0.02);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (5, 4, 0.0004);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (5, 5, 0.0003);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (5, 9, 0.002);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (5, 12, 0.02);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (6, 1, 0.012);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (6, 3, 0.1);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (6, 4, 0.002);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (6, 9, 0.6);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (6, 10, 0.3);
INSERT INTO MaterialePiese (MaterialID, PiesaID, Cantitate) VALUES (6, 11, 0.2);

-- Insert in Produse
INSERT INTO Produse (Nume) VALUES ('Placa de baza RTY23');
INSERT INTO Produse (Nume) VALUES ('Placa video RVG 45');
INSERT INTO Produse (Nume) VALUES ('Mouse cu fir H6');
INSERT INTO Produse (Nume) VALUES ('Mouse wireless J7');
INSERT INTO Produse (Nume) VALUES ('Procesor RE 43');
INSERT INTO Produse (Nume) VALUES ('Procesor RE 56');

-- Insert in PieseProduse
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (2, 1, 1);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (4, 2, 2);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (5, 2, 1);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (6, 1, 4);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (8, 5, 16000000);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (8, 6, 20000000);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (9, 5, 1);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (9, 6, 1);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (10, 3, 2);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (10, 4, 2);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (11, 3, 1);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (11, 4, 1);
INSERT INTO PieseProduse (PiesaID, ProdusID, Numar) VALUES (12, 3, 1);

-- Insert in Proprietati
INSERT INTO Proprietati (Nume, UnitateMasura) VALUES ('Rezolutie video', 'Pixeli');
INSERT INTO Proprietati (Nume, UnitateMasura) VALUES ('Latime de banda', 'Gb/s');
INSERT INTO Proprietati (Nume, UnitateMasura) VALUES ('Latenta', 'ms');
INSERT INTO Proprietati (Nume, UnitateMasura) VALUES ('Frecventa', 'Hz');
INSERT INTO Proprietati (Nume, UnitateMasura) VALUES ('Temperatura func', 'C');

-- Insert in ProprietatiPiese
INSERT INTO ProprietatiPiese (ProprietateID, PiesaID, Valoare) VALUES (1, 4, 1080);
INSERT INTO ProprietatiPiese (ProprietateID, PiesaID, Valoare) VALUES (1, 5, 720);
INSERT INTO ProprietatiPiese (ProprietateID, PiesaID, Valoare) VALUES (2, 4, 4.95);
INSERT INTO ProprietatiPiese (ProprietateID, PiesaID, Valoare) VALUES (2, 5, 3.56);
INSERT INTO ProprietatiPiese (ProprietateID, PiesaID, Valoare) VALUES (3, 1, 0.8);
INSERT INTO ProprietatiPiese (ProprietateID, PiesaID, Valoare) VALUES (4, 8, 300000);
