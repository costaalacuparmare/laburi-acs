public class Main {
  public static void main(String[] args) {
    System.out.println("INNER CLASSES FIRST PART:");
    InfluenzaDetector influenzaDetector = new InfluenzaDetector();

    Mucus fluA = new Mucus(Mucus.FluType.INFLUENZA_A, .7f);
    System.out.println("==========");
    System.out.println(fluA);
    influenzaDetector.checkAllFlyTypes(fluA);

    Mucus fluB = new Mucus(Mucus.FluType.INFLUENZA_B, 22f);
    System.out.println("==========");
    System.out.println(fluB);
    influenzaDetector.checkAllFlyTypes(fluB);

    Mucus covid = new Mucus(Mucus.FluType.COVID, 0.13f);
    System.out.println("==========");
    System.out.println(covid);
    influenzaDetector.checkAllFlyTypes(covid);

    System.out.println('\n');
    System.out.println("INNER CLASSES SECOND PART:");
    IDatabase mysql = new IDatabase() {
      final StudentManager studentManager = new StudentManager(this);
      @Override
      public void connect() {
        System.out.println("Connected to the database.");
      }

      @Override
      public void disconnect() {
        System.out.println("Disconnected from the database.");
      }

      @Override
      public void insert(Object object) {
        Student student = (Student) object;
        if (!studentManager.getStudents().contains(student)) {
          studentManager.getStudents().add(student);
        }
        System.out.println(studentManager);
      }

      @Override
      public void update(Object object, Object newObject) {
        Student student = (Student) object;
        Student replacement = (Student) newObject;
        if (studentManager.getStudents().contains(student)) {
          studentManager.getStudents().set(studentManager.getStudents().indexOf(student), replacement);
        }
        System.out.println(studentManager);
      }

      @Override
      public void delete(Object object) {
        Student student = (Student) object;
        studentManager.getStudents().remove(student);
        System.out.println(studentManager);
      }

      public void afisare() {
        System.out.println(studentManager);
      }

    };

    StudentManager studentManager = new StudentManager(mysql);
    studentManager.runSomeTests();
  }
}