USE FabricaElectronice1

-- 1. Piesele care sunt facute din plastic si cantitatea de plastic in kg
SELECT P.Nume, MP.Cantitate
FROM Piesa P
INNER JOIN MaterialPiesa MP ON P.PiesaID = MP.PiesaID
INNER JOIN Material M ON M.MaterialID = MP.MaterialID
WHERE M.Nume = 'Plastic';

-- 2. Furnizorii la care exista facturi neplatite
SELECT DISTINCT FUR.Nume
FROM Furnizor FUR
INNER JOIN Factura FCT ON FUR.FurnizorID = FCT.FurnizorID
WHERE FCT.Platita = 0;

-- 3. Materialele care nu sunt platite si suma de plata pentru fiecare
SELECT DISTINCT M.Nume, SUM(MF.Cantitate * MF.PretPerUnitate) AS SumaPlata
FROM Material M, Factura F, MaterialFactura MF
WHERE M.MaterialID = MF.MaterialID AND MF.FurnizorID = F.FurnizorID
	AND F.NumarFactura = MF.NumarFactura AND F.Platita = 0
GROUP BY M.MaterialID, M.Nume;

-- 4. Suma de plata la furnizori care sunt SC...SRL
SELECT F.Nume, SUM(MF.Cantitate * MF.PretPerUnitate) AS SumaPlata
FROM Furnizor F, Factura FCT, MaterialFactura MF
WHERE F.FurnizorID = FCT.FurnizorID
	AND FCT.NumarFactura = MF.NumarFactura AND MF.FurnizorID = FCT.FurnizorID 
	AND FCT.Platita = 0
GROUP BY F.Nume
HAVING F.Nume LIKE 'SC%SRL';

-- 5. Numarul de piese la care este folosit fiecare material
SELECT M.Nume, NumarPiese = COUNT(P.PiesaID)
FROM Material M, Piesa P, MaterialPiesa MP
WHERE M.MaterialID = MP.MaterialID AND P.PiesaID = MP.PiesaID
GROUP BY M.Nume;

-- 6. Produsul impreuna cu piesele pe care le are si numarul lor
SELECT PR.Nume, P.Nume, PP.Numar
FROM Produs PR, Piesa P, PiesaProdus PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID;

-- 7. Produsele si numarul de piese din care este facut fiecare produs
SELECT PR.Nume, COUNT(DISTINCT P.PiesaID) AS NumarPiese
FROM Produs PR, Piesa P, PiesaProdus PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID
GROUP BY PR.ProdusID, PR.Nume;

-- 8. Numarul de piese care se produc in functie de anul de renovare al liniilor lor de asamblare, considerandu-le doar pe cele renovate dupa 2018 inclusiv
SELECT LA.AnRenovare, NumarPiese = COUNT(*)
FROM LinieAsamblare LA, Piesa P
WHERE LA.LinieAsamblareID = P.LinieAsamblareID
GROUP BY LA.AnRenovare
HAVING LA.AnRenovare >= 2018;

-- 9. Timpul mediu de producere cu 3 zecimale a pieselor pentru fiecare linie de asamblare pentru cele care media este sub 5 minute
SELECT LA.Nume, CAST(AVG(P.TimpProductie) AS decimal(10, 3)) AS MedieTimp
FROM LinieAsamblare LA, Piesa P
WHERE P.LinieAsamblareID = LA.LinieAsamblareID
GROUP BY LA.AnRenovare, LA.Nume
HAVING AVG(P.TimpProductie) < 5;

-- 10. Materialele care au fost cumparate cu cel putin 2000 de unitati monetare per unitate de masura in cel putin o factura
SELECT DISTINCT M.Nume
FROM Material M, MaterialFactura MF
WHERE M.MaterialID = MF.MaterialID AND MF.PretPerUnitate >= 2000;

-- 11. Timpul maxim de productie al unei piese pentru fiecare produs
SELECT PR.Nume, TimpMaximPiesa = MAX(P.TimpProductie)
FROM Produs PR, Piesa P, PiesaProdus PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID
GROUP BY PR.ProdusID, PR.Nume;

/* -- 11. Piesele pentru care timpul de productie este mai mare sau egal cu 15 minute
SELECT P.Nume
FROM Piesa P
WHERE P.TimpProductie >= 15; */