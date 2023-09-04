SELECT CustomerID, sum(Freight)
FROM Orders
GROUP BY CustomerID
HAVING sum(Freight) > "200";