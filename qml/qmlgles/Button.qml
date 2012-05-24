import QtQuick 1.0

//A button that sends a clicked signal.
//Shows a white frame when pressed.
//Use the buttonText property for text on the button.

Rectangle {
    property string buttonText: "buttonText"
    property int fontSize: frame.height / 2
    signal clicked()

    id: frame
    width: 170
    height: 50
    border.width: 2
    border.color: "black"
    radius: 10
    gradient: Gradient {
        GradientStop {
            id: topGradient
            position: 0
            color: "#0d0dff"
        }

        GradientStop {
            position: 1
            color: "#020202"
        }
    }

    Text{
       id: buttonText
       text: parent.buttonText
       font.pointSize: fontSize
       font.bold: true
       color: "white"
       verticalAlignment: Text.AlignVCenter
       horizontalAlignment: Text.AlignHCenter
       anchors.fill: parent
    }
    MouseArea{
        id: mousearea1
        anchors.fill: parent
        onPressed: {
            frame.state = "Pressed"
        }
        onReleased: {
            frame.state = "" //base state
        }

        onClicked:{
            console.log("Button clicked: " + buttonText.text)
            frame.clicked()
            frame.state = "State1"
        }
    }
    states: [
        State {
            name: "Pressed"

            PropertyChanges {
                target: frame
                border.width : 4
                border.color: "white"
             }
        }
    ]
}
