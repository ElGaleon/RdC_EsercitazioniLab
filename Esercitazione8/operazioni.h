/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _OPERAZIONI_H_RPCGEN
#define _OPERAZIONI_H_RPCGEN

#define RPCGEN_VERSION	199506

#include <rpc/rpc.h>


struct FS_Out {
	int numChar;
	int numWords;
	int numLines;
};
typedef struct FS_Out FS_Out;
#ifdef __cplusplus
extern "C" bool_t xdr_FS_Out(XDR *, FS_Out*);
#elif __STDC__
extern  bool_t xdr_FS_Out(XDR *, FS_Out*);
#else /* Old Style C */
bool_t xdr_FS_Out();
#endif /* Old Style C */


struct DirScan_In {
	char *direttorio;
	int soglia;
};
typedef struct DirScan_In DirScan_In;
#ifdef __cplusplus
extern "C" bool_t xdr_DirScan_In(XDR *, DirScan_In*);
#elif __STDC__
extern  bool_t xdr_DirScan_In(XDR *, DirScan_In*);
#else /* Old Style C */
bool_t xdr_DirScan_In();
#endif /* Old Style C */


#define OPERAZIONIPROG ((rpc_uint)0x20000013)
#define OPERAZIONIVERS ((rpc_uint)1)

#ifdef __cplusplus
#define FILE_SCAN ((rpc_uint)1)
extern "C" FS_Out * file_scan_1(char **, CLIENT *);
extern "C" FS_Out * file_scan_1_svc(char **, struct svc_req *);
#define DIR_SCAN ((rpc_uint)2)
extern "C" int * dir_scan_1(DirScan_In *, CLIENT *);
extern "C" int * dir_scan_1_svc(DirScan_In *, struct svc_req *);

#elif __STDC__
#define FILE_SCAN ((rpc_uint)1)
extern  FS_Out * file_scan_1(char **, CLIENT *);
extern  FS_Out * file_scan_1_svc(char **, struct svc_req *);
#define DIR_SCAN ((rpc_uint)2)
extern  int * dir_scan_1(DirScan_In *, CLIENT *);
extern  int * dir_scan_1_svc(DirScan_In *, struct svc_req *);

#else /* Old Style C */
#define FILE_SCAN ((rpc_uint)1)
extern  FS_Out * file_scan_1();
extern  FS_Out * file_scan_1_svc();
#define DIR_SCAN ((rpc_uint)2)
extern  int * dir_scan_1();
extern  int * dir_scan_1_svc();
#endif /* Old Style C */

#endif /* !_OPERAZIONI_H_RPCGEN */
