SELECT od.OrderID, c.ContactName,od.UnitPrice,od.Quantity,od.Discount
FROM `Order Details` od
JOIN Orders o
ON od.OrderID = o.OrderID
JOIN Customers c
ON c.CustomerID = o.CustomerID
WHERE od.Discount != '0';