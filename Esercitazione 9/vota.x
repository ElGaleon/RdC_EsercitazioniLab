const N=7;
const NUMCOL=6;
const MAXS = 256;

struct Input{ char[MAXS] cand ; char op ;};
struct Riga { char[MAXS] col [NUMCOL];
struct Tab { Riga riga[N]; };
program VOTA {
    version VOTAVERS{
    Tab CLASSIFICA_GIUDICI(void) = 1;
    int ESPRIMI_VOTO(Input) = 2;
    } = 1;
} = 0x20000013;
