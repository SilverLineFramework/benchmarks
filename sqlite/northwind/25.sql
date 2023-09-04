SELECT s.SupplierID, p.ProductName, S.CompanyName
FROM Suppliers s
JOIN Products p
ON s.SupplierID = p.SupplierID
WHERE s.CompanyName IN ('Exotic Liquids','Specialty Biscuits, Ltd.','Escargots Nouveaux')
ORDER BY s.SupplierID;