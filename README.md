# Makefile Dependency Simulator 2017

## Description

Basically simulates the dependencies of updating files based on a primitive "makefile" created by the user. So when a file is updated, only the required files are rebuilt.

Input commands are as follows:
- `target: source` -> creates a dependency relation where `target` file depends on `source` file
- `touch file` -> tells the program that `file` has been updated.
- `make file` -> this tells the program that `file` should be rebuilt from the files it depends on

### Example 1: 

Input:
```
a: b
touch b
touch b
touch b
```

Output:
```
b updated at time 1
b updated at time 2
b updated at time 3
```

### Example 2: 
Updating non-leaf objects does not make sense.

Input:
```
a: b 
touch a
```

Output:
```
Cannot update non-leaf object
```

### Example 3:
"Making" the file

Input:
```
a: b
a: c
b: d
c: e
touch e
make a
```

Output:
```
e updated at time 1
Building c
Building a
```

Notice that only files which require e are rebuilt.
