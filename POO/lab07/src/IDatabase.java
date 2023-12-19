public interface IDatabase {
  void connect();
  void disconnect();

  void insert(Object object);
  void update(Object object, Object newObject);
  void delete(Object object);
}