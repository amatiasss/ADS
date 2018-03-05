//---------------------------------------------------------------------------
#include <stdlib.h>
//---------------------------------------------------------------------------
#include "ltQuery.h"
//---------------------------------------------------------------------------
void ltQuery::Open( sqlite3 *db ){
    ltQuery::db = db;
}
//---------------------------------------------------------------------------
bool ltQuery::Sql( string sql ){
    return Sql( (char*)sql.c_str() );
}
//---------------------------------------------------------------------------
bool ltQuery::Sql( char* sql ){
   rc = sqlite3_prepare(db, sql, -1, &Stmt, 0);
   if( rc !=SQLITE_OK ) return true;
   rc = sqlite3_exec(db, sql, NULL, 0, &ErrMsg);
   sqlite3_finalize(Stmt);
   if( rc != SQLITE_OK ) return true;
   return false;
}
//---------------------------------------------------------------------------
