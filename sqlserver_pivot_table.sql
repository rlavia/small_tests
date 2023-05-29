select *
from   (select customer, year, total from sales) temp
pivot  (sum(total) 
        for year in ('2010' as Y_2010,
                     '2011' as Y_2011,
                     '2012' as Y_2012,
                     '2013' as Y_2013,
                     '2014' as Y_2014,
                     '2015' as Y_2015 ) 
       )


