SELECT ShipPostalCode, OrderID, OrderDate, RequiredDate, ShippedDate,ShipAddress
FROM Orders
WHERE ShipPostalCode = '98124';