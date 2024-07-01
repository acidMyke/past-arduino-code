template <class T>
class List: public Printable {
  private:
    int index = 0;
    T list[10];
  public:
    void forEach(void (*)(T));
    bool isEmpty();
    int add(T);
    int indexOf(T);
    int size();
    T get(int);
    T remove(int);
    T getMax();
    T getMin();
    T operator [](int);
    List forEach(T (*)(T));
    List operator = (List<T>);
    List operator + (T);
    operator bool();
    size_t printTo(Print&) const;
};

template <class T>
void List<T>::forEach(void (*function)(T)) {
  for (int i = 0; i < size(); i++)
    function(list[i]);
}

template <class T>
bool List<T>::isEmpty(){
  return index == 0;
}

template <class T>
int List<T>::add(T ele) {
  list[index] = ele;
  return index++;
}

template <class T>
int List<T>::indexOf(T ele) {
  for (int i = 0; i < size(); i++)
    if (list[i] == ele) return i;
  return -1;
}

template <class T>
int List<T>::size() {
  return index;
}

template <class T>
T List<T>::get(int rIndex) {
  if (rIndex > index) return;
  return list[rIndex];
}

template <class T>
T List<T>::remove(int rIndex) {
  if (isEmpty()) return;
  if (rIndex > index) return;
  T buffer = list[rIndex];
  for (int i = 0; i < (index - rIndex); i++)
    list[rIndex + i] = list[rIndex + i + 1];
  index--;
  return buffer;
}

template <class T>
T List<T>::getMax() {
  T max = list[0];
  for (int i = 0; i < size(); i++)
    if (list[i] > max) max = list[i];
  return max;
}

template <class T>
T List<T>::getMin() {
  T min = list[0];
  for (int i = 0; i < size(); i++)
    if (list[i] < min) min = list[i];
  return min;
}

template <class T>
T List<T>::operator [](int rIndex){
  return get(rIndex);
}

template <class T>
List<T> List<T>::forEach(T (*function)(T)) {
  List<T> returnList;
  for (int i = 0; i < size(); i++)
    returnList.add(function(list[i]));
  return returnList;
}

template <class T>
List<T> List<T>::operator =(List<T> li) {
  index = li.index;
  for (int i = 0; i < size(); i++) list[i] = li.list[i];
  return *this;
}

template <class T>
List<T> List<T>::operator +(T ele) {
  add(ele);
  return *this;
}

template <class T>
List<T>::operator bool(){
  return !isEmpty();
}

template <class T>
size_t List<T>::printTo(Print& p) const {
  size_t n = 0;
  if (isEmpty())
    n += p.println("List is Empty");
  else {
    for (int i = 0; i < size(); i++) {
      n += p.print("[" + String(i) + "] ");
      n += p.println(list[i]);
    }
  }
  return n;
}
