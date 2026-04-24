#include "../default.hpp"

struct Trie {
  bool isend = false;
  Trie *child[26];

  Trie() {
    memset(child, 0, sizeof(child));
  }
  ~Trie() {
    for (i32 i=0; i<26; i++) if (child[i]) delete child[i];
  }

  Trie(const char *s): isend(s[0] == '\0') {
    if (!isend) child[s[0] - 'a'] = new Trie(s+1);
  }
  Trie(const string &s): Trie(s.c_str()) {}

  void insert(const char *s) {
    if (s[0] == '\0') {
      isend = true;
      return;
    }
    
    if (!child[s[0] - 'a']) child[s[0] - 'a'] = new Trie;
    child[s[0] - 'a']->insert(s+1);
  }
  void insert(const string &s) { return insert(s.c_str()); }

  bool find(const char *s) {
    // s가 prefix로 존재하는지 판정.
    if (s[0] == '\0') return true;

    if (!child[s[0] - 'a']) return false;
    return child[s[0] - 'a']->find(s+1);
  }
  bool find(const string &s) { return find(s.c_str()); }

  bool findall(const char *s) {
    // s가 존재하는지 판정.
    if (s[0] == '\0') return isend;

    if (!child[s[0] - 'a']) return false;
    return child[s[0] - 'a']->findall(s+1);
  }
  bool findall(const string &s) { return findall(s.c_str()); }
};
