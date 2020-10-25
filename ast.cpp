#include "ast.h"

static unordered_map<string, symbol*> symtab;

struct ast *
new_ast(int nodetype, struct ast *l, struct ast *r)
{
  struct ast *a = new struct ast();
  if (!a) {
    yyerror("Out of memory");
    exit(1);
  }

  a->nodetype = nodetype;
  a->l = l;
  a->r = r;

  return a;
}

struct ast *
new_num(float val)
{
  struct numval *n = new struct numval();
  if (!n) {
    yyerror("Out of memory");
    exit(1);
  }

  n->nodetype = 'K';
  n->number = val;

  return (struct ast*) n;
}

struct ast *
new_cmp(int cmptype, struct ast *l, struct ast *r)
{
  struct ast *a = new struct ast();
  if (!a) {
    yyerror("Out of memory");
    exit(1);
  }

  a->nodetype = '0' + cmptype;
  a->l = l;
  a->r = r;

  return a;
}

struct ast *
new_func(int functype, struct ast *l)
{
  struct fncall *a = new struct fncall();
  if (!a) {
    yyerror("Out of memory");
    exit(1);
  }

  a->nodetype = 'F';
  a->l = l;
  a->functype = static_cast<builtins>(functype);
  return (struct ast *) a;
}

struct ast *
new_call(struct symbol *s, struct ast *l)
{
  struct ufncall *a = new struct ufncall();
  if (!a) {
    yyerror("Out of memory");
    exit(1);
  }

  a->nodetype = 'C';
  a->l = l;
  a->s = s;

  return (struct ast *) a;
}

struct ast *
new_ref(struct symbol *s)
{
  struct symref *a = new struct symref();
  if (!a) {
    yyerror("Out of memory");
    exit(1);
  }

  a->nodetype = 'N';
  a->s = s;

  return (struct ast *) a;
}

struct ast *
new_flow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el)
{
  struct flow *a = new struct flow();
  if (!a) {
    yyerror("Out of memory");
    exit(1);
  }

  a->nodetype = nodetype;
  a->cond = cond;
  a->tl = tl;
  a->el = el;

  return (struct ast *) a;
}

float
eval(struct ast *a)
{
  float v;
  switch(a->nodetype) {
    case 'K': v = ((struct numval *) a)->number; break;
    case '+': v = eval(a->l) + eval(a->r); break;
    case '-': v = eval(a->l) - eval(a->r); break;
    case '*': v = eval(a->l) * eval(a->r); break;
    case '/': v = eval(a->l) / eval(a->r); break;
    default: printf("Invalid node type: %c\n", a->nodetype);
  }

  return v;
}

void
free_ast(struct ast *a)
{
  if (a == NULL)
    return;
  
  free_ast(a->l);
  free_ast(a->r);

  free(a);
}

void
free_list(list<symbol*>* symlist)
{
  for (symbol *s : *symlist)
    delete s;
  delete symlist;
}

void
yyerror(char const *s, ...)
{
  va_list ap;
  va_start(ap, s);

  fprintf(stderr, "%d: error: ", yylineno);
  fprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}

struct symbol *
lookup(char *s)
{
  string str(s);
  if (symtab.find(s) == symtab.end()) {
    struct symbol *sp = new struct symbol();
    sp->value = 0;
    sp->func = NULL;
    symtab[str] = sp;
  }

  return symtab[str];
}

static float
call_builtin(struct fncall *f)
{
  enum builtins functype = f->functype;
  double v = eval(f->l);

  switch(functype) {
    case B_sqrt:
      return sqrt(v);
    case B_exp:
      return exp(v);
    case B_log:
      return log10(v);
    default:
      yyerror("Unknown builtin");
      return 0;
  }
}

static float
call_user(struct ufncall *f)
{
  struct symbol *fn = f->s;
  struct symlist *sl;
  struct ast *args = f->l;
  float *oldval, *newval;
  float v;
  int nargs;
  int i;

  if (!fn->func) {
    yyerror("call to undefined function");
    return 0;
  }
}

void
dodef(struct symbol *ref, list<symbol*> *symlist, struct ast *func)
{
  if (ref->symlist) free_list(ref->symlist);
  if (ref->func) free_ast(ref->func);
  ref->symlist = symlist;
  ref->func = func;
}