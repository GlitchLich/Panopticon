import QtQuick 2.0
import "core"

Rectangle {
    id: screen
    width: 800; height: 600;
    property int partition: height/3
    border { width: 1; color: "#DCDCCC"}
    state: "DRAWER_CLOSED"

    /*
    //Item 1: MenuBar on the top portion of the screen
    MenuBar {
        id:menuBar
        height: screen.partition; width: screen.width
        z: 1
    }*/

    //Item 2: The editable text area
    TextArea {
        id: textArea
        y: 0
        color: "#3F3F3F"
        fontColor: "#DCDCCC"
        height: parent.height * 0.8; width:parent.width
    }

    Text {
        id: postArea
        y: 0
        height: parent.height * 0.2
        width: parent.width
        color: "#3F3F3F"
        text: 'Panopticon Panopticon Panopticon Panopticon Panopticon Panopticon Panopticon Panopticon Panopticon Panopticon'
        font { family: 'Mono'; pixelSize: 20; capitalization: Font.SmallCaps }
    }

    /*
    //Item 3: The drawer handle
    Rectangle {
        id: drawer
        height: 15; width: parent.width
        border { color : "#6A6D6A"; width: 1 }
        z: 1
        gradient: Gradient {
                GradientStop { position: 0.0; color: "#8C8F8C" }
                GradientStop { position: 0.17; color: "#6A6D6A" }
                GradientStop { position: 0.77; color: "#3F3F3F" }
                GradientStop { position: 1.0; color: "#6A6D6A" }
        }


        Image {
            id: arrowIcon
            source: "images/arrow.png"
            anchors.horizontalCenter: parent.horizontalCenter
            Behavior{ NumberAnimation { property: "rotation"; easing.type: Easing.OutExpo } }
        }

        MouseArea {
            id: drawerMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onEntered: parent.border.color = Qt.lighter("#6A6D6A")
            onExited:  parent.border.color = "#6A6D6A"
            onClicked: {
                if (screen.state == "DRAWER_CLOSED") {
                    screen.state = "DRAWER_OPEN"
                }
                else if (screen.state == "DRAWER_OPEN"){
                    screen.state = "DRAWER_CLOSED"
                }
            }
        }
    }

//! [states]
    states:[
        State {
            name: "DRAWER_OPEN"
            // PropertyChanges { target: menuBar; y: 0}
            PropertyChanges { target: textArea; y: partition + drawer.height}
            PropertyChanges { target: drawer; y: partition}
            // PropertyChanges { target: arrowIcon; rotation: 180}
        },
        State {
            name: "DRAWER_CLOSED"
            // PropertyChanges { target: menuBar; y:-height; }
            PropertyChanges { target: textArea; y: drawer.height; height: screen.height - drawer.height }
            PropertyChanges { target: drawer; y: 0 }
            // PropertyChanges { target: arrowIcon; rotation: 0 }
        }
    ]
//! [states]

//! [transitions]
    transitions: [
        Transition {
            to: "*"
            NumberAnimation { target: textArea; properties: "y, height"; duration: 100; easing.type:Easing.OutExpo }
            NumberAnimation { target: menuBar; properties: "y"; duration: 100; easing.type: Easing.OutExpo }
            NumberAnimation { target: drawer; properties: "y"; duration: 100; easing.type: Easing.OutExpo }
        }
    ]
//! [transitions]
    */
}
