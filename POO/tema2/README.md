# Object-Oriented Programming - 2nd Homework

### Constantinescu Vlad 324CB

The source folder contains:

- Main.java: contains custom general methods and the main method
- Secretariat.java: contains the Secretariat class and its variables and
  methods1 
- Student.java: contains the Student class and its variables and methods
- Master.java: contains the Master class and its variables and methods
- Bachelor.java: contains the Bachelor class and its variables and methods
- Course.java: contains the Course class and its variables and methods
- DuplicateCourseException.java: contains the exception class for duplicate
  courses
- DuplicateStudentException.java: contains the exception class for duplicate
  students

## General Implementation
```     
- Read the main method argument and create paths to requested directory.
- Read the input file and create a list of commands.
- Use Collections in Secretariat to store the data.
```

## Classes and Methods

- `Main` contains secretariat, input, filepaths and other String auxiliaries,
as well as the methods: `writeOutput`,`readInput`


- `Secretariat` contains the student map, courses hashmaps, and contains the
methods `addStudent`, `addGrade`, `readGrade`, `changeGrade`, `postGrade`,
`addPreferences`, `enrollStudentBachelor`, `enrollStudentMaster`, `postStudent`
, `addMasterCourse`, `addBachelorCourse`, `allocateCourses`, `postCourse`,


- `Course` contains the course's name, current capacity, maximum capacity and
a list of enrolled students while also containing the methods `setCapacity`,
`getName`. `getCapacity`, `getStudents`, `addStudent`, `getMinimumGrade`,
`toString`

- `Student` contains the student's name, grade, a list of preferences, and the
assigned course implementing Comparable while also containing the methods `setGrade`,
`setAssignedCourse`, `getPreferences`, `getAverage`, `getName`,
`addPreference`, `compareTo`, `compareToAlphabetical`


- `Bachelor` contains the `toString` method


- `Master` contains the `toString` method


- `DuplicateCourseException` contains the constructor


- `DuplicateStudentException` contains the constructor

## Command List and Implementation Details

- `adauga_student` adds a student to the map of students if it doesn't already
  exist with its name as key and the student object as value, of the specified
    type


- `citeste_mediile` searched all "note_" files in the input directory and
  reads the grades of the students from them, adding them to the students


- `posteaza_mediile` writes the grades of the students to the "out" file in
  the output directory


- `contestatie` changes the grade of the student with the given name


- `adauga_curs` adds a course to the courses hashmap if it doesn't already
  exist with its name as key and the course object as value, of the specified
    type


- `adauga_preferinte` adds the preferences to the student with the given name,
reading all the preferences with a String list


- `repartizeaza` parses the preferences of the students and assigns them to
  the courses, if the course is full and their grade is not equal to the last
  enrolled grade, the student is assigned to the next preference. If all
  preferences are full, the student is assigned to the next available course


- `posteaza_curs` writes the courses to the "out" file in the output directory

- `posteaza_studenti` writes the students to the "out" file in the output
  directory, specifying the assigned course

## Bonus

### Assigning left Students
- used allocate method in Secretariat to assign students to courses
- used boolean variables to check if the student is already assigned to a
course
- used a for loop to iterate through the courses and assign students to them
based on the next read course with capacity left