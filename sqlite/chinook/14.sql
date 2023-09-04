select billingcountry, count(billingcountry) as '# of invoices'
from invoice
group by billingcountry;