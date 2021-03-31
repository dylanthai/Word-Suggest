///////////////////////////////////////////////////////////////////////////// 
// Name: Dylan Thai
/////////////////////////////////////////////////////////////////////////////

#include "suggest.h"
#include "words.h"
#include <string.h>
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////// 
// do not modify this constants:
const int SUGGEST_MAX_STRLEN = 63;
const int NO_IND_FOUND = -1;
/////////////////////////////////////////////////////////////////////////////

// check_single_deletions(new_sss_adt, dict, word) adds word to 
//   the new_sss_adt if the paramater word with a single letter 
//   removed is in the dictionary dict
// time: O(n^2)
void check_single_deletions(struct triple_s *new_sss_adt,
                            const struct triple_s *dict,
                            const char *word) {
  int word_len = strlen(word);
  char word_one_off[63] = {0};
  const char *new_word_p = word_one_off;
  int index = 0;

  for (int skip = 0; skip < word_len; skip++) {
    index = 0;
    for (int i = 0; i < word_len; i++) {
      if (i != skip) {
        word_one_off[index] = word[i];
        index++;
      }
    }
    int search_ind = sss_search(dict, new_word_p);
    if (search_ind != -1) {
      sss_add(new_sss_adt, sss_get(dict, search_ind));
    }
  }

}

// check_single_insertions(new_sss_adt, dict, word) adds word to 
//    the new_sss_adt if the paramater word with a single letter  
//    added is in the dictionary dict
// time: O(n^2)
void check_single_insertions(struct triple_s *new_sss_adt,
                             const struct triple_s *dict,
                             const char *word) {
  int word_len = strlen(word) + 1;
  char word_one_more[63] = {0};
  const char *new_word_p = word_one_more;

  int index_orig_word = 0;

  for (int index_skip = 0; index_skip < word_len; index_skip++) {
    index_orig_word = 0;
    for (int index_new_word = 0; index_new_word < word_len;
         index_new_word++) {

      if (index_new_word != index_skip) {
        word_one_more[index_new_word] = word[index_orig_word];
        index_orig_word++;
      }

    }

    for (int character = 'a'; character <= 'z'; character++) {
      word_one_more[index_skip] = character;
      int search_ind = sss_search(dict, new_word_p);
      if (search_ind != NO_IND_FOUND) {
        sss_add(new_sss_adt, sss_get(dict, search_ind));
      }
    }

  }
}

// check_single_substitutions(new_sss_adt, dict, word) adds word
//    to new_sss_adt if when single letter is replaced and the
//    new word is in the dictionary dict
// time: O(n^2)
void check_single_substitutions(struct triple_s *new_sss_adt,
                                const struct triple_s *dict,
                                const char *word) {
  int word_len = strlen(word);
  char word_one_sub[63] = {0};
  char *new_word_p = word_one_sub;

  for (int index = 0; index < word_len ; index++) {
    strcpy(new_word_p, word);

    for (int character = 'a'; character <= 'z'; character++) {

      word_one_sub[index] = character;
      int search_ind = sss_search(dict, new_word_p);
      if (search_ind != NO_IND_FOUND) {
        sss_add(new_sss_adt, sss_get(dict, search_ind));
      }
    }
  }
}

// check_adj_swaps(new_sss_adt, dict, word) adds word to
//    new_sss_adt if when two adjacent characters in word are
//    swapped and the resulting word is in the dictionary dict
// time: O(n^2)
void check_adj_swaps(struct triple_s *new_sss_adt,
                     const struct triple_s *dict,
                     const char *word) {
  
  int word_len = strlen(word);
  char word_one_swap[63] = {0};
  char *new_word_p = word_one_swap;

  for (int index = 0; index < word_len - 1 ; index++) {
    strcpy(new_word_p, word);
    
    char temp = word_one_swap[index];
    word_one_swap[index] = word_one_swap[index + 1];
    word_one_swap[index + 1] = temp;

    int search_ind = sss_search(dict, new_word_p);
    if (search_ind != NO_IND_FOUND) {
      sss_add(new_sss_adt, sss_get(dict, search_ind));
    }
  }

}

//time: O(n^2)
struct triple_s *suggest(const struct triple_s *dict, const char *word) {

  struct triple_s *new_sss_adt = sss_create();

  check_single_deletions(new_sss_adt, dict, word);
  check_single_insertions(new_sss_adt, dict, word);
  check_single_substitutions(new_sss_adt, dict, word);
  check_adj_swaps(new_sss_adt, dict, word);

  return new_sss_adt;
}
