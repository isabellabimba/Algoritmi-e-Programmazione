/*
 ============================================================================
 Name        : Lab04_3.c
 Author      : Priano Isabella S258356
 ============================================================================
 */

/*   '.'        punto, corrisponde con qualsiasi carattere
 *   '[abc]'    gruppo di caratteri, corrisponde se il caratt. e' {'a', 'b', 'c'}
 *   '[^abc]'   gruppo di caratteri invertito, corisponde se NON appartienen a {'a', 'b', 'c'}
 *   '\a'       sequenza per definire MINUSCOLO
 *   '\A'       Non-MINUSCOLO
 */

#include <stdio.h>
#include <ctype.h>

/* Definizioni */

#define MAX_REGEXP_OBJECTS  30    /* Massimo numero di simboli in una regex      */
#define MAX_GRP_CARAT_LEN   40    /* Massima lunghezza di un gruppo di caratteri */


enum { STOP, PUNTO, NEGAZIONE, FINE, CHAR, GRP_CARAT, NEG_GRP_CARAT, MINUSCOLO, MAIUSCOLO };

typedef struct regex_t
{
  unsigned char  type;   /* carattere, punto, etc.                         */
  union
  {
    unsigned char  ch;   /*         singolo carattere                         */
    unsigned char* ccl;  /* OPPURE  puntatore a carattere in gruppo caratteri */
  };
} regex_t;

/* Definizione del puntatore per tipo di dato astratto */
typedef struct regex_t* re_t;

/* Dichiarazioni delle funzioni utilizzate */
static int matchpattern(regex_t* pattern, const char* text);
static int matchcharclass(char c, const char* str);
static int matchone(regex_t p, char c);
static int matchminuscolo(char c);
static int matchmetachar(char c, const char* str);
static int ismetachar(char c);

/* Compilatore della stringa regex in regex_t-array. */
re_t re_compile(const char* pattern);

/* Ricerca corrispondenze del pattern compilato nel testo fornito */
int  re_matchp(re_t pattern, const char* text);
char *cercaRegexp(char *src, const char *regexp);


int main(void)
{
	/* esempio di utilizzo della funzione cercaRegexp */
	char* testo = {"macheFotoscura"};
	char* regExp = {"\\Aoto[sf]cura"};
	printf("\"%s\" in \"%s\" = %s\n", regExp, testo, cercaRegexp(testo,regExp ));

  return 0;
}


/* Funzioni varie */
char *cercaRegexp(char *src, const char *regexp)
{
  int n = re_matchp(re_compile(regexp), src);
  return (n != -1 ? src + n : NULL);
}

int re_matchp(re_t pattern, const char* text)
{
  if (pattern != 0)
  {
    if (pattern[0].type == NEGAZIONE)
    {
      return ((matchpattern(&pattern[1], text)) ? 0 : -1);
    }
    else
    {
      int idx = -1;

      do
      {
        idx += 1;

        if (matchpattern(pattern, text))
        {
          if (text[0] == '\0')
            return -1;

          return idx;
        }
      }
      while (*text++ != '\0');
    }
  }
  return -1;
}

re_t re_compile(const char* pattern)
{
  static regex_t re_compiled[MAX_REGEXP_OBJECTS];
  static unsigned char ccl_buf[MAX_GRP_CARAT_LEN];
  int ccl_bufidx = 1;

  char c;     /* carattere corrente nel pattern   */
  int i = 0;  /* indice nel pattern        */
  int j = 0;  /* indice in  re_compiled    */

  while (pattern[i] != '\0' && (j+1 < MAX_REGEXP_OBJECTS))
  {
    c = pattern[i];

    switch (c)
    {
      /* Meta-caratteri: */
      case '^': {    re_compiled[j].type = NEGAZIONE;         } break;
      case '.': {    re_compiled[j].type = PUNTO;             } break;

      /* Caratteri con sequenza di escape (\a \A): */
      case '\\':
      {
        if (pattern[i+1] != '\0')
        {
          /* Salta il carattere di escape'\\' */
          i += 1;
          /* ... e controlla il carattere successivo */
          switch (pattern[i])
          {
            /* Metacaratteri */
            case 'a': {    re_compiled[j].type = MINUSCOLO;   } break;
            case 'A': {    re_compiled[j].type = MAIUSCOLO;   } break;

            default:
            {
              re_compiled[j].type = CHAR;
              re_compiled[j].ch = pattern[i];
            } break;
          }
        }
      } break;

      /* Gruppo di caratteri: */
      case '[':
      {
        /* Memorizza dove inizia il buffer del gruppo caratteri. */
        int buf_begin = ccl_bufidx;

        /* Controllo se esiste negazione */
        if (pattern[i+1] == '^')
        {
          re_compiled[j].type = NEG_GRP_CARAT;
          i += 1; /* Incrementa i per evitare di includere '^' nel gruppo caratteri */
        }
        else
        {
          re_compiled[j].type = GRP_CARAT;
        }

        /* Copia dei caratteri in [..] nel buffer */
        while (    (pattern[++i] != ']')
                && (pattern[i]   != '\0')) /* nel caso di assenza di ] */
        {
          if (pattern[i] == '\\')
          {
            if (ccl_bufidx >= MAX_GRP_CARAT_LEN - 1)
            {
              fputs("buffer interno superato!\n", stderr);
              return 0;
            }
            ccl_buf[ccl_bufidx++] = pattern[i++];
          }
          else if (ccl_bufidx >= MAX_GRP_CARAT_LEN)
          {
              fputs("buffer interno superato!\n", stderr);
              return 0;
          }
          ccl_buf[ccl_bufidx++] = pattern[i];
        }
        if (ccl_bufidx >= MAX_GRP_CARAT_LEN)
        {
            /* cattura casi del tipo [00000000000000000000000000000000000000][ */
            fputs("buffer interno superato!\n", stderr);
            return 0;
        }
        /* stringa con terminatoe Null */
        ccl_buf[ccl_bufidx++] = 0;
        re_compiled[j].ccl = &ccl_buf[buf_begin];
      } break;

      /* Altri caratteri: */
      default:
      {
        re_compiled[j].type = CHAR;
        re_compiled[j].ch = c;
      } break;
    }
    i += 1;
    j += 1;
  }
  /* 'STOP' e' usato come come indicatore di fine compilazione pattern */
  re_compiled[j].type = STOP;

  return (re_t) re_compiled;
}


/* funzioni per la ricerca delle corrispondeze */

static int matchminuscolo(char c)
{
  return (c == tolower(c));
}

static int ismetachar(char c)
{
  return ((c == 'a') || (c == 'A'));
}

static int matchmetachar(char c, const char* str)
{
  switch (str[0])
  {
    case 'a': return  matchminuscolo(c);
    case 'A': return !matchminuscolo(c);
    default:  return (c == str[0]);
  }
}

static int matchcharclass(char c, const char* str)
{
  do
  {
   if (str[0] == '\\')
    {
      /* carattere di escape: incrementa str-ptr ed esegue match  */
      str += 1;  /* su carattere successivo */
      if (matchmetachar(c, str))
      {
        return 1;
      }
      else if ((c == str[0]) && !ismetachar(c))
      {
        return 1;
      }
    }
    else if (c == str[0])
    {
      return 1;
    }
  }
  while (*str++ != '\0');

  return 0;
}

static int matchone(regex_t p, char c)
{
  switch (p.type)
  {
    case PUNTO:          return 1;
    case GRP_CARAT:      return  matchcharclass(c, (const char*)p.ccl);
    case NEG_GRP_CARAT:  return !matchcharclass(c, (const char*)p.ccl);
    case MINUSCOLO:      return  matchminuscolo(c);
    case MAIUSCOLO:      return !matchminuscolo(c);
    default:             return  (p.ch == c);
  }
}

/* Ricerca ricorsiva corrispondenze */
static int matchpattern(regex_t* pattern, const char* text)
{
  if (pattern[0].type == STOP)
  {
      return 1;
  }
  else if ((pattern[0].type == FINE) && pattern[1].type == STOP)
  {
    return text[0] == '\0';
  }
  else if ((text[0] != '\0') && matchone(pattern[0], text[0]))
  {
    return matchpattern(&pattern[1], text+1);
  }
  else
  {
    return 0;
  }
}



