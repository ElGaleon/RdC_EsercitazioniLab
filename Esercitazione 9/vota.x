const N=7;
const NUMCOL=6;
const MAXS = 256;


struct Input{ string cand <MAXS>; char op;};
struct Show { string candidato <MAXS>; string giudice <MAXS>; char categoria; string nomeFile <MAXS>; char fase; int voto; };
struct Tab { Show show[N] ; };

struct Nome { string c <MAXS> ;};
struct Elenco { Nome nome[N] ;};

program VOTA {
    version VOTAVERS{
    Elenco CLASSIFICA_GIUDICI(void) = 2;
    int ESPRIMI_VOTO(Input) = 1;
    } = 1;
} = 0x20000013;
