SELECT OrderID, count(OrderID) as NumberofOrders
FROM "Order Details"
GROUP BY OrderID
ORDER BY NumberofOrders DESC;