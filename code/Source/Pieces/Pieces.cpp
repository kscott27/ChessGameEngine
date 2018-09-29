// This source file houses the Pieces constructor, 
// which instantiates all of the piece objects and
// sets their initial data for the beginning of 
// the game.


#include "Pieces.h"

namespace Chess
{

  Pieces * lastCreatedPiecePointer = NULL ;


  Pieces::Pieces( string name, string type )
    : name(name), type(type), in_check(false),
      prev_in_check(false), pinned(false), captured(false),
      color(name[0])
  {
    
    if (color == 'W')
    {
      opponent = 'B';
    }
    if (color == 'B')
    {
      opponent = 'W';
    }

    row = NULL ;
    col = NULL ;

    prevPiecePointer = lastCreatedPiecePointer ;
    lastCreatedPiecePointer = this ;

  }

  string Pieces::getType ( )
  {
    return type ;
  }

  char Pieces::getColor ( )
  {
    return color;
  }

  Pieces * Pieces::getPrevPiecePointer ( )
  {
    return prevPiecePointer;
  }

  string Pieces::getPrevPiecePointerName ( )
  {
    if ( prevPiecePointer != NULL )
    {
      return prevPiecePointer->name;
    }
    else
    {
      return "First piece created has been reached." ;
    }
  }

  string Pieces::getName ( )
  {
    return name ;
  }

  void Pieces::setLocation ( int rowToSet, int colToSet )
  {
    row = rowToSet ;
    col = colToSet ;
  }

  void Pieces::clrLocation ( )
  {
    row = NULL ;
    col = NULL ;
  }



}


