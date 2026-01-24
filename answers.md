# Studio 5: Processes

## Base Exercises
1. Contributors:
   - Jonathan Rodriguez Gomez
   
2. Simple Fork:
```
Parent: before fork
Parent: after fork
Child: (PID=31964, PPID=31963)
Parent: the child is dead (child PID=31964)
```

3. tree_fork.c:

```
sammy@mikey:~ $ ./tree_fork 4 > out
sammy@mikey:~ $ cat out 
My generation is 0. (PID=8981, PPID=1312)
My generation is 1. (PID=8982, PPID=8981)
My generation is 1. (PID=8983, PPID=8981)
My generation is 2. (PID=8985, PPID=8983)
My generation is 2. (PID=8986, PPID=8983)
My generation is 2. (PID=8988, PPID=8982)
My generation is 3. (PID=8989, PPID=8985)
My generation is 2. (PID=8984, PPID=1)
My generation is 3. (PID=8987, PPID=1)
My generation is 3. (PID=8994, PPID=1)
My generation is 3. (PID=8991, PPID=1)
My generation is 3. (PID=8998, PPID=1)
My generation is 3. (PID=8992, PPID=8986)
My generation is 3. (PID=8996, PPID=1)
My generation is 3. (PID=8990, PPID=8986)
sammy@mikey:~ $ wc -l out
15 out
```

4. 

## Enrichment Exercises
