/**************************************************************************
 *       Licence: GPL
 **************************************************************************/

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

import GLItems 1.0

/**
  * The glRectangle is used as a parent for the glScene. (see below)
  * For this to work, the viewport of the qmlApplicationViewer (QDeclarativeView)
  * must be set as: setViewport(new QGLWidget);
  */

Rectangle {id: mainRect //covers screen
    color: "black"
    //set width and height to > 0,they will be expanded to fit screen size
    width: 100
    height: 100

    Timer{id: timer
        interval: 20
        repeat: true
        onTriggered:{
            exampleScene.rotate(1)
           exampleScene.callUpdate()
        }
    }
    Row{id: mainRow //button column + glArea
        height: mainRect.height
        spacing: 10
        Column{id:buttonColumn //the buttons
           width: 200
           spacing: 10
           Button{id: buttonClose
              width: buttonColumn.width
              height: mainRect.height / 4 - buttonColumn.spacing
              fontSize: height / 3
              buttonText: "Close"
              onClicked:  Qt.quit();
           }
           Button{id: buttonObjects
              width: buttonColumn.width
              height: mainRect.height / 4 - buttonColumn.spacing
              fontSize: height / 3
              buttonText: "Cubes"
              onClicked:
              {
                  exampleScene.showObject(buttonText)
                  if(buttonText == "Globe")
                      buttonText = "Cubes"
                  else if (buttonText == "Cubes")
                     buttonText = "Triangles"
                  else if(buttonText == "Triangles")
                      buttonText = "Globe"
                 exampleScene.callUpdate()
              }
           }
           Button{id: buttonMove
              width: buttonColumn.width
              height: mainRect.height / 4 - buttonColumn.spacing
              buttonText: "Move"
              fontSize: height / 3
              onClicked: {
                  if(buttonText === "Move")
                  {
                      mainRect.state = "Moving"
                  }
                  else {
                      mainRect.state = ""
                  }
              }
           }
           Button{id: buttonReset
              width: buttonColumn.width
              height: mainRect.height / 4 - buttonColumn.spacing
              fontSize: height / 3
              buttonText: "Reset"
              onClicked: {
                  mainRect.state = ""
                  exampleScene.reset()
              }
           }
        }

        //This rectangle is the background for the OpenGL scene
        //Its color is used for clearing the glScene
        // instead of using glClear(GL_COLOR_BUFFER_BIT).
        // (which would clear the whole screen)
        Rectangle{id: glRectangle
            width: mainRect.width - buttonColumn.width - mainRow.spacing - 1
            height: mainRow.height - 1
            color: "black" //this is the color to be used as gl-background color
            border.color: "white"
            ExampleScene{id: exampleScene //exampleScene accepts mouse events
                anchors.fill: parent
                anchors.margins: 10
                screenHeight: mainRect.height
                //we need screen coordinates here! (no parent coordinates)
                viewportX : glRectangle.x + x
                viewportY : glRectangle.y + y
                viewportW : width
                viewportH : height
            }
          }
    }
    states: [
        State{ name: ""
            StateChangeScript {
                name: "stopTimer"
                script:timer.stop()
            }
        },

        State {
            name: "Moving"
            StateChangeScript {
                name: "startTimer"
                script:timer.start()
            }
            PropertyChanges {
                target: buttonMove
                buttonText: "Stop"
            }
        }
    ]
}
