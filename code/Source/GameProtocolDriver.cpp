#include "GameProtocolDriver.h"

#include "State/InitState.h"
#include "State/InputState.h"
#include "State/RelevancyState.h"
#include "State/MoveValidityState.h"
#include "State/PathScanState.h"
#include "State/MoveState.h"
#include "State/DefensiveCheckScanState.h"
#include "State/ReturnPieceState.h"
#include "State/OffensiveCheckScanState.h"
#include "State/SwitchTurnState.h"
#include "State/PinScanState.h"
#include "State/EscapeRouteState.h"
#include "State/CheckmateState.h"


namespace Chess
{

  // Used to set the InitState
  static const char * stateConfigFile("/home/developer/personal/ChessGame/config/DefaultInitialState.xml");

  GameProtocolDriver::GameProtocolDriver( )
    : board_(new Board),
      currentTurn_(),
      interface_(new Interface(board_, currentTurn_)),
      whiteTurn_(new BaseTurn('W')),
      blackTurn_(new BaseTurn('B'))
  {
    createStateMachine();
    runStateMachine();
  }

  void GameProtocolDriver::createStateMachine( )
  {
    using namespace State;

    init_.reset(               new InitState(stateConfigFile, interface_, board_, whiteTurn_, blackTurn_, currentTurn_) );
    input_.reset(              new InputState(interface_) );
    relevancy_.reset(          new RelevancyState(interface_) );
    moveValidity_.reset(       new MoveValidityState(interface_, board_) );
    pathscan_.reset(           new PathScanState(interface_, board_) );
    move_.reset(               new MoveState(interface_, board_) );
    defensiveCheckScan_.reset( new DefensiveCheckScanState(board_, currentTurn_) );
    returnPiece_.reset(        new ReturnPieceState(interface_, board_) );
    offensiveCheckScan_.reset( new OffensiveCheckScanState(board_, currentTurn_) );
    switchTurn_.reset(         new SwitchTurnState(interface_, whiteTurn_, blackTurn_, currentTurn_) );
    pinScan_.reset(            new PinScanState(board_, currentTurn_) );
    escapeRoute_.reset(        new EscapeRouteState(interface_, board_, currentTurn_) );
    checkmate_.reset(          new CheckmateState(interface_) );

    init_->setTransitionStates(               input_, input_ );
    input_->setTransitionStates(              relevancy_, input_ );
    relevancy_->setTransitionStates(          moveValidity_, input_ );
    moveValidity_->setTransitionStates(       pathscan_, input_ );
    pathscan_->setTransitionStates(           move_, input_ );
    move_->setTransitionStates(               defensiveCheckScan_, input_ );
    defensiveCheckScan_->setTransitionStates( offensiveCheckScan_, returnPiece_ );
    returnPiece_->setTransitionStates(        input_, input_ );
    offensiveCheckScan_->setTransitionStates( pinScan_, pinScan_ );
    pinScan_->setTransitionStates(            escapeRoute_, switchTurn_ );
    escapeRoute_->setTransitionStates(        checkmate_, switchTurn_ );
    switchTurn_->setTransitionStates(         input_, input_ );
  }

  void GameProtocolDriver::runStateMachine( )
  {
    currentState_ = init_->execute();

    while( currentState_ != checkmate_ )
      currentState_ = currentState_->execute();

    currentState_->execute();
    std::cout << "State machine done." << std::endl;
  }

}
