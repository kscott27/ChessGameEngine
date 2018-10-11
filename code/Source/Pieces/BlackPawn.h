// This header file houses all of the data
// that composes the Pawn 
// class. This class serves to characterize
// each piece with specific data, along with
// data inherited from the Pieces class, which is 
// analyzed by the Mastermind files.


#ifndef BLACKPAWN_H_
#define BLACKPAWN_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
// #include "Interface.h"
#include "Pieces.h"

using namespace std;

namespace Chess
{

    class BlackPawn 
    : public Pieces
    {
    protected:

    public:

      // Contructs piece objects which take the interface object,
      // a specified name, and specified initial coordinates as
      // arguments.
      BlackPawn( const string name, Board * board, int initRow, int initCol );
      BlackPawn( const string name, Board * board );
      bool validDirection( int destRow, int destCol ) ;
      virtual bool pathScan( int destRow, int destCol ) ;  
      
    };


}




#endif /* BLACKPAWN_H_ */
