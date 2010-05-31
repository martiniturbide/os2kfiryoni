// tokenizing.h
// used to seperate strings into tokens

// strings are seperated into a linked list of tokens
struct list {
         char *str;
         struct list *next;
       };
typedef struct list List;

// given a string and a list of delimiters, returns
// a linked list of tokens. parsing stops when
// one of the forbidden characters is reached.
// example:
// List* l = parse( user_input, " ", "\0\n" );
List *parse(char *str, char *delimiters, char *forbidden);

// returns length of given list
int length(List *l);
void free_list(List * list);
void add_to_list(List **l, char *element);
