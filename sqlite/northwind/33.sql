SELECT s.SupplierID, s.CompanyName, c.CategoryName, p.ProductName, p.UnitPrice
FROM Products p
JOIN Suppliers s
ON s.SupplierID = p.SupplierID
JOIN Categories C
On c.CategoryID = p.CategoryID;