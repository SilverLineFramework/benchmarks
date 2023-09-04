select *
from customer as c, invoice as i
where c.country = 'Brazil' and
c.customerid = i.customerid;