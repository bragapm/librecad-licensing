

/*
UI-only file (.ui.qml): layout & styling. No logic here.
Logic is hooked from App.qml via the aliases / signals below.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    width: 1100
    height: 680
    color: "#0f172a"

    // ---- API for logic (used from App.qml) ----
    property alias usernameField: usernameField
    property alias passwordField: passwordField
    property alias rememberCheck: rememberCheck
    property alias loginButton: loginButton
    property alias forgotButton: forgotButton
    property alias errorText: errorText
    property alias busy: busyIndicator.running

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // ---- Left brand panel ----
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 5
            visible: root.width > 800
            gradient: Gradient {
                orientation: Gradient.Vertical
                GradientStop {
                    position: 0.0
                    color: "#1e3a8a"
                }
                GradientStop {
                    position: 1.0
                    color: "#0f172a"
                }
            }

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 16

                Rectangle {
                    Layout.alignment: Qt.AlignHCenter
                    width: 88
                    height: 88
                    radius: 22
                    color: "#3b82f6"

                    Text {
                        anchors.centerIn: parent
                        text: "L"
                        color: "white"
                        font.pixelSize: 48
                        font.bold: true
                    }
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Licensing Portal")
                    color: "white"
                    font.pixelSize: 34
                    font.bold: true
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Kelola lisensi produk Anda\ndengan mudah dan aman.")
                    horizontalAlignment: Text.AlignHCenter
                    color: "#bfdbfe"
                    font.pixelSize: 16
                }
            }
        }

        // ---- Right login form ----
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: 4
            color: "#f8fafc"

            ColumnLayout {
                anchors.centerIn: parent
                width: Math.min(360, parent.width - 64)
                spacing: 14

                Text {
                    text: qsTr("Selamat Datang")
                    color: "#0f172a"
                    font.pixelSize: 28
                    font.bold: true
                }

                Text {
                    text: qsTr("Silakan login untuk melanjutkan")
                    color: "#64748b"
                    font.pixelSize: 14
                    Layout.bottomMargin: 10
                }

                Text {
                    text: qsTr("Username")
                    color: "#334155"
                    font.pixelSize: 13
                    font.bold: true
                }

                TextField {
                    id: usernameField
                    Layout.fillWidth: true
                    Layout.preferredHeight: 44
                    placeholderText: qsTr("Masukkan username")
                    selectByMouse: true
                    color: "#0f172a"
                    leftPadding: 14
                    rightPadding: 14
                    topPadding: 0
                    bottomPadding: 0
                    verticalAlignment: TextInput.AlignVCenter
                    background: Rectangle {
                        radius: 8
                        color: "white"
                        border.width: usernameField.activeFocus ? 2 : 1
                        border.color: usernameField.activeFocus ? "#3b82f6" : "#cbd5e1"
                    }
                }

                Text {
                    text: qsTr("Password")
                    color: "#334155"
                    font.pixelSize: 13
                    font.bold: true
                }

                TextField {
                    id: passwordField
                    Layout.fillWidth: true
                    Layout.preferredHeight: 44
                    placeholderText: qsTr("Masukkan password")
                    echoMode: TextInput.Password
                    selectByMouse: true
                    color: "#0f172a"
                    leftPadding: 14
                    rightPadding: 14
                    topPadding: 0
                    bottomPadding: 0
                    verticalAlignment: TextInput.AlignVCenter
                    background: Rectangle {
                        radius: 8
                        color: "white"
                        border.width: passwordField.activeFocus ? 2 : 1
                        border.color: passwordField.activeFocus ? "#3b82f6" : "#cbd5e1"
                    }
                }

                RowLayout {
                    Layout.fillWidth: true

                    CheckBox {
                        id: rememberCheck
                        text: qsTr("Ingat saya")
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Button {
                        id: forgotButton
                        flat: true
                        text: qsTr("Lupa password?")
                    }
                }

                Text {
                    id: errorText
                    Layout.fillWidth: true
                    text: ""
                    visible: text.length > 0
                    color: "#dc2626"
                    font.pixelSize: 13
                    wrapMode: Text.WordWrap
                }

                Button {
                    id: loginButton
                    Layout.fillWidth: true
                    Layout.preferredHeight: 46
                    text: qsTr("Login")
                    enabled: !busyIndicator.running

                    contentItem: Text {
                        text: loginButton.text
                        color: "white"
                        font.pixelSize: 16
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 8
                        color: !loginButton.enabled ? "#93c5fd" : loginButton.down ? "#1d4ed8" : loginButton.hovered ? "#2563eb" : "#3b82f6"
                    }

                    BusyIndicator {
                        id: busyIndicator
                        running: false
                        width: 28
                        height: 28
                        anchors.right: parent.right
                        anchors.rightMargin: 12
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }
}
