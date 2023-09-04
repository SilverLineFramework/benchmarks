SELECT round (avg (UnitPrice),0) AS AveragePrice,
SUM(UnitsInStock) AS TotalStock,
max(UnitsOnOrder) as MaxOrder
FROM Products;