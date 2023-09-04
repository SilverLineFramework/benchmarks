select i.*, t.name
from invoiceline as i, track as t
on i.trackid = t.trackid;