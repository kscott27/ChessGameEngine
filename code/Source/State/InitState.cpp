#include "State/InitState.h"

#include "Tools/pugixml/pugixml.hpp"

#include "Pieces/Pieces.h"
#include "Pieces/NullPiece.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/WhitePawn.h"
#include "Pieces/BlackPawn.h"


namespace Chess
{
  namespace State
  {

    BaseState::StatePtr InitState::execute( )
    {
      DEBUG_CONSOLE_1ARG("State: INIT");

      vector<PiecePtr> nullPieceList;
      for( int j = 0; j < 8; j++ )
      {
        for( int i = 0; i < 8; i++ )
        {
          PiecePtr np( new NullPiece(".. ") );
          setPiece(np, j, i);
          nullPieceList.push_back(np);
        }  
      }

      // Configure the state of the board from the xml
      // file passed in during construction of this class.
      parseXMLFile();

      board_->init(nullPieceList);

      currentTurn_ = whiteTurn_;
      
      interface_->printBoard();

      return nextState_;
    }

    void InitState::parseXMLFile()
    {
      // Setup the xml document structure and load the state initialization file
      pugi::xml_document doc;
      pugi::xml_parse_result result = doc.load_file(configFileName_);

      // Grab the root node
      pugi::xml_node root = doc.child("root");

      // Iterate through all of the children of the root node
      for( pugi::xml_node_iterator i = root.begin(); i != root.end(); ++i )
      {
        string type   = i->attribute("type").value();
        string color  = i->attribute("color").value();
        int    row    = i->attribute("row").as_int();
        int    col    = i->attribute("column").as_int();
        string symbol = i->attribute("symbol").value();

        // Create pieces on the heap based on the configuration
        // read from the xml file
        PiecePtr p;
        if( type == "Pawn" )
        {
          if( color == "W" )
            p.reset( new Chess::WhitePawn(symbol) );
          else
            p.reset( new Chess::BlackPawn(symbol) );
        }
        else if( type == "Bishop" )
        {
          p.reset( new Chess::Bishop(symbol, board_) );
        }
        else if( type == "Rook" )
        {
          p.reset( new Chess::Rook(symbol, board_) );
        }
        else if( type == "Knight" )
        {
          p.reset( new Chess::Knight(symbol) );
        }
        else if( type == "Queen" )
        {
          p.reset( new Chess::Queen(symbol, board_) );
        }
        else if( type == "King" )
        {
          p.reset( new Chess::King(symbol, board_) );
          if( color == "W" )
          {
            whiteTurn_->setDefensiveKing(p);
            blackTurn_->setOffensiveKing(p);
          }
          else
          {
            whiteTurn_->setOffensiveKing(p);
            blackTurn_->setDefensiveKing(p);
          }
        }

        setPiece(p,row,col);

        if( color == "W" )
          whiteTurn_->setActivePiece(p);
        else
          blackTurn_->setActivePiece(p);
      }
    }

    void InitState::setPiece( PiecePtr pieceToSet, int rowToSet, int colToSet )
    {
      pieceToSet->setLocation(rowToSet, colToSet);
      board_->setPiece(pieceToSet, rowToSet, colToSet);
    }

  }
}
