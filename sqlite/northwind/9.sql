SELECT ContactName, Address, City
FROM Customers
WHERE Country NOT IN ("Germany","Mexico", "Spain");