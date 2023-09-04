SELECT c.CompanyName, count(c.CustomerID) AS NumberofOrders
FROM Customers c
JOIN Orders o
ON o.CustomerID = c.CustomerID
WHERE o.OrderDate >= '1994-12-31'
GROUP BY c.CustomerID
having count(c.CustomerID) > 10;