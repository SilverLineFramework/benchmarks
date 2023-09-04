SELECT s.CompanyName,p.ProductName
FROM Categories c
JOIN Products p
ON c.CategoryID = p.CategoryID
JOIN Suppliers s
ON s.SupplierID = p.SupplierID
WHERE CategoryName = "Seafood";