//---------------------------------------------------------------------------
#ifndef ltQueryH
#define ltQueryH
//-----------------------------------------------------------------------------
#include "sqlite3.h"
//-----------------------------------------------------------------------------
#include <string>
using std::string;
//-----------------------------------------------------------------------------
#if !defined(_WIN32) && !defined(WIN32) && !defined(__MACOS__)
# include <signal.h>
# include <pwd.h>
# include <unistd.h>
# include <sys/types.h>
#endif
//-----------------------------------------------------------------------------
#ifdef __MACOS__
# include <console.h>
# include <signal.h>
# include <unistd.h>
# include <extras.h>
# include <Files.h>
# include <Folders.h>
#endif
//-----------------------------------------------------------------------------
#if defined(HAVE_READLINE) && HAVE_READLINE==1
# include <readline/readline.h>
# include <readline/history.h>
#else
# define readline(p) local_getline(p,stdin)
# define add_history(X)
# define read_history(X)
# define write_history(X)
# define stifle_history(X)
#endif
//-----------------------------------------------------------------------------
typedef unsigned char uchar;
//-----------------------------------------------------------------------------
class ltQuery{
    private:
	    sqlite3       *db;
        char          *ErrMsg;
        sqlite3_stmt  *Stmt;
        char         **azResult;
	    int  	       rc, size, column, cursor, total;

	public:
        void Open( sqlite3* );
        bool Sql ( string   );
        bool Sql ( char*    );
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
