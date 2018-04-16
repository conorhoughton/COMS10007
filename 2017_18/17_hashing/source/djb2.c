//djb2 hash function for string by Dan Bernstein.
//from http://stackoverflow.com/questions/7666509/hash-function-for-string
//but see http://dmytry.blogspot.co.uk/2009/11/horrible-hashes.html

#include <stdio.h>


int hash(char *str,int table_size)
{
    long hash = 5381;
    int c;

    while (c = *str++)
      hash =( ((hash << 5) + hash) + c)%table_size; /* hash * 33 + c */

    return hash;
}

int main()
{
  int table_size=1009;

  char elbow6[6] = "elbow";
  printf("hash value=%i\n",hash(elbow6,table_size));

  char elbow10[10] = "elbow";
  printf("hash value=%i\n",hash(elbow10,table_size));

  char word1[5] = "lame";
  printf("hash value=%i\n",hash(word1,table_size));

  char word2[5] = "male";
  printf("hash value=%i\n",hash(word2,table_size));

}
