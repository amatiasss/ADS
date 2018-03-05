//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
//-----------------------------------------------------------------------------
//using std::string;
//using std::stringstream;
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
#include "ltQuery.h"
#include "ltDriver.h"
//------------------------------------------------------------------------------
int REPT, BLOCKSIZE;
//------------------------------------------------------------------------------
string itos(int);
void Insert(ltQuery *Query);
void Select( ltQuery *Query );
void Update( ltQuery *Query );

//------------------------------------------------------------------------------
//argc[1] - Seleciona a operação no banco
//argc[2] - Informa o tamanho do Bloco de Operações
//argc[3] - Informa o número de repetições por operação
int main(int argc, char *argv[] ){
  ltDriver *db    = new ltDriver();
  ltQuery  *Query = new ltQuery();

  char tmp[] = "Banco.db";
  if( db->Attach(tmp)) printf("\n error attach ... ");
  Query->Open ( db->db);

  string str = "delete from A";
  Query->Sql(str.c_str());

  REPT = atoi(argv[3]);
  BLOCKSIZE = atoi(argv[2]);

  switch(atoi(argv[1])){
      case 1: Insert(Query); break;
      case 2: Select(Query); break;
      case 3: Update(Query); break;
  }

	db->Detach();

	delete Query;
	delete db;

    return 0;
}
//------------------------------------------------------------------------------

string itos( int x ){
    stringstream str;
    str << x;
    return str.str();
}
//------------------------------------------------------------------------------
void Insert( ltQuery *Query ){
   for( int r = 0, c=1; r < REPT; r++ ){
         for( int b = 0; b < BLOCKSIZE; b++ ){
              Query->Sql("insert into A(A0,A1,A2,A3,A4,A5,A6) values(" + itos(c++) + ",1,1.2,'abcdefghijklmnopqrstuvxz','abcdefghijklmnopqrstuvxz','11:11:11','2007-11-11');");
         }
   }
}
//------------------------------------------------------------------------------
void Select( ltQuery *Query ){
   for( int r = 0, c=1; r < REPT; r++ ){
         for( int b = 0; b < BLOCKSIZE; b++ ){
              Query->Sql("select * from A where A0=" + itos(c++) );
         }
   }
}
//------------------------------------------------------------------------------
void Update( ltQuery *Query ){
   for( int r = 0, c=1; r < REPT; r++ ){
         for( int b = 0; b < BLOCKSIZE; b++ ){
              Query->Sql( "update A set A1=1, A2=1.2 ,A3='abcdefghijklmnopqrstuvxz', A4='abcdefghijklmnopqrstuvxz', A5= '11:11:11', A6='2007-11-11'  where A0=" + itos(c++) );
         }
   }
}
