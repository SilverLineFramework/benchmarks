SELECT CompanyName,ContactName,Fax
FROM Customers
WHERE Fax IS NULL
ORDER BY ContactName;