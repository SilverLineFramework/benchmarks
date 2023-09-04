select e.firstname as 'employee first', e.lastname as 'employee last', c.firstname as 'customer first', c.lastname as 'customer last', c.country, i.total
from employee as e
	join customer as c on e.employeeid = c.supportrepid
	join invoice as i on c.customerid = i.customerid;
