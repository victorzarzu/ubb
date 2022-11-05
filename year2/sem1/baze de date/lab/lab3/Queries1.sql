USE FabricaElectronice1

-- 1. Produsele care contin piese din plastic, numarul pieselor din plastic si cantitatea de plastic pentru care cantitatea este cel putin 0.5
SELECT PR.Nume, COUNT(DISTINCT P.PiesaID) AS NumarPiese, CAST(SUM(MP.Cantitate) as decimal(10, 3)) AS Cantitate
FROM Produse PR, Piese P, PieseProduse PP, Materiale M, MaterialePiese MP
WHERE PR.ProdusID = PP.ProdusID AND PP.PiesaID = P.PiesaID AND P.PiesaID = MP.PiesaID AND MP.MaterialID = M.MaterialID AND M.Nume = 'Plastic'
GROUP BY PR.ProdusID, PR.Nume
HAVING CAST(SUM(MP.Cantitate) as decimal(10, 3)) >= 0.5;

-- 2. Materialele care nu sunt platite si suma de plata pentru fiecare in functie de furnizor
SELECT M.Nume, SUM(MF.Cantitate * MF.PretPerUnitate) AS SumaPlata, FUR.Nume
FROM Materiale M, Facturi F, MaterialeFacturi MF, Furnizori FUR
WHERE M.MaterialID = MF.MaterialID AND MF.FurnizorID = F.FurnizorID
	AND F.NumarFactura = MF.NumarFactura AND F.Platita = 0 AND FUR.FurnizorID = MF.FurnizorID
GROUP BY M.MaterialID, M.Nume, FUR.Nume;

-- 3. Produsul impreuna cu piesele pe care le are si numarul lor
SELECT PR.Nume, P.Nume, PP.Numar
FROM Produse PR, Piese P, PieseProduse PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID;

-- 4. Timpul mediu de producere cu 3 zecimale a pieselor pentru fiecare linie de asamblare pentru cele 
-- care media este sub 5 minute impreuna cu numarul de piese produse pe acea linie
SELECT LA.Nume, CAST(AVG(P.TimpProductie) AS decimal(10, 3)) AS MedieTimp, COUNT(DISTINCT P.PiesaID) AS NumarPiese
FROM LiniiAsamblare LA, Piese P
WHERE P.LinieAsamblareID = LA.LinieAsamblareID
GROUP BY LA.AnRenovare, LA.Nume
HAVING AVG(P.TimpProductie) < 5;

-- 5. Furnizorii la care exista facturi neplatite
SELECT DISTINCT FUR.Nume
FROM Furnizori FUR
INNER JOIN Facturi FCT ON FUR.FurnizorID = FCT.FurnizorID
WHERE FCT.Platita = 0;

-- 6. Timpul maxim de productie al unei piese pentru fiecare produs si numarul de piese
SELECT PR.Nume, TimpMaximPiesa = MAX(P.TimpProductie), COUNT(DISTINCT PP.PiesaID) as NumarPiese
FROM Produse PR, Piese P, PieseProduse PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID
GROUP BY PR.ProdusID, PR.Nume;

-- 7. Furnizorii, tipul facturilor de la ei (platite neplatite) si valoarea facturii
SELECT FUR.Nume, FCT.Platita, SUM(MF.Cantitate * MF.PretPerUnitate) AS Valoare
FROM Furnizori FUR, Facturi FCT, MaterialeFacturi MF
WHERE FUR.FurnizorID = FCT.FurnizorID AND MF.FurnizorID = FCT.FurnizorID 
	AND MF.NumarFactura = FCT.NumarFactura
GROUP BY FUR.Nume, FCT.NumarFactura, FCT.Platita;

-- 8. Numarul de piese si materiale din care este facut fiecare produs
SELECT PR.Nume, COUNT(DISTINCT P.PiesaID) AS NumarPiese, COUNT(DISTINCT M.MaterialID) AS NumarMateriale
FROM Produse PR, Piese P, Materiale M, MaterialePiese MP, PieseProduse PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID AND MP.PiesaID = P.PiesaID AND MP.MaterialID = M.MaterialID
GROUP BY PR.ProdusID, PR.Nume;

-- 9. Proprietatile tuturor pieselor
SELECT P.Nume, PR.Nume, PR.UnitateMasura, PP.Valoare
FROM Piese P, ProprietatiPiese PP, Proprietati PR
WHERE P.PiesaID = PP.PiesaID AND PP.ProprietateID = PR.ProprietateID;

-- 10. Cel mai scump pret la fiecare material cumparat vreodata in functie de furnizor
SELECT FUR.Nume AS Furnizor, M.Nume AS Material, MAX(MF.PretPerUnitate) AS PretMaxim
FROM Furnizori FUR, Facturi FCT, Materiale M, MaterialeFacturi MF
WHERE FUR.FurnizorID = FCT.FurnizorID AND MF.FurnizorID = FUR.FurnizorID AND MF.MaterialID = M.MaterialID
GROUP BY FUR.FurnizorID, FUR.Nume, M.Nume;