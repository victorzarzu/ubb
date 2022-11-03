USE FabricaElectronice

-- 1. Produsele care contin piese din plastic, numarul pieselor din plastic si cantitatea de plastic pentru care cantitatea este cel putin 0.5
SELECT PR.Nume, COUNT(DISTINCT P.PiesaID) AS NumarPiese, CAST(SUM(MP.Cantitate) as decimal(10, 3)) AS Cantitate
FROM Produse PR
INNER JOIN PieseProduse PP ON PP.ProdusID = PR.ProdusID
INNER JOIN Piese P ON PP.PiesaID = P.PiesaID
INNER JOIN MaterialePiese MP ON MP.PiesaID = P.PiesaID
INNER JOIN Materiale M ON MP.MaterialID = M.MaterialID
WHERE M.Nume = 'Plastic'
GROUP BY PR.ProdusID, PR.Nume
HAVING CAST(SUM(MP.Cantitate) as decimal(10, 3)) >= 0.5;

-- 2. Materialele care nu sunt platite si suma de plata Ppentru fiecare in functie de furnizor
SELECT M.Nume, SUM(MF.Cantitate * MF.PretPerUnitate) AS SumaPlata, FUR.Nume
FROM Materiale M, Facturi F, MaterialeFacturi MF, Furnizori FUR
WHERE M.MaterialID = MF.MaterialID AND MF.FurnizorID = F.FurnizorID
	AND F.NumarFactura = MF.NumarFactura AND F.Platita = 0 AND FUR.FurnizorID = MF.FurnizorID
GROUP BY M.MaterialID, M.Nume, FUR.Nume;

-- 3. Produsul impreuna cu piesele pe care le are si numarul lor pentru cele care au mai putin de 20 de piese
SELECT PR.Nume AS Produs, P.Nume AS Piesa, PP.Numar
FROM Produse PR
INNER JOIN PieseProduse PP ON PR.ProdusID = PP.ProdusID
INNER JOIN Piese P ON P.PiesaID = PP.PiesaID
WHERE PP.Numar < 20;

-- 4. Timpul mediu de producere cu 3 zecimale a pieselor pentru fiecare linie de asamblare pentru cele 
-- care media este sub 5 minute impreuna cu numarul de piese produse pe acea linie
SELECT LA.Nume as LinieAsamblare, CAST(AVG(P.TimpProductie) AS decimal(10, 3)) AS MedieTimp, COUNT(DISTINCT P.PiesaID) AS NumarPiese
FROM LiniiAsamblare LA
INNER JOIN Piese P ON P.LinieAsamblareID = LA.LinieAsamblareID
GROUP BY LA.AnRenovare, LA.Nume
HAVING AVG(P.TimpProductie) < 5;

-- 5. Furnizorii la care exista facturi neplatite
SELECT DISTINCT FUR.Nume as Furnizor
FROM Furnizori FUR
INNER JOIN Facturi FCT ON FUR.FurnizorID = FCT.FurnizorID
WHERE FCT.Platita = 0;

-- 6. Timpul maxim de productie al unei piese pentru fiecare produs si numarul de piese
SELECT PR.Nume AS Produs, TimpMaximPiesa = MAX(P.TimpProductie), COUNT(DISTINCT PP.PiesaID) as NumarPiese
FROM Produse PR
INNER JOIN PieseProduse PP ON PP.ProdusID = PR.ProdusID
INNER JOIN Piese P ON PP.PiesaID = P.PiesaID
GROUP BY PR.ProdusID, PR.Nume;

-- 7. Furnizorii, tipul facturilor de la ei (platite neplatite) si valoarea facturii daca furnizorul este de forma SC...SRL
SELECT FUR.Nume AS Furnizor, FCT.Platita, SUM(MF.Cantitate * MF.PretPerUnitate) AS Valoare
FROM Furnizori FUR, Facturi FCT, MaterialeFacturi MF
WHERE FUR.FurnizorID = FCT.FurnizorID AND MF.FurnizorID = FCT.FurnizorID 
	AND MF.NumarFactura = FCT.NumarFactura AND FUR.Nume LIKE 'SC%SRL'
GROUP BY FUR.Nume, FCT.NumarFactura, FCT.Platita;

-- 8. Numarul de piese si materiale din care este facut fiecare produs unde materialul este cupru
SELECT PR.Nume AS Produs, COUNT(DISTINCT P.PiesaID) AS NumarPiese, COUNT(DISTINCT M.MaterialID) AS NumarMateriale
FROM Produse PR
INNER JOIN PieseProduse PP ON PR.ProdusID = PP.ProdusID
INNER JOIN Piese P ON P.PiesaID = PP.PiesaID
INNER JOIN MaterialePiese MP ON MP.PiesaID = P.PiesaID
INNER JOIN Materiale M ON MP.MaterialID = M.MaterialID
WHERE M.Nume = 'Cupru'
GROUP BY PR.ProdusID, PR.Nume;


SELECT PR.Nume AS Produs, COUNT(DISTINCT P.PiesaID) AS NumarPiese, COUNT(DISTINCT M.MaterialID) AS NumarMateriale
FROM Produse PR, Piese P, Materiale M, MaterialePiese MP, PieseProduse PP
WHERE PR.ProdusID = PP.ProdusID AND P.PiesaID = PP.PiesaID AND MP.PiesaID = P.PiesaID AND MP.MaterialID = M.MaterialID
GROUP BY PR.ProdusID, PR.Nume;

-- 9. Proprietatile tuturor pieselor daca unitatea de masura este in pixeli
SELECT P.Nume AS Piesa, PR.Nume AS Produs, PR.UnitateMasura, PP.Valoare
FROM Piese P
INNER JOIN ProprietatiPiese PP ON P.PiesaID = PP.PiesaID
INNER JOIN Proprietati PR ON PP.ProprietateID = PR.ProprietateID
WHERE PR.UnitateMasura = 'Pixeli'

-- 10. Cel mai scump pret la fiecare material cumparat vreodata in functie de furnizor pentru care pretul maxim pentru furnizorii care nu sunt de tip 'sc...srl'
SELECT FUR.Nume AS Furnizor, M.Nume AS Material, MAX(MF.PretPerUnitate) AS PretMaxim
FROM Furnizori FUR
INNER JOIN Facturi FCT ON FCT.FurnizorID = FUR.FurnizorID
INNER JOIN MaterialeFacturi MF ON MF.FurnizorID = FCT.FurnizorID
INNER JOIN Materiale M ON MF.MaterialID = M.MaterialID
WHERE FUR.Nume NOT LIKE 'SC%SRL'
GROUP BY FUR.FurnizorID, FUR.Nume, M.Nume;