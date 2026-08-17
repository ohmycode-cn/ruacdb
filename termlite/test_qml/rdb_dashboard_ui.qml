import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Basic

ApplicationWindow {
    x: 1200
    y: 800
    width: 600
    height: 400
    visible: true

    Rectangle {
        id: root
        width: parent.width - 20
        height: parent.height - 20
        color: "green"
        radius: 16
        anchors.centerIn: parent

        Text {
            anchors.centerIn: parent
            font.pixelSize: 24
            color: "red"
            text: "This is tmp test"
        }
    }

    Rectangle {
        id: button_list
        width: root.width / 4
        height: root.height - 20
        color: "white"
        radius: 16
        anchors.left: root.left
        anchors.verticalCenter: root.verticalCenter
        anchors.leftMargin: 5

        Column {
            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Repeater {
                model: ["Settings", "CPU", "GPU", "NPU", "Memory", "Disk", "Network"]

                Item {
                    width: parent.width
                    height: 36

                    Rectangle {
                        id: shadow
                        anchors.fill: btn
                        anchors.topMargin: 2
                        radius: btn.radius
                        color: "#40000000"
                        visible: mouseArea.containsMouse
                    }

                    Rectangle {
                        id: btn
                        width: parent.width
                        height: 36
                        color: mouseArea.containsMouse ? '#e84040' : "#aa0000"
                        radius: root.radius - 6
                        y: mouseArea.containsMouse ? -3 : 0

                        Behavior on y {
                            NumberAnimation {
                                duration: 150
                                easing.type: Easing.OutQuad
                            }
                        }

                        Behavior on color {
                            ColorAnimation {
                                duration: 150
                            }
                        }

                        Text {
                            anchors.centerIn: parent
                            text: modelData
                            color: "white"
                            font.pixelSize: 14
                        }

                        MouseArea {
                            id: mouseArea
                            anchors.fill: parent
                            hoverEnabled: true
                            cursorShape: Qt.PointingHandCursor
                            onClicked: console.log("Clicked:", modelData)
                        }
                    }
                }
            }
        }
    }
}
