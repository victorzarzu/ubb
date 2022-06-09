#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

#define L 20
#define B 1024

typedef struct rec {
  char* file;
  unsigned char checksum[L];
  int ignore;
  struct rec* next;
}rec;

rec* list;

char* path(char* dir, char* name) {
  char* p = (char*)malloc(strlen(dir) + strlen(name) + 2);
  sprintf(p, "%s/%s", dir, name);

  return p;
}

rec* newrec(char* file) {
  rec* n = (rec*)malloc(sizeof(rec));
  n->file = file;
  n->ignore = 0;
  n->next = NULL;

  return n;
}

int equal(rec* a, rec* b) {
  int i;
  
  for(i = 0;i < L;++i) {
    if(a->checksum[i] != b->checksum[i]) {
      return 0;
    }
  }

  return 1;
}

void sha1(rec* r) {
  unsigned char buf[B];   
  int fd, k;
  EVP_MD_CTX* ctx;

  fd = open(r->file, O_RDONLY);
  if(fd < 0) {
    r->ignore = 1;
    return;
  }

  ctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(ctx, EVP_sha1(), NULL);

  while(1) {
    k = read(fd, buf, B);
    if(k < 0) {
      r->ignore = 1;
      close(fd);
      return;
    }

    if(k == 0) {
      break;
    }
    EVP_DigestUpdate(ctx, buf, k);
  }

  close(fd);
  EVP_DigestFinal_ex(ctx, r->checksum, NULL);
  EVP_MD_CTX_destroy(ctx);
}

rec* find(char* dir, rec** head, rec* tail) {
  struct dirent* e;
  DIR* d = opendir(dir);
  rec* t = tail;

  if(d != NULL) {
    while((e = readdir(d)) != NULL) {
      if(e->d_type == DT_DIR && strcmp(e->d_name, ".") != 0 && strcmp(e->d_name, "..") != 0) {
        char* subd = path(dir, e->d_name);
        t = find(subd, head, t);
        free(subd);
      }
      else if(e->d_type == DT_REG) {
        if(t == NULL) {
          t = newrec(path(dir, e->d_name)); 
          *head = t;
        } else {
          t->next = newrec(path(dir, e->d_name)); 
          t = t->next;
        }
      }
    }
    closedir(d);
  }

  return t;
}

int main(int argc, char** argv) {
  rec* r;
  rec* x;

  find(argv[1], &list, NULL);

  r = list;
  while(r != NULL) {
    sha1(r);
    r = r->next;
  }

  r = list;
  while(r != NULL) {
    if(!r->ignore) {
      x = list;
      while(x != NULL) {
        if(!x->ignore) {
          if(strcmp(r->file, x->file) != 0 && equal(r, x)) {
            printf("%s = %s\n", r->file, x->file);
          }
        }
        x = x->next;
      }
    }
    r = r->next;
  }

  while(list != NULL) {
    r = list->next;
    free(list->file);
    free(list);
    list = r;
  }

  return 0;
}
