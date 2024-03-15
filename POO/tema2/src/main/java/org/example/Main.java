package org.example;

import java.io.*;
import java.util.*;

public class Main {

  /* Macros used for file paths */
  public final static String FILEPATH = "src/main/resources/";
  public final static String IN = ".in";
  public final static String OUT = ".out";

  /* Function that writes the output to a file */
  public static void writeOutput(String filepath, String content) {
    try {
      FileWriter fw = new FileWriter(filepath, true);
      BufferedWriter bw = new BufferedWriter(fw);
      PrintWriter out = new PrintWriter(bw);
      out.println(content);
      out.close();
    } catch (IOException e) {
      System.out.println("An error occurred.");
      throw new RuntimeException(e);
    }
  }

  /* Function that reads the input from a file and returns it as string */
  public static String readInput(String filepath) throws FileNotFoundException {
   File file = new File(filepath);
    Scanner scanner = new Scanner(file);
    StringBuilder sb = new StringBuilder();
    while (scanner.hasNextLine()) {
      sb.append(scanner.nextLine());
      sb.append("\n");
    }
    scanner.close();
    return sb.toString();
  }
  public static void main(String[] args) throws IOException {
    /* declaration of secretariat */
    Secretariat secretariat = new Secretariat();

    /* correct parameters */
    if (args.length != 1) {
      System.out.println("Enter a valid parameter!");
      System.exit(1);
    }

    /* declaration of file paths */
    String testName = args[0];
    String filepath = FILEPATH + testName + "/";
    String outFile = filepath + testName + OUT;

    /* reading the input information */
    String input = readInput(filepath + testName + IN);
    List<String> lines = List.of(input.split("\n"));

    /* parsing input */
    for (String fullCommand : lines) {
      /*
       * reading individual commands and separating
       * the command from the arguments
       */
      List<String> command = List.of(fullCommand.split(" - "));
      switch(command.get(0)) {
        /*
        * adds students and verifies their uniqueness
        * otherwise, throws an exception
        */
        case "adauga_student":
          String studentType = command.get(1);
          String studentName = command.get(2);
          if (studentType.equals("master")) {
            try {
              secretariat.addStudent(new Master(studentName));
            } catch (DuplicateStudentException e) {
              writeOutput(outFile, e.getMessage());
            }
            break;
          }
          if (studentType.equals("licenta")) {
            try {
              secretariat.addStudent(new Bachelor(studentName));
            } catch (DuplicateStudentException e) {
              writeOutput(outFile, e.getMessage());
            }
            break;
          }
          /* if student type is not master or bachelor, then prints error */
          writeOutput(outFile, "Invalid arguments to command");
          break;
        /* adds grades to students */
        case "citeste_mediile":
          /* used to read all the files with notes in the folder */
          File folder = new File(filepath);
          List<File> listOfFiles =
                  List.of(Objects.requireNonNull(folder.listFiles()));
          for (File file : listOfFiles) {
            if (file.isFile() && file.getName().startsWith("note_")) {
               secretariat.readGrade(filepath, file);
            }
          }
          break;
        /* prints the students and their grades */
        case "posteaza_mediile" :
          secretariat.postGrade(outFile);
          break;
        /* changes the grade of a student */
        case "contestatie" :
          String studentCheckName = command.get(1);
          double newGrade = Double.parseDouble(command.get(2));
          secretariat.changeGrade(studentCheckName, newGrade);
          break;
        /*
         * adds courses and verifies their uniqueness
         * otherwise, throws an exception
         */
        case "adauga_curs" :
          String courseType = command.get(1);
          String courseName = command.get(2);
          int capacity = Integer.parseInt(command.get(3));
          if (courseType.equals("licenta")) {
            try {
              secretariat.addBachelorCourse(new Course<>(courseName, capacity));
            } catch (DuplicateCourseException e) {
              writeOutput(outFile, e.getMessage());
            }
            break;
          }
          if (courseType.equals("master")) {
            try {
              secretariat.addMasterCourse(new Course<>(courseName, capacity));
            } catch (DuplicateCourseException e) {
              writeOutput(outFile, e.getMessage());
            }
            break;
          }
          /* if the course type is not master or bachelor, then prints error */
          writeOutput(outFile, "Invalid arguments to command");
          break;
        /* adds preferences to students */
        case "adauga_preferinte" :
          String studentNamePreference = command.get(1);
          List<String> preferences = new ArrayList<>();
          for (int i = 2; i < command.size(); i++)
            preferences.add(command.get(i));
          for (String preference : preferences) {
            secretariat.addPreference(studentNamePreference, preference);
          }
          break;
        /* allocates courses to students */
        case "repartizeaza" :
          secretariat.allocateCourses();
          break;
        /* prints the courses and the students allocated to them */
        case "posteaza_curs" :
          String coursePostName = command.get(1);
          secretariat.postCourse(outFile, coursePostName);
          break;
        /* prints the students and the courses allocated to them */
        case "posteaza_student" :
          String studentPostName = command.get(1);
          secretariat.postStudent(outFile, studentPostName);
          break;
        /* if the command is not valid, then prints error */

        default:
          writeOutput(outFile, "Invalid command");
          break;
      }
    }
  }
}
