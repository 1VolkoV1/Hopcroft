#ifndef AUTOMATA_MIN_REGEX_AUTOMATA
#define AUTOMATA_MIN_REGEX_AUTOMATA

class Automata {
  public:

    // here *int* means char (hack for less fns)
    std::vector<int> T;
    std::vector<int> Q;
    int q0;
    std::vector<int> Q_f;
    /**
     * f[current_state][letter_idx] == new_state
     *
     * all missing edges point towards -1
     */
    std::vector<std::vector<int > > f;

    Automata(
      std::vector<int> __T,
      std::vector<int> __Q,
      int __q0,
      std::vector<int> __Q_f,
      std::vector<std::vector<int > > __f
    );
    //test if the Automata accept a word:
    bool test(const char* word);
    const char* match(const char* word);

    
    //print a vector:
    static void printVec(
      std::ostream& stream, std::vector<int> v
    ) {
      stream << "[ ";
      for (int i = 0; i < v.size(); i++) {
        stream << v[i];
        if (i != v.size() - 1) stream << ',';
        stream << ' ';
      }
      stream << ']';
    }
    //make a function of writing to a stream:
    friend std::ostream& operator<< (
      std::ostream& stream, const Automata& a
    ) {
      auto T = a.T;
      auto Q = a.Q;
      auto q0 = a.q0;
      auto Q_f = a.Q_f;
      auto f = a.f;

      stream << "{" << std::endl;

      stream << "\t\"T\": ";
      printVec(stream, T);
      stream << "," << std::endl;

      stream << "\t\"Q\": ";
      printVec(stream, Q);
      stream << "," << std::endl;

      stream << "\t\"q0\": " << q0 << "," << std::endl;

      stream << "\t\"Q_f\": ";
      printVec(stream, Q_f);
      stream << "," << std::endl;

      stream << "\t\"f\": {" << std::endl;
      for (int i = 0; i < f.size(); i++) {
        stream << "\t\t";
        printVec(stream, f[i]);
        stream << "," << std::endl;
      }
      stream << "\t}" << std::endl;

      stream << "}";
      return stream;
    }
};

#endif