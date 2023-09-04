SELECT City,CompanyName,ContactName,city
FROM Customers
WHERE City LIKE "%L%"
ORDER BY ContactName;