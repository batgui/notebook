
## 几个常用的查询employee工资的sql语句

1. return employee record with max salary
```sql
select * 
from employee
where salary = (select Max(salary) from employee)
```

2. select highest salary in employee table
```sql
select Max(salary) from employee
```

3. select highest salary in employee

```sql
select Max(salary)
from employee
where salary Not in (select Max(salary) from employee)
```

4. select range of employee on id

```sql
select * 
from employee
where employ_id betwween 2001 and 2011
```

5. select employee name, highest salary and department

```sql
select e.first_name, e.last_name e.salary, d.department_name
from employee e Inner Join department d
ON (e.department_id = d.department_id)
where salary IN (select Max(salary) from employee)
```


6. select employee name, highest salary and department for each department

```sql
select e.first_name, e.last_name, e.salary, d.department_name from employee e Inner join Department d ON (e.department_id = d.department_id) where salary IN (select Max(salary) from employee group by department_id)
```


7. Find Nth Highest salary in SQL 
```sql
select  TOP 1 salary from 
(select DISTINCT TOP 2 salary from employee Order by salary Desc) result
Order By salary
```

```sql
WITH RESULT AS {
select salary, DENSE_RANK() over (Order by salary DESC) as DENSERANK
from employee 
}
Select salary
from RESULT
where RESULT.DENSERANK = 2
```


### 几个写出高效sql语句的tips

1. 尽可能的早一点filter

2. predict pushdown 



3. 提高数据库查询效率

4. 在经常需要查询的地方使用索引
5. 索引索引的值的分布应该尽可能的大

6. 避免在where使用！= 或者<>会放弃索引

7. 避免使用or会放弃索引




